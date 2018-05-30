#pragma once

#include "Oasis/Graphics/Shader.h"
#include "Oasis/Graphics/VertexFormat.h"

#include "Oasis/Math/MathUtil.h"

#include <GL/glew.h>

#include <map>

namespace Oasis
{

class OGLShader;

struct OASIS_API UniformValue
{
    UniformValue() : location(0), type(UNIFORM_UNKNOWN) {}
    UniformValue(GLuint loc, Uniform type) : location(loc), type(type) {}
    UniformValue(const UniformValue& uv) : location(uv.location), type(uv.type) {}
    UniformValue& operator=(const UniformValue& uv)
    {
        if (this == &uv) return *this;
        location = uv.location;
        type = uv.type;
        return *this;
    }

    GLuint location;
    Uniform type;
};

class OASIS_API OGLShader : public Shader
{
public:
    static int GetAttributeIndex(Attribute attrib);
    static const std::string& GetAttributeName(Attribute attrib);

    static Uniform GetUniformType(GLenum type);

    OGLShader(const std::string& vs, const std::string& fs);
    ~OGLShader();

    void Release();

    GLuint GetId() const;

    bool IsValid() const;

    const std::string& GetErrorMessage() const;

    const std::string& GetVertexSource() const;
    const std::string& GetFragmentSource() const;

    UniformValue* GetUniformValue(const std::string& name);

private:
    bool Compile(GLuint id, GLuint type, const std::string& typeName, const std::string& source);
    bool Link(GLuint vs, GLuint fs);

    void FindUniforms();

    GLuint id_;
    bool valid_;
    std::string errorMessage_;
    std::string vSource_;
    std::string fSource_;

    std::map<std::string, UniformValue> uniformValues_;
};

}
