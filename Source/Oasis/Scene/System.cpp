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

EntitySystem::~EntitySystem() {}

void EntitySystem::OnUpdate(Scene& scene, uint32 count, const EntityId* entities, float dt) 
{
    (void) scene; 
    (void) count; 
    (void) entities; 
    (void) dt; 
}

void EntitySystem::OnRender(Scene& scene, uint32 count, const EntityId* entities) 
{
    (void) scene; 
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
        OnUpdate(*scene_, count, entities, dt); 
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
        OnRender(*scene_, count, entities); 
        fc.Unlock(); 
    }
}

void EntitySystem::SetScene(Scene* newScene) 
{
    if (newScene) 
    {
        if (scene_) 
        {
            OnRemoved(); 
            scene_->GetEntityManager().GetFilterCache().ReleaseFilterId(filterId_); 
            filterId_ = 0; 
        }

        scene_ = newScene; 
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