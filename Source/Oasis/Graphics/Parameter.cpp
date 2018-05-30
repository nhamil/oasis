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
    m_type = param.m_type;

    switch (m_type)
    {
    case PARAMETER_INT:
        m_value.Get<int>() = param.m_value.Get<int>();
        break;
    case PARAMETER_FLOAT:
        m_value.Get<float>() = param.m_value.Get<float>();
        break;
    case PARAMETER_VECTOR2:
        m_value.Get<Vector2>() = param.m_value.Get<Vector2>();
        break;
    case PARAMETER_VECTOR3:
        m_value.Get<Vector3>() = param.m_value.Get<Vector3>();
        break;
    case PARAMETER_VECTOR4:
        m_value.Get<Vector4>() = param.m_value.Get<Vector4>();
        break;
    case PARAMETER_MATRIX3:
        m_value.Get<Matrix3>() = param.m_value.Get<Matrix3>();
        break;
    case PARAMETER_MATRIX4:
        m_value.Get<Matrix3>() = param.m_value.Get<Matrix3>();
        break;
    default: // should not happen, instead update this if new types are added
        memcpy(&m_value, &param.m_value, sizeof (ParameterValue));
        break;
    }

    return *this;
}

Parameter& Parameter::operator=(int value)
{
    m_type = PARAMETER_INT;
    m_value.Get<int>() = value;
    return *this;
}

Parameter& Parameter::operator=(float value)
{
    m_type = PARAMETER_FLOAT;
    m_value.Get<float>() = value;
    return *this;
}

Parameter& Parameter::operator=(double value)
{
    m_type = PARAMETER_FLOAT;
    m_value.Get<float>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector2& value)
{
    m_type = PARAMETER_VECTOR2;
    m_value.Get<Vector2>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector3& value)
{
    m_type = PARAMETER_VECTOR3;
    m_value.Get<Vector3>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Vector4& value)
{
    m_type = PARAMETER_VECTOR4;
    m_value.Get<Vector4>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Matrix3& value)
{
    m_type = PARAMETER_MATRIX3;
    m_value.Get<Matrix3>() = value;
    return *this;
}

Parameter& Parameter::operator=(const Matrix4& value)
{
    m_type = PARAMETER_MATRIX4;
    m_value.Get<Matrix4>() = value;
    return *this;
}

bool Parameter::operator==(const Parameter& param) const
{
    switch (param.m_type)
    {
    case PARAMETER_INT: return *this == param.m_value.Get<int>();
    case PARAMETER_FLOAT: return *this == param.m_value.Get<float>();
    case PARAMETER_VECTOR2: return *this == param.m_value.Get<Vector2>();
    case PARAMETER_VECTOR3: return *this == param.m_value.Get<Vector3>();
    case PARAMETER_VECTOR4: return *this == param.m_value.Get<Vector4>();
    case PARAMETER_MATRIX3: return *this == param.m_value.Get<Matrix3>();
    case PARAMETER_MATRIX4: return *this == param.m_value.Get<Matrix4>();\
    default: return memcmp(&m_value, &param.m_value, sizeof (ParameterValue));
    }
}

bool Parameter::operator==(int value) const
{
    return m_type == PARAMETER_INT && m_value.Get<int>() == value;
}

bool Parameter::operator==(float value) const
{
    return m_type == PARAMETER_FLOAT && m_value.Get<float>() == value;
}

bool Parameter::operator==(double value) const
{
    return m_type == PARAMETER_FLOAT && m_value.Get<float>() == (float)value;
}

bool Parameter::operator==(const Vector2& value) const
{
    return m_type == PARAMETER_VECTOR2 && m_value.Get<Vector2>() == value;
}

bool Parameter::operator==(const Vector3& value) const
{
    return m_type == PARAMETER_VECTOR3 && m_value.Get<Vector3>() == value;
}

bool Parameter::operator==(const Vector4& value) const
{
    return m_type == PARAMETER_VECTOR4 && m_value.Get<Vector4>() == value;
}

bool Parameter::operator==(const Matrix3& value) const
{
    return m_type == PARAMETER_MATRIX3 && m_value.Get<Matrix3>() == value;
}

bool Parameter::operator==(const Matrix4& value) const
{
    return m_type == PARAMETER_MATRIX4 && m_value.Get<Matrix4>() == value;
}

int Parameter::GetInt() const
{
    switch (m_type)
    {
    case PARAMETER_INT:
        return m_value.Get<int>();
    case PARAMETER_FLOAT:
        return (int) m_value.Get<float>();
    default:
        return 0;
    }
}

float Parameter::GetFloat() const
{
    switch (m_type)
    {
    case PARAMETER_INT:
        return (float) m_value.Get<int>();
    case PARAMETER_FLOAT:
        return m_value.Get<float>();
    default:
        return 0.0;
    }
}

const Vector2& Parameter::GetVector2() const
{
    return m_type == PARAMETER_VECTOR2 ? m_value.Get<Vector2>() : Vector2::ZERO;
}

const Vector3& Parameter::GetVector3() const
{
    return m_type == PARAMETER_VECTOR3 ? m_value.Get<Vector3>() : Vector3::ZERO;
}

const Vector4& Parameter::GetVector4() const
{
    return m_type == PARAMETER_VECTOR4 ? m_value.Get<Vector4>() : Vector4::ZERO;
}

const Matrix3& Parameter::GetMatrix3() const
{
    return m_type == PARAMETER_MATRIX3 ? m_value.Get<Matrix3>() : Matrix3::IDENTITY;
}

const Matrix4& Parameter::GetMatrix4() const
{
    return m_type == PARAMETER_MATRIX4 ? m_value.Get<Matrix4>() : Matrix4::IDENTITY;
}

}
