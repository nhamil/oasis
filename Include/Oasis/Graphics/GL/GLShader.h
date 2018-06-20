#pragma once 

#include "Oasis/Graphics/Shader.h" 
#include "Oasis/Graphics/VertexFormat.h" 

#include <GL/glew.h> 

namespace Oasis 
{

class GLGraphicsDevice; 

class OASIS_API GLShader : public Shader 
{
public: 
    GLShader(GLGraphicsDevice* graphics, const std::string& vSource, const std::string& fSource); 
    ~GLShader(); 

    static int GetAttributeIndex(Attribute attrib); 
    static const char* GetAttributeName(Attribute attrib); 

    static ParameterType GetParameterType(GLenum uniformType); 

    inline GLuint GetId() const { return id_; } 

private: 
    void Upload() override; 
    void Create(); 
    void Destroy(); 

    bool CompileShader(GLuint id, GLenum type, const char* typeName, const std::string& source); 
    bool LinkProgram(GLuint vId, GLuint fId); 
    void FindUniforms(); 

    GLGraphicsDevice* graphics_; 
    GLuint id_ = 0; 
};

}