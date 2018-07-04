#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/EntityId.h" 
#include "Oasis/Scene/Filter.h" 
#include "Oasis/Util/IdManager.h" 

namespace Oasis 
{

class EntityManager; 

class OASIS_API EntityFilterCache 
{
public: 
    EntityFilterCache(EntityManager* manager); 

    uint32 GetFilterId(const EntityFilter& filter); 

    bool ReleaseFilterId(uint32 id); 

    void GetEntities(uint32 filterId, uint32* count, EntityId** entities) const; 

    void Lock(); 

    void Unlock(); 

private: 
    friend class EntityManager; 

    struct Entry 
    {
        int count = 0; 
        EntityFilter filter; 
        std::vector<EntityId> entities; 
    };

    enum class EntityEventType 
    {
        CREATE, 
        DESTROY, 
        ADD_COMPONENT, 
        REMOVE_COMPONENT, 
        count
    };

    struct EntityEvent 
    {
        EntityEvent() {} 
        EntityEvent(EntityId id, EntityEventType type) : id(id), eventType(type) {} 
        EntityEvent(EntityId id, EntityEventType type, ClassId compId) : id(id), eventType(type), componentId(compId) {} 

        EntityId id; 
        EntityEventType eventType; 
        ClassId componentId; 
    };

    void OnCreateEntity(const EntityId& id); 
    void OnAddEntityComponent(const EntityId& id, ClassId compId); 
    void OnRemoveEntityComponent(const EntityId& id, ClassId compId); 
    void OnDestroyEntity(const EntityId& id); 

    void OnCreateEntityNoLock(const EntityId& id); 
    void OnAddEntityComponentNoLock(const EntityId& id, ClassId compId); 
    void OnRemoveEntityComponentNoLock(const EntityId& id, ClassId compId); 
    void OnDestroyEntityNoLock(const EntityId& id); 

    std::vector<EntityEvent> eventBuffer_; 
    std::vector<Entry> entries_; 
    IdManager32 ids_; 
    EntityManager* entityManager_; 
    bool lock_ = false; 
};

}