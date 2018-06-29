#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Entity.h" 
#include "Oasis/Scene/Filter.h" 

namespace Oasis 
{

class Entity; 
struct EntityId; 
class EntityManager; 

class OASIS_API EntityFilterCache 
{
public: 
    EntityFilterCache(EntityManager* manager); 

    uint32 GetId(const EntityFilter& filter); 

    bool ReleaseId(uint32 id); 

    void GetEntities(uint32 filterId, int* count, Entity** entities) const; 

private: 
    struct Entry 
    {
        int count = 0; 
        EntityFilter filter; 
        std::vector<Entity> entities; 
    };

    void OnCreateEntity(const EntityId& id); 
    void OnUpdateEntity(const EntityId& id); 
    void OnDestroyEntity(const EntityId& id); 

    std::vector<Entry> entries_; 
    IdManager32 ids_; 
    EntityManager* entityManager_; 
};

}