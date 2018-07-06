#include "Oasis/Math/MathUtil.h"

namespace Oasis
{

const Vector2 Vector2::ZERO(0, 0);
const Vector2 Vector2::UP(0, 1); 
const Vector2 Vector2::DOWN(0, -1);
const Vector2 Vector2::LEFT(-1, 0);
const Vector2 Vector2::RIGHT(1, 0);

const Vector3 Vector3::ZERO(0, 0, 0);
const Vector3 Vector3::UP(0, 1, 0);
const Vector3 Vector3::DOWN(0, -1, 0);
const Vector3 Vector3::LEFT(-1, 0, 0);
const Vector3 Vector3::RIGHT(1, 0, 0);
const Vector3 Vector3::FORWARD(1, 0, 0);
const Vector3 Vector3::BACKWARD(-1, 0, 0);

const Vector4 Vector4::ZERO(0, 0, 0, 0);

const Matrix3 Matrix3::ZERO(0);
const Matrix3 Matrix3::IDENTITY = Matrix3::Identity();

const Matrix4 Matrix4::ZERO(0);
const Matrix4 Matrix4::IDENTITY = Matrix4::Identity();

}
