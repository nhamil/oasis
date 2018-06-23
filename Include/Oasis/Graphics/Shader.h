#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/Parameter.h" 
#include "Oasis/Math/MathUtil.h" 

namespace Oasis
{

class Shader; 

struct OASIS_API ShaderParameter 
{
    ParameterType type; 
    unsigned location; 
    Parameter curValue; 
    Parameter defValue; 
    bool dirty = true; 

    ShaderParameter() = default; 
    ShaderParameter(const ShaderParameter& other) = default; 
    ShaderParameter& operator=(const ShaderParameter& other) = default; 
    ShaderParameter(ParameterType type, unsigned location, const Parameter& value) 
        : type(type), location(location), curValue(value), defValue(value) {} 

    inline void Reset() 
    {
        if (defValue != curValue) 
        {
            curValue = defValue; 
            dirty = true; 
        }
    }

    inline void Set(const Parameter& param) 
    {
        if (param != curValue) 
        {
            curValue = param; 
            dirty = true; 
        }
    }
};

class OASIS_API Shader  
{
public:
    Shader(const std::string& vSource, const std::string& fSource); 
    virtual ~Shader(); 

    void FlushToGPU(); 

    inline bool IsValid() const { return valid_; } 

    inline const std::string& GetErrorMessage() const { return errorMessage_; } 

    inline const std::string& GetVertexSource() const { return vSource_; }
    inline const std::string& GetFragmentSource() const { return fSource_; } 

    void ClearParameter(const std::string& name); 
    void SetParameter(const std::string& name, const Parameter& value); 

    inline void SetTextureUnit(const std::string& name, int value) { SetParameter(name, Parameter(value)); } 
    inline void SetInt(const std::string& name, int value) { SetParameter(name, Parameter(value)); } 
    inline void SetFloat(const std::string& name, float value) { SetParameter(name, Parameter(value)); }  
    inline void SetVector2(const std::string& name, const Vector2& value) { SetParameter(name, Parameter(value)); }  
    inline void SetVector3(const std::string& name, const Vector3& value) { SetParameter(name, Parameter(value)); }  
    inline void SetVector4(const std::string& name, const Vector4& value) { SetParameter(name, Parameter(value)); } 
    inline void SetMatrix3(const std::string& name, const Matrix3& value) { SetParameter(name, Parameter(value)); }  
    inline void SetMatrix4(const std::string& name, const Matrix4& value) { SetParameter(name, Parameter(value)); }  

protected: 
    virtual void UploadToGPU() = 0; 

    inline void FlagUpdateParameter(const std::string& name) 
    {
        updateParameters_.insert(name); 
    }

    bool valid_ = false; 
    std::string errorMessage_ = ""; 
    std::string vSource_; 
    std::string fSource_; 
    std::unordered_map<std::string, ShaderParameter> parameters_; 
    std::unordered_set<std::string> updateParameters_; 
};

}
