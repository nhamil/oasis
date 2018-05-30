#include "Oasis/Graphics/OpenGL/OGLShader.h"

#include "Oasis/Graphics/VertexFormat.h"

#include <iostream>

using namespace std;

namespace Oasis
{

static const int OGL_ATTRIBUTE_INDEX[ATTRIBUTE_COUNT] =
{
    0, 1, 2, 3, 4
};

static const string OGL_ATTRIBUTE_NAME[ATTRIBUTE_COUNT] =
{
    "a_Position",
    "a_Normal",
    "a_Bitangent",
    "a_Texture",
    "a_Color"
};

Uniform OGLShader::GetUniformType(GLenum type)
{
    switch (type)
    {
    case GL_SAMPLER_2D: return UNIFORM_INT;
    case GL_INT: return UNIFORM_INT;
    case GL_FLOAT: return UNIFORM_FLOAT;
    case GL_FLOAT_VEC2: return UNIFORM_VECTOR2;
    case GL_FLOAT_VEC3: return UNIFORM_VECTOR3;
    case GL_FLOAT_VEC4: return UNIFORM_VECTOR4;
    case GL_FLOAT_MAT3: return UNIFORM_MATRIX3;
    case GL_FLOAT_MAT4: return UNIFORM_MATRIX4;
    default: return UNIFORM_UNKNOWN;
    }
}

int OGLShader::GetAttributeIndex(Attribute attrib)
{
    return OGL_ATTRIBUTE_INDEX[attrib];
}

const string& OGLShader::GetAttributeName(Attribute attrib)
{
    return OGL_ATTRIBUTE_NAME[attrib];
}

OGLShader::OGLShader(const string& vs, const string& fs)
    : id_(0)
    , valid_(true)
    , errorMessage_()
    , vSource_(vs)
    , fSource_(fs)
{
    //cout << "Vertex source: " << vs << endl;
    //cout << "Fragment source: " << fs << endl;

    id_ = glCreateProgram();
    GLuint vId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fId = glCreateShader(GL_FRAGMENT_SHADER);

    valid_ &= Compile(vId, GL_VERTEX_SHADER, "vertex shader", vSource_);
    valid_ &= Compile(fId, GL_FRAGMENT_SHADER, "fragment shader", fSource_);
    valid_ &= Link(vId, fId);

    if (valid_)
    {
        FindUniforms();
    }

    glDeleteShader(vId);
    glDeleteShader(fId);
}

OGLShader::~OGLShader()
{
    Release();
}

void OGLShader::Release()
{
    if (id_)
    {
        glDeleteProgram(id_);
        id_ = 0;
    }
}

GLuint OGLShader::GetId() const
{
    return id_;
}

bool OGLShader::IsValid() const
{
    return valid_;
}

const string& OGLShader::GetErrorMessage() const
{
    return errorMessage_;
}

const string& OGLShader::GetVertexSource() const
{
    return vSource_;
}

const string& OGLShader::GetFragmentSource() const
{
    return fSource_;
}

bool OGLShader::Compile(GLuint id, GLuint type, const string& typeName, const string& source)
{
    const char* src = source.c_str();
    int srcLength = source.length();
    GLint status;

    glShaderSource(id, 1, &src, &srcLength);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char text[512];
        GLsizei length;
        glGetShaderInfoLog(id, 512, &length, text);

        errorMessage_ += text;
        errorMessage_ += "\n";

        cout << "Error compiling " << typeName << " : " << text << endl;
        return false;
    }

    cout << "Compiling " << typeName << " success!" << endl;
    return true;
}

bool OGLShader::Link(GLuint vs, GLuint fs)
{
    glAttachShader(id_, vs);
    glAttachShader(id_, fs);

    // bind attribs
    for (int i = 0; i < ATTRIBUTE_COUNT; i++)
    {
        glBindAttribLocation(id_, OGL_ATTRIBUTE_INDEX[i], OGL_ATTRIBUTE_NAME[i].c_str());
        cout << "Binding attrib location " << OGL_ATTRIBUTE_INDEX[i] << " " << OGL_ATTRIBUTE_NAME[i] << endl;
    }

    glLinkProgram(id_);

    GLint status;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char text[512];
        GLsizei length;
        glGetProgramInfoLog(id_, 512, &length, text);

        errorMessage_ += text;
        errorMessage_ += "\n";

        cout << "Error linking shader : " << text << endl;

        glDeleteShader(id_);
        id_ = 0;

        return false;
    }

    cout << "Linking shader success!" << endl;
    return true;
}

void OGLShader::FindUniforms()
{
    int count;

    glGetProgramiv(id_, GL_ACTIVE_UNIFORMS, &count);

    char name[1024];
    GLsizei length;
    GLint size;
    GLenum type;

    for (int i = 0; i < count; i++)
    {
        glGetActiveUniform(id_, i, 1024, &length, &size, &type, name);

        uniformValues_[name] = UniformValue(i, GetUniformType(type));
    }
}

UniformValue* OGLShader::GetUniformValue(const std::string& name)
{
    map<string, UniformValue>::iterator it = uniformValues_.find(name);

    if (it == uniformValues_.end())
    {
        return NULL;
    }
    else
    {
        return &it->second;
    }
}

}
