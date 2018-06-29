#include "Oasis/Scene/EntityManager.h" 

namespace Oasis
{

EntityManager::EntityManager() {}

EntityManager::~EntityManager() 
{
    // TODO 
    for (auto it = componentPools_.begin(); it != componentPools_.end(); it++) 
    {
        delete it->second; 
    }
    componentPools_.clear(); 
}

EntityId EntityManager::CreateEntityId() 
{
    uint32 id = ids_.Get(); 

    if (id == entities_.size()) 
    {
        entities_.push_back(EntityEntry()); 
    }

    entities_[id].OnCreate(); 

    return EntityId(id, entities_[id].version); 
}

bool EntityManager::DestroyEntityId(const EntityId& id) 
{
    if (!IdInBounds(id.id)) return false; 

    EntityEntry& entity = entities_[id.id]; 

    if (!entity.valid || entity.version != id.version) return false; 

    for (unsigned i = 0; i < entity.components.size(); i++) 
    {
        auto& pair = entity.components[i]; 
        componentPools_[pair.first]->DestroyComponent(pair.second); 
    }

    entity.OnDestroy(); 
    return true; 
}

bool EntityManager::IsValidId(const EntityId& id) const 
{
    // id in bounds 
    if (!IdInBounds(id.id)) return false; 

    const EntityEntry& entity = entities_[id.id]; 

    // entity still valid for id
    return entity.valid && entity.version == id.version; 
}

bool EntityManager::HasComponent(const EntityId& id, ClassId compId) const 
{
    // id in bounds 
    if (!IdInBounds(id.id)) return false; 

    const EntityEntry& entity = entities_[id.id]; 

    // entity still valid for id
    if (!entity.valid || entity.version != id.version) return false; 

    return FindComponentIndex(id.id, compId) != -1; 
}

Component* EntityManager::GetComponent(const EntityId& id, ClassId compId) 
{
    // id in bounds 
    if (!IdInBounds(id.id)) return nullptr; 

    EntityEntry& entity = entities_[id.id]; 

    // entity still valid for id
    if (!entity.valid || entity.version != id.version) return nullptr; 

    int index = FindComponentIndex(id.id, compId); 

    // check entity has component 
    if (index == -1) return nullptr; 

    uint32 poolIndex = entity.components[index].second; 
    ComponentPoolBase* pool = componentPools_[compId];

    return pool->GetComponent(poolIndex); 
}

Component* EntityManager::AttachComponent(const EntityId& id, ClassId compId, const Component* from) 
{
    // id in bounds 
    if (!IdInBounds(id.id)) return nullptr; 

    EntityEntry& entity = entities_[id.id]; 

    // entity still valid for id
    if (!entity.valid || entity.version != id.version) return nullptr; 

    int index = FindComponentIndex(id.id, compId); 

    ComponentPoolBase* pool = componentPools_[compId]; 

    // check entity has component 
    if (index != -1) 
    {
        // entity already has component 
        uint32& poolIndex = entity.components[index].second; 
        pool->DestroyComponent(poolIndex); 

        poolIndex = pool->CreateComponent(from); 

        return pool->GetComponent(poolIndex); 
    }
    else 
    {
        uint32 newPoolIndex = pool->CreateComponent(from); 
        entity.components.push_back(std::make_pair(compId, newPoolIndex)); 

        return pool->GetComponent(newPoolIndex); 
    }
}

bool EntityManager::DetachComponent(const EntityId& id, ClassId compId) 
{
    // id in bounds
    if (!IdInBounds(id.id)) return false; 
 
    EntityEntry& entity = entities_[id.id]; 

    // entity still valid for id
    if (!entity.valid || entity.version != id.version) return false; 

    int index = FindComponentIndex(id.id, compId); 

    // check entity has component 
    if (index == -1) return false; 

    uint32 poolIndex = entity.components[index].second; 
    ComponentPoolBase* pool = componentPools_[compId];

    pool->DestroyComponent(poolIndex); 

    entity.components[index] = entity.components[entity.components.size() - 1]; 
    entity.components.pop_back(); 

    return false; 
}

bool EntityManager::IdInBounds(uint32 id) const 
{
    return id < ids_.Size(); 
}

int EntityManager::FindComponentIndex(uint32 entityId, ClassId compId) const  
{
    auto& list = entities_[entityId].components; 

    for (unsigned i = 0; i < list.size(); i++) 
    {
        if (list[i].first == compId) return i; 
    }

    return -1; 
}

}