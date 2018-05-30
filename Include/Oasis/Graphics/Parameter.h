#pragma once

#include "Oasis/Oasis.h"

#include "Oasis/Math/MathUtil.h"

#include <string.h> 

namespace Oasis
{

enum ParameterType
{
    PARAMETER_INT,
    PARAMETER_FLOAT,
    PARAMETER_VECTOR2,
    PARAMETER_VECTOR3,
    PARAMETER_VECTOR4,
    PARAMETER_MATRIX3,
    PARAMETER_MATRIX4,

    PARAMETER_COUNT
};

struct OASIS_API ParameterValue
{
    char data[sizeof (Matrix4)]; 

    template <class T> 
    T& Get() const { return *(T*) data; } 

    template <class T> 
    void Set(T t) { memset(data, &t, sizeof (T)); }

    ParameterValue() {}
    ~ParameterValue() {}
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
