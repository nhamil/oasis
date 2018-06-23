#include "Oasis/Graphics/GL/GLShader.h" 

#include "Oasis/Graphics/VertexFormat.h" 
#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 
#include "Oasis/Graphics/GL/GLUtil.h" 

using namespace std; 

namespace Oasis 
{

const int ATTRIBUTE_INDEX[(int) Attribute::count] =
{
    0, 1, 2, 3, 4
};

const char* const ATTRIBUTE_NAME[(int) Attribute::count] =
{
    "a_Position",
    "a_Normal",
    "a_Bitangent",
    "a_Texture",
    "a_Color"
};

GLShader::GLShader(GLGraphicsDevice* graphics, const string& vs, const string& fs) 
    : Shader(vs, fs) 
    , graphics_(graphics) 
{
    Create(); 
}

GLShader::~GLShader() 
{
    Destroy(); 
}

void GLShader::Create() 
{
    if (id_) return; 

    GLuint vId, fId; 

    GLCALL(vId = glCreateShader(GL_VERTEX_SHADER)); 
    GLCALL(fId = glCreateShader(GL_FRAGMENT_SHADER)); 
    GLCALL(id_ = glCreateProgram()); 

    valid_ = true; 

    GLCALL(valid_ &= CompileShader(vId, "vertex shader", vSource_)); 
    GLCALL(valid_ &= CompileShader(fId, "fragment shader", fSource_)); 
    GLCALL(valid_ &= LinkProgram(vId, fId)); 

    if (valid_) FindUniforms(); 

    GLCALL(glDeleteShader(vId)); 
    GLCALL(glDeleteShader(fId)); 
}

void GLShader::UploadToGPU() 
{
    GLCALL(glUseProgram(id_)); 

    for (auto& name : updateParameters_) 
    {
        auto it = parameters_.find(name); 

        if (it != parameters_.end()) 
        {
            ShaderParameter& param = it->second; 

            if (param.dirty) // should be true but just check in case 
            {
                //cout << "Upload parameter: " << param.location << " (" << name << ")" << endl; 
                switch (param.type) 
                {
                case ParameterType::INT: 
                    //cout << "Upload int uniform" << endl; 
                    GLCALL(glUniform1i(param.location, param.curValue.GetInt())); 
                    break; 
                case ParameterType::FLOAT: 
                    //cout << "Uplaod float uniform" << endl; 
                    GLCALL(glUniform1f(param.location, param.curValue.GetFloat())); 
                    break; 
                case ParameterType::VECTOR2: 
                    //cout << "Upload vector2 uniform" << endl; 
                    GLCALL(glUniform2fv(param.location, 1, (float*) &(param.curValue.GetVector2()))); 
                    break; 
                case ParameterType::VECTOR3: 
                    //cout << "Upload vector3 uniform" << endl; 
                    GLCALL(glUniform3fv(param.location, 1, (float*) &(param.curValue.GetVector3()))); 
                    break; 
                case ParameterType::VECTOR4: 
                    //cout << "Upload vector4 uniform" << endl; 
                    GLCALL(glUniform4fv(param.location, 1, (float*) &(param.curValue.GetVector4()))); 
                    break; 
                case ParameterType::MATRIX3: 
                    //cout << "Upload matrix3 uniform" << endl; 
                    GLCALL(glUniformMatrix3fv(param.location, 1, GL_FALSE, (float*) &(param.curValue.GetMatrix3()))); 
                    break; 
                case ParameterType::MATRIX4: 
                    //cout << "Upload matrix4 uniform" << endl; 
                    GLCALL(glUniformMatrix4fv(param.location, 1, GL_FALSE, (float*) &(param.curValue.GetMatrix4()))); 
                    break; 
                default: 
                    //cout << "Unknown ParameterType: " << (int) param.type << endl; 
                    break; 
                }

                param.dirty = false; 
            }
        }
    }

    updateParameters_.clear(); 
} 

void GLShader::Destroy() 
{
    if (id_) 
    {
        if (graphics_->GetShader() == this) graphics_->SetShader(nullptr); 

        GLCALL(glDeleteProgram(id_)); 
        id_ = 0; 
    }
} 

int GLShader::GetAttributeIndex(Attribute attrib) 
{
    return ATTRIBUTE_INDEX[(int) attrib]; 
}

const char* GLShader::GetAttributeName(Attribute attrib) 
{
    return ATTRIBUTE_NAME[(int) attrib]; 
}

ParameterType GLShader::GetParameterType(GLenum type) 
{
    switch (type) 
    {
    case GL_INT: return ParameterType::INT; 
    case GL_FLOAT: return ParameterType::FLOAT; 
    case GL_FLOAT_VEC2: return ParameterType::VECTOR2; 
    case GL_FLOAT_VEC3: return ParameterType::VECTOR3; 
    case GL_FLOAT_VEC4: return ParameterType::VECTOR4; 
    case GL_FLOAT_MAT3: return ParameterType::MATRIX3; 
    case GL_FLOAT_MAT4: return ParameterType::MATRIX4; 
    default: return ParameterType::UNKNOWN; 
    }
}

bool GLShader::CompileShader(GLuint id, const char* typeName, const string& source) 
{
    const char* src = source.c_str();
    int srcLength = source.length();
    GLint status;

    GLCALL(glShaderSource(id, 1, &src, &srcLength));
    GLCALL(glCompileShader(id));

    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
    if (status != GL_TRUE)
    {
        char text[512];
        GLsizei length;
        GLCALL(glGetShaderInfoLog(id, 512, &length, text));

        errorMessage_ += text;
        errorMessage_ += "\n";

        Logger::Warning("Error compiling ", typeName, " : ", text);
        return false;
    }

    Logger::Debug("Compiling ", typeName, " success!");
    return true;
}

bool GLShader::LinkProgram(GLuint vId, GLuint fId) 
{
    GLCALL(glAttachShader(id_, vId));
    GLCALL(glAttachShader(id_, fId));

    // bind attribs
    for (int i = 0; i < (int) Attribute::count; i++)
    {
        GLCALL(glBindAttribLocation(id_, ATTRIBUTE_INDEX[i], ATTRIBUTE_NAME[i]));
        //Logger::Debug("Binding attrib location ", ATTRIBUTE_INDEX[i], " to ", ATTRIBUTE_NAME[i]);
    }

    GLCALL(glLinkProgram(id_));

    GLint status;
    GLCALL(glGetProgramiv(id_, GL_LINK_STATUS, &status));
    if (status != GL_TRUE)
    {
        char text[512];
        GLsizei length;
        GLCALL(glGetProgramInfoLog(id_, 512, &length, text));

        errorMessage_ += text;
        errorMessage_ += "\n";

        Logger::Error("Error linking program : ", text);

        GLCALL(glDeleteShader(id_));
        id_ = 0;

        return false;
    }

    Logger::Debug("Linking program success!");
    return true;
}

void GLShader::FindUniforms() 
{
    int count;

    GLCALL(glGetProgramiv(id_, GL_ACTIVE_UNIFORMS, &count));

    char name[1024];
    GLsizei length;
    GLint size;
    GLenum type;

    for (int i = 0; i < count; i++)
    {
        GLCALL(glGetActiveUniform(id_, i, 1024, &length, &size, &type, name));

        ParameterType paramType = GetParameterType(type); 
        parameters_[name] = ShaderParameter(paramType, i, Parameter(paramType));
    }
}

}