#pragma once 

#include <Oasis/Oasis.h> 

using namespace Oasis; 

struct Transform : public Component  
{
    Vector3 position = Vector3::ZERO; 
    Quaternion rotation = Quaternion::AxisAngle(Vector3::UP, 0); 
    Vector3 scale = Vector3(1); 

    Matrix4 CreateMatrix() const 
    {
        return Matrix4::Translation(position) * Matrix4::FromQuaternion(rotation) * Matrix4::Scale(scale); 
    }
};

struct Velocity : public Component 
{
    Vector3 positional = Vector3::ZERO; 
    Vector3 rotational = Vector3::ZERO; 
};

struct MeshContainer : public Component 
{
    Mesh* mesh = nullptr; 
    Material* material = nullptr; 
};
