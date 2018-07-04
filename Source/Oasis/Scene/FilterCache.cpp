#include "Oasis/Scene/FilterCache.h" 

#include "Oasis/Scene/EntityManager.h" 

namespace Oasis 
{

EntityFilterCache::EntityFilterCache(EntityManager* manager) 
    : entityManager_(manager) 
{

}

uint32 EntityFilterCache::GetFilterId(const EntityFilter& filter) 
{
    // TODO search existing entries to see if there is
    // equivalent filter 
    uint32 id = ids_.Get(); 

    if (id >= entries_.size()) 
    {
        entries_.push_back(Entry(filter)); 
    }
    else 
    {
        entries_[id] = Entry(filter); 
    }

    return id; 
}

bool EntityFilterCache::ReleaseFilterId(uint32 id) 
{
    if (ids_.IsValid(id)) 
    {
        Entry& e = entries_[id]; 

        e.count--; 

        if (e.count == 0) 
        {
            e.entities.clear(); 
            ids_.Release(id); 

            return true; 
        }
        else return false; 
    }
    else return false;  
}

void EntityFilterCache::GetEntities(uint32 filterId, uint32& count, const EntityId*& entities) const 
{
    if (ids_.IsValid(filterId)) 
    {
        const Entry& e = entries_[filterId]; 

        count = e.entities.size(); 
        if (count) 
        {
            entities = &e.entities[0]; 
        }
        else 
        {
            entities = nullptr; 
        }
    }
    else 
    {
        count = 0; 
        entities = nullptr; 
    }
}

void EntityFilterCache::Lock() 
{
    lock_ = true; 
}

void EntityFilterCache::Unlock() 
{
    lock_ = false; 

    for (auto& event : eventBuffer_) 
    {
        switch (event.eventType) 
        {
        case EntityEventType::CREATE: 
            OnCreateEntityNoLock(event.id); 
            break; 
        case EntityEventType::DESTROY: 
            OnDestroyEntityNoLock(event.id); 
            break; 
        case EntityEventType::ADD_COMPONENT: 
            OnAddEntityComponentNoLock(event.id, event.componentId); 
            break; 
        case EntityEventType::REMOVE_COMPONENT: 
            OnRemoveEntityComponentNoLock(event.id, event.componentId); 
            break; 
        default: 
            Logger::Warning("FilterCache: Unknown Event Type: ", (int) event.eventType); 
        }
    }

    eventBuffer_.clear(); 
}

void EntityFilterCache::OnCreateEntity(const EntityId& id) 
{
    if (lock_) 
    {
        eventBuffer_.push_back({id, EntityEventType::CREATE}); 
    }
    else 
    {
        OnCreateEntityNoLock(id); 
    }
}

void EntityFilterCache::OnDestroyEntity(const EntityId& id) 
{
    if (lock_) 
    {
        eventBuffer_.push_back({id, EntityEventType::DESTROY}); 
    }
    else 
    {
        OnDestroyEntityNoLock(id); 
    }
}

void EntityFilterCache::OnAddEntityComponent(const EntityId& id, ClassId compId) 
{
    if (lock_) 
    {
        eventBuffer_.push_back({id, EntityEventType::ADD_COMPONENT, compId}); 
    }
    else 
    {
        OnAddEntityComponentNoLock(id, compId); 
    }
}

void EntityFilterCache::OnRemoveEntityComponent(const EntityId& id, ClassId compId) 
{
    if (lock_) 
    {
        eventBuffer_.push_back({id, EntityEventType::REMOVE_COMPONENT, compId}); 
    }
    else 
    {
        OnRemoveEntityComponentNoLock(id, compId); 
    }
}

void EntityFilterCache::OnCreateEntityNoLock(const EntityId& id) 
{
    for (auto& entry : entries_) 
    {
        if (!entry.count) continue; 

        if (entry.filter.Matches(*entityManager_, id)) 
        {
            // Logger::Debug("FilterCache: Adding ID: ", id.id); 
            entry.entities.push_back(id); 
        }
    }
}

void EntityFilterCache::OnDestroyEntityNoLock(const EntityId& id) 
{
    for (auto& entry : entries_) 
    {
        if (!entry.count) continue; 

        auto& list = entry.entities; 

        for (unsigned i = 0; i < list.size(); i++) 
        {
            if (list[i] == id) 
            {
                list[i] = list.back(); 
                list.pop_back(); 
                break; 
            }
        }
        // Logger::Debug("FilterCache: Removing ID: ", id.id); 
    }
}

void EntityFilterCache::OnAddEntityComponentNoLock(const EntityId& id, ClassId compId) 
{
    for (auto& entry : entries_) 
    {
        if (!entry.count) continue; 
        // TODO 
        auto& filter = entry.filter; 

        bool match = filter.Matches(*entityManager_, id); 

        if (match && filter.Includes(compId)) 
        {
            // added component must be included to match filter 

            // add id 
            entry.entities.push_back(id); 
            // Logger::Debug("FilterCache: Adding ID (Add Component): ", id.id); 
        }
        else if (!match && filter.MatchesWithout(*entityManager_, id, compId)) 
        {
            // added component must be excluded to match filter 

            // remove id 
            auto& list = entry.entities; 
            for (unsigned i = 0; i < list.size(); i++) 
            {
                if (list[i] == id) 
                {
                    list[i] = list.back(); 
                    list.pop_back(); 
                    break; 
                }
            }
            // Logger::Debug("FilterCache: Removing ID (Add Component): ", id.id); 
        }

        // else do nothing, it is already either in or not in list 
    }
}

void EntityFilterCache::OnRemoveEntityComponentNoLock(const EntityId& id, ClassId compId) 
{
    for (auto& entry : entries_) 
    {
        if (!entry.count) continue; 
        // TODO 
        auto& filter = entry.filter; 

        bool match = filter.Matches(*entityManager_, id); 

        if (match && filter.Excludes(compId)) 
        {
            // removed component must be excluded to match filter 

            // add id
            entry.entities.push_back(id); 
            // Logger::Debug("FilterCache: Adding ID (Remove Component): ", id.id); 
        }
        else if (!match && filter.MatchesWith(*entityManager_, id, compId)) 
        {
            // removed component must be included to match filter 

            // remove id 
            auto& list = entry.entities; 
            for (unsigned i = 0; i < list.size(); i++) 
            {
                if (list[i] == id) 
                {
                    list[i] = list.back(); 
                    list.pop_back(); 
                    break; 
                }
            } 
            // Logger::Debug("FilterCache: Removing ID (Remove Component): ", id.id); 
        }

        // else do nothing, it is already either in or not in list 
    }
}

}