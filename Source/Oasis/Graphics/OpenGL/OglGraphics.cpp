#include "Oasis/Graphics/OpenGL/OGLGraphics.h"

#include "Oasis/Core/Window.h"

#include "Oasis/Graphics/OpenGL/OGLShader.h"

#include <GL/glew.h>

#include <iostream>
#include <string>

using namespace std;

namespace Oasis
{

static const string OGL_VS = ""
    "#version 120 \n"
    "attribute vec3 a_Position; \n"
    "uniform mat4 oa_Model; \n"
    "uniform mat4 oa_View; \n"
    "uniform mat4 oa_Proj; \n"
    "void main() { \n"
    "  gl_Position = oa_Proj * oa_View * oa_Model * vec4(a_Position, 1.0); \n"
    "} \n";

static const string OGL_FS = ""
    "#version 120 \n"
    "uniform vec3 u_Color; \n"
    "void main() { \n"
    "  gl_FragColor = vec4(u_Color, 1.0); \n"
    "} \n";

static const GLuint OGL_PRIMITIVE[(int) Primitive::COUNT] =
{
    GL_LINES,
    GL_LINE_STRIP,
    GL_TRIANGLES,
    GL_TRIANGLE_STRIP
};

void OGLGraphics::BindVertexArray()
{
    if (!vertexArray_) return;

    OGLIndexBuffer* ib = (OGLIndexBuffer*) vertexArray_->GetIndexBuffer();

    if (ib)
    {
        ib->Upload();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->GetId());
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int attribs[ATTRIBUTE_COUNT];

    for (int i = 0; i < ATTRIBUTE_COUNT; i++) attribs[i] = -1;

    for (int i = 0; i < vertexArray_->GetVertexBufferCount(); i++)
    {
        OGLVertexBuffer* vb = (OGLVertexBuffer*) vertexArray_->GetVertexBuffer(i);
        vb->Upload();
        const VertexFormat& format = vb->GetFormat();

        for (int j = 0; j < format.GetAttributeCount(); j++)
        {
            Attribute attrib = format.GetAttribute(j);

            if (attribs[attrib] == -1)
            {
                attribs[attrib] = i;
            }
        }
    }

    for (int i = 0; i < ATTRIBUTE_COUNT; i++)
    {
        if (attribs[i] == -1)
        {
            glDisableVertexAttribArray(OGLShader::GetAttributeIndex((Attribute) i));
            //cout << "Disabling " << OGLShader::GetAttributeName((Attribute) i) << endl;
            continue;
        }

        OGLVertexBuffer* vb = (OGLVertexBuffer*) vertexArray_->GetVertexBuffer(attribs[i]);
        //cout << "Binding " << vb->GetId() << endl;
        glBindBuffer(GL_ARRAY_BUFFER, vb->GetId());

        //cout << "Enabling " << OGLShader::GetAttributeName((Attribute) i) << endl;
        glEnableVertexAttribArray(OGLShader::GetAttributeIndex((Attribute) i));

        /*cout << "attrib pointer "
            << i << " "
            << GetAttributeSize((Attribute) i) << " "
            << vb->GetFormat().GetSize() * sizeof (float) << " "
            << (vb->GetFormat().GetOffset((Attribute) i) * sizeof (float)) << endl;*/
        glVertexAttribPointer(i, GetAttributeSize((Attribute) i), GL_FLOAT, GL_FALSE, vb->GetFormat().GetSize() * sizeof (float), (void*) (vb->GetFormat().GetOffset((Attribute) i) * sizeof (float)));
    }
}

OGLGraphics::OGLGraphics()
    : vertexArray_(NULL)
{
    shader_ = (OGLShader*) CreateShader(OGL_VS, OGL_FS);

    /*GLuint shader, vert, frag;

    shader = glCreateProgram();
    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vs = OGL_VS.c_str();
    int vsLength = OGL_VS.length();

    const char* fs = OGL_FS.c_str();
    int fsLength = OGL_FS.length();

    glShaderSource(vert, 1, &vs, &vsLength);
    glCompileShader(vert);

    glShaderSource(frag, 1, &fs, &fsLength);
    glCompileShader(frag);

    glAttachShader(shader, vert);
    glAttachShader(shader, frag);

    for (int i = 0; i < ATTRIBUTE_COUNT; i++)
    {
        glBindAttribLocation(shader, OGL_ATTRIBUTE_INDEX[i], OGL_ATTRIBUTE_NAME[i].c_str());
        cout << "Binding attrib location " << OGL_ATTRIBUTE_INDEX[i] << " " << OGL_ATTRIBUTE_NAME[i] << endl;
    }

    glLinkProgram(shader);*/

    glUseProgram(shader_->GetId());
}

OGLGraphics::~OGLGraphics()
{

}

int OGLGraphics::GetMaxTextureCount() const
{
    return 16;
}

void OGLGraphics::PreRender()
{
    SetViewport(0, 0, Engine::GetWindow()->GetWidth(), Engine::GetWindow()->GetHeight());
    SetClearColor(0);
    Clear();
}

void OGLGraphics::PostRender()
{

}

void OGLGraphics::SetViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

void OGLGraphics::SetClearColor(const Vector4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}

void OGLGraphics::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OGLGraphics::SetVertexArray(VertexArray* geom)
{
    vertexArray_ = (OGLVertexArray*) geom;
}

void OGLGraphics::SetShader(Shader* shader)
{
    shader_ = (OGLShader*) shader;

    if (shader_)
    {
        glUseProgram(shader_->GetId());
    }
    else
    {
        glUseProgram(0);
    }
}

void OGLGraphics::SetTexture(int unit, Texture* tex)
{

}

void OGLGraphics::DrawArrays(Primitive prim, int start, int primCount)
{
    if (!vertexArray_) return;

    BindVertexArray();

    // TODO primitive size
    glDrawArrays(OGL_PRIMITIVE[(int) prim], start, primCount * 3);
}

void OGLGraphics::DrawIndexed(Primitive prim, int start, int primCount)
{
    if (!vertexArray_) return;

    BindVertexArray();

    // TODO primitive size
    glDrawElements(OGL_PRIMITIVE[(int) prim], primCount * 3, GL_UNSIGNED_SHORT, (void*)(start * sizeof(short)));
}

IndexBuffer* OGLGraphics::CreateIndexBuffer(int numElements, BufferUsage usage)
{
    return new OGLIndexBuffer(numElements, usage);
}

VertexBuffer* OGLGraphics::CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage)
{
    return new OGLVertexBuffer(numElements, format, usage);
}

VertexArray* OGLGraphics::CreateVertexArray()
{
    return new OGLVertexArray();
}

Shader* OGLGraphics::CreateShader(const std::string& vs, const std::string& fs)
{
    return new OGLShader(vs, fs);
}

Texture2D* OGLGraphics::CreateTexture2D()
{
    return NULL;
}

Uniform OGLGraphics::GetUniform(const std::string& name)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            return uv->type;
        }
        else
        {
            return UNIFORM_NONE;
        }
    }
    else
    {
        return UNIFORM_NONE;
    }
}

bool OGLGraphics::HasUniform(const std::string& name)
{
    return GetUniform(name) != UNIFORM_NONE;
}

bool OGLGraphics::ClearUniform(const std::string& name)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            switch (uv->type)
            {
            case UNIFORM_INT: return SetUniform(name, 0);
            case UNIFORM_FLOAT: return SetUniform(name, 0);
            case UNIFORM_VECTOR2: return SetUniform(name, (Vector2){0, 0});
            case UNIFORM_VECTOR3: return SetUniform(name, (Vector3){0, 0, 0});
            case UNIFORM_VECTOR4: return SetUniform(name, (Vector4){0, 0, 0, 1});
            case UNIFORM_MATRIX3: return SetUniform(name, Matrix3::Identity());
            case UNIFORM_MATRIX4: return SetUniform(name, Matrix4::Identity());
            default: return false;
            }
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, int value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniform1i(uv->location, value);
            return true;
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, float value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniform1f(uv->location, value);
            return true;
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, const Vector2& value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniform2fv(uv->location, 1, &value[0]);
            return true;
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, const Vector3& value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniform3fv(uv->location, 1, &value[0]);
            return true;
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, const Vector4& value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniform4fv(uv->location, 1, &value[0]);
            return true;
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, const Matrix3& value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniformMatrix3fv(uv->location, 1, GL_FALSE, &value[0]);
            return true;
        }
    }

    return false;
}

bool OGLGraphics::SetUniform(const std::string& name, const Matrix4& value)
{
    if (shader_)
    {
        UniformValue* uv = shader_->GetUniformValue(name);

        if (uv)
        {
            glUniformMatrix4fv(uv->location, 1, GL_FALSE, &value[0]);
            return true;
        }
    }

    return false;
}


}