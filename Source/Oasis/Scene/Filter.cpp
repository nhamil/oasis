#include "Oasis/Scene/Filter.h" 

#include "Oasis/Scene/EntityManager.h" 

namespace Oasis 
{

bool EntityFilter::Includes(ClassId id) const 
{
    for (auto inc : include_) 
    {
        if (inc == id) return true; 
    }

    return false; 
}

bool EntityFilter::Excludes(ClassId id) const 
{
    for (auto inc : exclude_) 
    {
        if (inc == id) return true; 
    }

    return false; 
}

EntityFilter& EntityFilter::Include(ClassId id) 
{
    include_.push_back(id); 
    return *this; 
}

EntityFilter& EntityFilter::Exclude(ClassId id) 
{
    exclude_.push_back(id); 
    return *this; 
}

EntityFilter::EntityFilter(const std::vector<ClassId>& include, const std::vector<ClassId>& exclude) 
    : include_(include) 
    , exclude_(exclude) {} 

bool EntityFilter::Matches(const EntityManager& manager, const EntityId& id) const 
{
    for (auto comp : include_) 
    {
        if (!manager.HasComponent(id, comp)) return false; 
    }

    for (auto comp : exclude_) 
    {
        if (manager.HasComponent(id, comp)) return false; 
    }

    return true; 
}

bool EntityFilter::MatchesWithout(const EntityManager& manager, const EntityId& id, ClassId compId) const 
{
    for (auto comp : include_) 
    {
        if (comp != compId && !manager.HasComponent(id, comp)) return false; 
    }

    for (auto comp : exclude_) 
    {
        if (comp != compId && manager.HasComponent(id, comp)) return false; 
    }

    return true; 
}

bool EntityFilter::MatchesWith(const EntityManager& manager, const EntityId& id, ClassId compId) const 
{
    for (auto comp : include_) 
    {
        if (comp == compId || !manager.HasComponent(id, comp)) return false; 
    }

    for (auto comp : exclude_) 
    {
        if (comp == compId || manager.HasComponent(id, comp)) return false; 
    }

    return true; 
}

}