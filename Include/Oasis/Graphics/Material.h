#pragma once

#include "Oasis/Common.h"

#include "Oasis/Math/MathUtil.h"

#include "Oasis/Graphics/Parameter.h"

#include <string>
#include <unordered_map>

namespace Oasis
{

class Shader; 
class Shader; 

class OASIS_API Material
{
public:
    Material();
    ~Material();

    void ApplyToShaderVariant(Shader* variant); 

    void ClearParameter(const std::string& name); 
    void SetParameter(const std::string& name, const Parameter& value); 

    inline void SetInt(const std::string& name, int value) { SetParameter(name, Parameter(value)); }
    inline void SetFloat(const std::string& name, float value) { SetParameter(name, Parameter(value)); } 
    inline void SetVector2(const std::string& name, const Vector2& value) { SetParameter(name, Parameter(value)); }
    inline void SetVector3(const std::string& name, const Vector3& value) { SetParameter(name, Parameter(value)); }
    inline void SetVector4(const std::string& name, const Vector4& value) { SetParameter(name, Parameter(value)); }
    inline void SetMatrix3(const std::string& name, const Matrix3& value) { SetParameter(name, Parameter(value)); }
    inline void SetMatrix4(const std::string& name, const Matrix4& value) { SetParameter(name, Parameter(value)); }

    const Parameter* GetParameter(const std::string& name) const;

    Shader* GetShader() { return shader_; } 
    void SetShader(Shader* shader);  

    void SetKeywords(const std::string& keywords); 
    const std::string& GetKeywords() const { return keywords_; } 

private:
    Shader* shader_; 
    std::unordered_map<std::string, Parameter> parameters_;
    std::string keywords_; 
};

}
