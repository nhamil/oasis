#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/GraphicsResource.h" 
#include "Oasis/Graphics/Parameter.h" 
#include "Oasis/Math/MathUtil.h" 

namespace Oasis
{

class OASIS_API Shader : public GraphicsResource 
{
public:
    void Update(); 

    inline bool IsValid() const { return valid_; } 

    inline const std::string& GetErrorMessage() const { return errorMessage_; } 

    inline const std::string& GetVertexSource() const { return vSource_; }
    inline const std::string& GetFragmentSource() const { return fSource_; } 

    void ClearParameter(const std::string& name); 
    void SetParameter(const std::string& name, const Parameter& value); 

    inline void SetParameterInt(const std::string& name, int value) { SetParameter(name, Parameter(value)); } 
    inline void SetParameterFloat(const std::string& name, float value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterVector2(const std::string& name, const Vector2& value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterVector3(const std::string& name, const Vector3& value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterVector4(const std::string& name, const Vector4& value) { SetParameter(name, Parameter(value)); } 
    inline void SetParameterMatrix3(const std::string& name, const Matrix3& value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterMatrix4(const std::string& name, const Matrix4& value) { SetParameter(name, Parameter(value)); }  

private: 
    friend class Graphics; 

    Shader(const std::string& vSource, const std::string& fSource); 
    ~Shader(); 

    OASIS_NO_COPY(Shader) 

    bool valid_ = false; 
    std::string errorMessage_; 
    std::string vSource_; 
    std::string fSource_; 
    std::unordered_map<std::string, Parameter> parameters_; 
};

}
