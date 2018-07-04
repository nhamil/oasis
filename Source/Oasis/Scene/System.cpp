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

void EntitySystem::OnUpdate(EntityManager* entityManager, uint32 count, const EntityId* entities, float dt) 
{
    (void) entityManager; 
    (void) count; 
    (void) entities; 
    (void) dt; 
}

void EntitySystem::OnRender(EntityManager* entityManager, uint32 count, const EntityId* entities) 
{
    (void) entityManager; 
    (void) count; 
    (void) entities; 
}

void EntitySystem::Update(float dt) 
{
    if (scene_) 
    {
        EntityManager& em = scene_->GetEntityManager(); 
        EntityFilterCache& fc = em.GetFilterCache(); 
        uint32 count; 
        const EntityId* entities; 
        fc.GetEntities(filterId_, count, entities); 
        
        fc.Lock(); 
        OnUpdate(&em, count, entities, dt); 
        fc.Unlock(); 
    }
}

void EntitySystem::Render() 
{
    if (scene_) 
    {
        EntityManager& em = scene_->GetEntityManager(); 
        EntityFilterCache& fc = em.GetFilterCache(); 
        uint32 count; 
        const EntityId* entities; 
        fc.GetEntities(filterId_, count, entities); 
        
        fc.Lock(); 
        OnRender(&em, count, entities); 
        fc.Unlock(); 
    }
}

void EntitySystem::SetScene(Scene* scene) 
{
    if (scene) 
    {
        if (scene_) 
        {
            OnRemoved(); 
            scene_->GetEntityManager().GetFilterCache().ReleaseFilterId(filterId_); 
            filterId_ = 0; 
        }

        scene_ = scene; 
        filterId_ = scene_->GetEntityManager().GetFilterCache().GetFilterId(filter_); 
        OnAdded(); 
    }
    else 
    {
        if (scene_) 
        {
            OnRemoved(); 
            scene_->GetEntityManager().GetFilterCache().ReleaseFilterId(filterId_); 
            filterId_ = 0; 
        }

        scene_ = nullptr; 
    }
}

}