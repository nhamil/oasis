#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/ComponentPool.h" 
#include "Oasis/Scene/EntityId.h" 
#include "Oasis/Scene/FilterCache.h" 

namespace Oasis 
{

class OASIS_API EntityManager 
{
public: 
    EntityManager(); 
    ~EntityManager(); 

    inline EntityFilterCache& GetFilterCache() { return filterCache_; } 

    EntityId CreateEntityId(); 
    bool DestroyEntityId(const EntityId&); 

    bool IsValidEntityId(const EntityId& id) const; 

    bool HasComponent(const EntityId& id, ClassId compId) const; 

    template <class T> 
    bool HasComponent(const EntityId& id) 
    {
        return HasComponent(id, GetClassId<T>()); 
    }

    template <class T> 
    T* GetComponent(const EntityId& id) 
    {
        CheckComponentPool<T>(); 
        return (T*) GetComponent(id, GetClassId<T>()); 
    }

    template <class T, class ... Args> 
    T* AttachComponent(const EntityId& id, Args... args) 
    {
        CheckComponentPool<T>(); 
        return (T*) AttachComponent(id, GetClassId<T>(), T(args...)); 
    }

    template <class T> 
    bool DetachComponent(const EntityId& id) 
    {
        return DetachComponent(id, GetClassId<T>()); 
    }

private: 
    using ComponentEntry = std::pair<ClassId, uint32>; 

    struct EntityEntry 
    {
        bool valid = false; 
        uint32 version = 0; 
        std::vector<ComponentEntry> components; 

        void OnCreate() 
        {
            version++; 
            valid = true; 
        }

        void OnDestroy() 
        {
            components.clear(); 
            valid = false; 
        }
    }; 

    template <class T>
    void CheckComponentPool() 
    {
        if (!componentPools_[GetClassId<T>()]) 
        {
            componentPools_[GetClassId<T>()] = new ComponentPool<T>(); 
        }
    }

    bool IdInBounds(uint32 id) const; 

    int FindComponentIndex(uint32 entityId, ClassId compId) const; 

    Component* GetComponent(const EntityId& id, ClassId compId); 

    Component* AttachComponent(const EntityId& id, ClassId compId, const Component& from); 

    bool DetachComponent(const EntityId& id, ClassId compId); 

    std::vector<EntityEntry> entities_; 
    std::unordered_map<ClassId, ComponentPoolBase*> componentPools_; 
    IdManager32 ids_; 
    EntityFilterCache filterCache_; 
}; 

}