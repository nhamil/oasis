#include "Oasis/Graphics/Parameter.h"

#include <string.h>

namespace Oasis
{

Parameter::Parameter(const Parameter& param)
{
    *this = param;
}

Parameter::Parameter()
{
    *this = 0;
}

Parameter::Parameter(int value)
{
    *this = value;
}

Parameter::Parameter(float value)
{
    *this = value;
}

Parameter::Parameter(double value)
{
    *this = value;
}

Parameter::Parameter(const Vector2& value)
{
    *this = value;
}

Parameter::Parameter(const Vector3& value)
{
    *this = value;
}

Parameter::Parameter(const Vector4& value)
{
    *this = value;
}

Parameter::Parameter(const Matrix3& value)
{
    *this = value;
}

Parameter::Parameter(const Matrix4& value)
{
    *this = value;
}

Parameter::Parameter(ParameterType type) 
{
    type_ = type; 

    switch (type) 
    {
    case ParameterType::INT: 
        value_.intValue = 0; 
        break; 
    case ParameterType::FLOAT: 
        value_.floatValue = 0; 
        break; 
    case ParameterType::VECTOR2: 
        value_.vec2Value = 0; 
        break; 
    case ParameterType::VECTOR3: 
        value_.vec3Value = 0; 
        break; 
    case ParameterType::VECTOR4: 
        value_.vec4Value = 0; 
        break; 
    case ParameterType::MATRIX3: 
        value_.mat3Value = 0; 
        break; 
    case ParameterType::MATRIX4: 
        value_.mat4Value = 0; 
        break; 
    default: 
        type = ParameterType::UNKNOWN; 
        value_.mat4Value = 0; 
    }
}

Parameter& Parameter::operator=(const Parameter& param)
{
    type_ = param.type_;

    switch (type_)
    {
    case ParameterType::INT:
        value_.intValue = param.value_.intValue;
        break;
    case ParameterType::FLOAT:
        value_.floatValue = param.value_.floatValue;
        break;
    case ParameterType::VECTOR2:
        value_.vec2Value = param.value_.vec2Value;
        break;
    case ParameterType::VECTOR3:
        value_.vec3Value = param.value_.vec3Value;
        break;
    case ParameterType::VECTOR4:
        value_.vec4Value = param.value_.vec4Value;
        break;
    case ParameterType::MATRIX3:
        value_.mat3Value = param.value_.mat3Value;
        break;
    case ParameterType::MATRIX4:
        value_.mat4Value = param.value_.mat4Value;
        break;
    case ParameterType::UNKNOWN: 
    default: // should not happen, instead update this if new types are added
        memcpy(&value_, &param.value_, sizeof (ParameterValue));
        break;
    }

    return *this;
}

Parameter& Parameter::operator=(int value)
{
    type_ = ParameterType::INT;
    value_.intValue = value;
    return *this;
}

Parameter& Parameter::operator=(float value)
{
    type_ = ParameterType::FLOAT;
    value_.floatValue = value;
    return *this;
}

Parameter& Parameter::operator=(double value)
{
    type_ = ParameterType::FLOAT;
    value_.floatValue = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector2& value)
{
    type_ = ParameterType::VECTOR2;
    value_.vec2Value = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector3& value)
{
    type_ = ParameterType::VECTOR3;
    value_.vec3Value = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector4& value)
{
    type_ = ParameterType::VECTOR4;
    value_.vec4Value = value;
    return *this;
}

Parameter& Parameter::operator=(const Matrix3& value)
{
    type_ = ParameterType::MATRIX3;
    value_.mat3Value = value;
    return *this;
}

Parameter& Parameter::operator=(const Matrix4& value)
{
    type_ = ParameterType::MATRIX4;
    value_.mat4Value = value;
    return *this;
}

bool Parameter::operator==(const Parameter& param) const
{
    switch (param.type_)
    {
    case ParameterType::INT: return *this == param.value_.intValue;
    case ParameterType::FLOAT: return *this == param.value_.floatValue;
    case ParameterType::VECTOR2: return *this == param.value_.vec2Value;
    case ParameterType::VECTOR3: return *this == param.value_.vec3Value;
    case ParameterType::VECTOR4: return *this == param.value_.vec4Value;
    case ParameterType::MATRIX3: return *this == param.value_.mat3Value;
    case ParameterType::MATRIX4: return *this == param.value_.mat4Value; 
    default: return memcmp(&value_, &param.value_, sizeof (ParameterValue));
    }
}

bool Parameter::operator==(int value) const
{
    return type_ == ParameterType::INT && value_.intValue == value;
}

bool Parameter::operator==(float value) const
{
    return type_ == ParameterType::FLOAT && value_.floatValue == value;
}

bool Parameter::operator==(double value) const
{
    return type_ == ParameterType::FLOAT && value_.floatValue == (float)value;
}

bool Parameter::operator==(const Vector2& value) const
{
    return type_ == ParameterType::VECTOR2 && value_.vec2Value == value;
}

bool Parameter::operator==(const Vector3& value) const
{
    return type_ == ParameterType::VECTOR3 && value_.vec3Value == value;
}

bool Parameter::operator==(const Vector4& value) const
{
    return type_ == ParameterType::VECTOR4 && value_.vec4Value == value;
}

bool Parameter::operator==(const Matrix3& value) const
{
    return type_ == ParameterType::MATRIX3 && value_.mat3Value == value;
}

bool Parameter::operator==(const Matrix4& value) const
{
    return type_ == ParameterType::MATRIX4 && value_.mat4Value == value;
}

int Parameter::GetInt() const
{
    switch (type_)
    {
    case ParameterType::INT:
        return value_.intValue;
    case ParameterType::FLOAT:
        return (int) value_.floatValue;
    default:
        return 0;
    }
}

float Parameter::GetFloat() const
{
    switch (type_)
    {
    case ParameterType::INT:
        return (float) value_.intValue;
    case ParameterType::FLOAT:
        return value_.floatValue;
    default:
        return 0.0;
    }
}

const Vector2& Parameter::GetVector2() const
{
    return type_ == ParameterType::VECTOR2 ? value_.vec2Value : Vector2::ZERO;
}

const Vector3& Parameter::GetVector3() const
{
    return type_ == ParameterType::VECTOR3 ? value_.vec3Value : Vector3::ZERO;
}

const Vector4& Parameter::GetVector4() const
{
    return type_ == ParameterType::VECTOR4 ? value_.vec4Value : Vector4::ZERO;
}

const Matrix3& Parameter::GetMatrix3() const
{
    return type_ == ParameterType::MATRIX3 ? value_.mat3Value : Matrix3::IDENTITY;
}

const Matrix4& Parameter::GetMatrix4() const
{
    return type_ == ParameterType::MATRIX4 ? value_.mat4Value : Matrix4::IDENTITY;
}

}
