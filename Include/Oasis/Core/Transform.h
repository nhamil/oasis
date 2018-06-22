#pragma once

#include "Oasis/Common.h"

#include "Oasis/Math/MathUtil.h"

namespace Oasis
{

class OASIS_API Transform
{
public:
    const Vector3& GetPosition() const { return position_; }
    Vector3& GetPosition() { return position_; }

    const Quaternion& GetRotation() const { return rotation_; }
    Quaternion& GetRotation() { return rotation_; }

    const Vector3& GetScale() const { return scale_; }
    Vector3& GetScale() { return scale_; }

    Matrix4 GetModelMatrix() const
    {
        Matrix4 m = Matrix4::Translation(position_);
        m *= Matrix4::FromQuaternion(rotation_);
        m *= Matrix4::Scale(scale_);
        return m;
    }

private:
    Vector3 position_ = Vector3::ZERO;
    Quaternion rotation_ = Quaternion::AxisAngle(Vector3::Up, 0);
    Vector3 scale_ = Vector3(1);
};

}
