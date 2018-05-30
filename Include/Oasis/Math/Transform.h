#pragma once

#include "Oasis/Oasis.h"

#include "MathUtil.h"

namespace Oasis
{

class OASIS_API Transform
{
public:
    Transform() : position_(0), rotation_(Quaternion::AxisAngle({0, 1, }, 0)), scale_(1) {}
    ~Transform() {}

    const Vector3& GetPosition() const { return position_; }
    Vector3& GetPosition() { return position_; }

    const Quaternion& GetRotation() const { return rotation_; }
    Quaternion& GetRotation() { return rotation_; }

    const Vector3& GetScale() const { return scale_; }
    Vector3& GetScale() { return scale_; }

    Matrix4 GetMatrix() const { return Matrix4::Translation(position_) * Matrix4::FromQuaternion(rotation_) * Matrix4::Scale(scale_); }

private:
    Vector3 position_;
    Quaternion rotation_;
    Vector3 scale_;
};

}
