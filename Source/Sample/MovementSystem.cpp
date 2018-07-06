#include "Sample/MovementSystem.h" 

MovementSystem::MovementSystem() 
{
    Include<Transform>(); 
    Include<Velocity>(); 
}

void MovementSystem::OnUpdate(Scene& scene, uint32 count, const EntityId* entities, float dt) 
{
    for (uint32 i = 0; i < count; i++) 
    {
        Entity e = scene.GetEntity(entities[i]); 

        Transform& t = *e.Get<Transform>(); 
        Velocity& v = *e.Get<Velocity>(); 

        t.position += v.positional * dt; 
        t.rotation = Quaternion::AxisAngle(Vector3::RIGHT, v.rotational.x * dt) * t.rotation; 
        t.rotation = Quaternion::AxisAngle(Vector3::UP, v.rotational.y * dt) * t.rotation; 
        t.rotation = Quaternion::AxisAngle(Vector3::FORWARD, v.rotational.z * dt) * t.rotation; 
    }
}