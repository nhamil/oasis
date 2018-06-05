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

Parameter& Parameter::operator=(const Parameter& param)
{
    type_ = param.type_;

    switch (type_)
    {
    case ParameterType::INT:
        value_.Get<int>() = param.value_.Get<int>();
        break;
    case ParameterType::FLOAT:
        value_.Get<float>() = param.value_.Get<float>();
        break;
    case ParameterType::VECTOR2:
        value_.Get<Vector2>() = param.value_.Get<Vector2>();
        break;
    case ParameterType::VECTOR3:
        value_.Get<Vector3>() = param.value_.Get<Vector3>();
        break;
    case ParameterType::VECTOR4:
        value_.Get<Vector4>() = param.value_.Get<Vector4>();
        break;
    case ParameterType::MATRIX3:
        value_.Get<Matrix3>() = param.value_.Get<Matrix3>();
        break;
    case ParameterType::MATRIX4:
        value_.Get<Matrix3>() = param.value_.Get<Matrix3>();
        break;
    default: // should not happen, instead update this if new types are added
        memcpy(&value_, &param.value_, sizeof (ParameterValue));
        break;
    }

    return *this;
}

Parameter& Parameter::operator=(int value)
{
    type_ = ParameterType::INT;
    value_.Get<int>() = value;
    return *this;
}

Parameter& Parameter::operator=(float value)
{
    type_ = ParameterType::FLOAT;
    value_.Get<float>() = value;
    return *this;
}

Parameter& Parameter::operator=(double value)
{
    type_ = ParameterType::FLOAT;
    value_.Get<float>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector2& value)
{
    type_ = ParameterType::VECTOR2;
    value_.Get<Vector2>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector3& value)
{
    type_ = ParameterType::VECTOR3;
    value_.Get<Vector3>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector4& value)
{
    type_ = ParameterType::VECTOR4;
    value_.Get<Vector4>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Matrix3& value)
{
    type_ = ParameterType::MATRIX3;
    value_.Get<Matrix3>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Matrix4& value)
{
    type_ = ParameterType::MATRIX4;
    value_.Get<Matrix4>() = value;
    return *this;
}

bool Parameter::operator==(const Parameter& param) const
{
    switch (param.type_)
    {
    case ParameterType::INT: return *this == param.value_.Get<int>();
    case ParameterType::FLOAT: return *this == param.value_.Get<float>();
    case ParameterType::VECTOR2: return *this == param.value_.Get<Vector2>();
    case ParameterType::VECTOR3: return *this == param.value_.Get<Vector3>();
    case ParameterType::VECTOR4: return *this == param.value_.Get<Vector4>();
    case ParameterType::MATRIX3: return *this == param.value_.Get<Matrix3>();
    case ParameterType::MATRIX4: return *this == param.value_.Get<Matrix4>();\
    default: return memcmp(&value_, &param.value_, sizeof (ParameterValue));
    }
}

bool Parameter::operator==(int value) const
{
    return type_ == ParameterType::INT && value_.Get<int>() == value;
}

bool Parameter::operator==(float value) const
{
    return type_ == ParameterType::FLOAT && value_.Get<float>() == value;
}

bool Parameter::operator==(double value) const
{
    return type_ == ParameterType::FLOAT && value_.Get<float>() == (float)value;
}

bool Parameter::operator==(const Vector2& value) const
{
    return type_ == ParameterType::VECTOR2 && value_.Get<Vector2>() == value;
}

bool Parameter::operator==(const Vector3& value) const
{
    return type_ == ParameterType::VECTOR3 && value_.Get<Vector3>() == value;
}

bool Parameter::operator==(const Vector4& value) const
{
    return type_ == ParameterType::VECTOR4 && value_.Get<Vector4>() == value;
}

bool Parameter::operator==(const Matrix3& value) const
{
    return type_ == ParameterType::MATRIX3 && value_.Get<Matrix3>() == value;
}

bool Parameter::operator==(const Matrix4& value) const
{
    return type_ == ParameterType::MATRIX4 && value_.Get<Matrix4>() == value;
}

int Parameter::GetInt() const
{
    switch (type_)
    {
    case ParameterType::INT:
        return value_.Get<int>();
    case ParameterType::FLOAT:
        return (int) value_.Get<float>();
    default:
        return 0;
    }
}

float Parameter::GetFloat() const
{
    switch (type_)
    {
    case ParameterType::INT:
        return (float) value_.Get<int>();
    case ParameterType::FLOAT:
        return value_.Get<float>();
    default:
        return 0.0;
    }
}

const Vector2& Parameter::GetVector2() const
{
    return type_ == ParameterType::VECTOR2 ? value_.Get<Vector2>() : Vector2::ZERO;
}

const Vector3& Parameter::GetVector3() const
{
    return type_ == ParameterType::VECTOR3 ? value_.Get<Vector3>() : Vector3::ZERO;
}

const Vector4& Parameter::GetVector4() const
{
    return type_ == ParameterType::VECTOR4 ? value_.Get<Vector4>() : Vector4::ZERO;
}

const Matrix3& Parameter::GetMatrix3() const
{
    return type_ == ParameterType::MATRIX3 ? value_.Get<Matrix3>() : Matrix3::IDENTITY;
}

const Matrix4& Parameter::GetMatrix4() const
{
    return type_ == ParameterType::MATRIX4 ? value_.Get<Matrix4>() : Matrix4::IDENTITY;
}

}