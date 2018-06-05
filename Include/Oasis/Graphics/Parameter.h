#pragma once

#include "Oasis/Common.h"

#include "Oasis/Math/MathUtil.h"

#include <string.h> 

namespace Oasis
{

enum class ParameterType
{
    INT,
    FLOAT,
    VECTOR2,
    VECTOR3,
    VECTOR4,
    MATRIX3,
    MATRIX4,

    count
};

union OASIS_API ParameterValue
{
    int intValue; 
    float floatValue; 
    Vector2 vec2Value; 
    Vector3 vec3Value; 
    Vector4 vec4Value; 
    Matrix3 mat3Value; 
    Matrix4 mat4Value; 

    ParameterValue() { intValue = 0; } 
};

class OASIS_API Parameter
{
public:
    Parameter(const Parameter& param);
    Parameter();
    Parameter(int value);
    Parameter(float value);
    Parameter(double value);
    Parameter(const Vector2& value);
    Parameter(const Vector3& value);
    Parameter(const Vector4& value);
    Parameter(const Matrix3& value);
    Parameter(const Matrix4& value);
    ~Parameter() {}

    Parameter& operator=(const Parameter& param);
    Parameter& operator=(int value);
    Parameter& operator=(float value);
    Parameter& operator=(double value);
    Parameter& operator=(const Vector2& value);
    Parameter& operator=(const Vector3& value);
    Parameter& operator=(const Vector4& value);
    Parameter& operator=(const Matrix3& value);
    Parameter& operator=(const Matrix4& value);

    bool operator==(const Parameter& param) const;
    bool operator==(int value) const;
    bool operator==(float value) const;
    bool operator==(double value) const;
    bool operator==(const Vector2& value) const;
    bool operator==(const Vector3& value) const;
    bool operator==(const Vector4& value) const;
    bool operator==(const Matrix3& value) const;
    bool operator==(const Matrix4& value) const;

    bool operator!=(const Parameter& param) const { return !(*this == param); }
    bool operator!=(int value) const { return !(*this == value); }
    bool operator!=(float value) const { return !(*this == value); }
    bool operator!=(double value) const { return !(*this == value); }
    bool operator!=(const Vector2& value) const { return !(*this == value); }
    bool operator!=(const Vector3& value) const { return !(*this == value); }
    bool operator!=(const Vector4& value) const { return !(*this == value); }
    bool operator!=(const Matrix3& value) const { return !(*this == value); }
    bool operator!=(const Matrix4& value) const { return !(*this == value); }

    ParameterType GetType() const { return type_; }

    int GetInt() const;
    float GetFloat() const;
    const Vector2& GetVector2() const;
    const Vector3& GetVector3() const;
    const Vector4& GetVector4() const;
    const Matrix3& GetMatrix3() const;
    const Matrix4& GetMatrix4() const;

private:
    ParameterType type_;
    ParameterValue value_;
};

}
