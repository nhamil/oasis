#include "Oasis/Scene/System.h" 

#include "Oasis/Scene/Scene.h" 

namespace Oasis 
{

const int EntitySystem::DEFAULT_PRIORITY = 1000; 

EntitySystem::EntitySystem(int priority) 
{
    priority_ = priority; 
} 

EntitySystem::EntitySystem() {}

EntitySystem::~EntitySystem() 
{

}

EntityManager* EntitySystem::GetEntityManager() 
{
    if (scene_) return &scene_->GetEntityManager(); 
    else return nullptr; 
}

void EntitySystem::OnUpdate(EntityManager* entityManager, uint32 count, EntityId* entities, float dt) 
{
    (void) entityManager; 
    (void) count; 
    (void) entities; 
    (void) dt; 
}

void EntitySystem::OnRender(EntityManager* entityManager, uint32 count, EntityId* entities) 
{
    (void) entityManager; 
    (void) count; 
    (void) entities; 
}

void EntitySystem::Update(float dt) 
{
    OnUpdate(nullptr, 0, nullptr, dt); 
}

void EntitySystem::Render() 
{
    OnRender(nullptr, 0, nullptr); 
}

void EntitySystem::SetScene(Scene* scene) 
{
    if (scene) 
    {
        if (scene_) OnRemoved(); 

        scene_ = scene; 
        OnAdded(); 
    }
    else 
    {
        if (scene_) OnRemoved(); 

        scene_ = nullptr; 
    }
}

}