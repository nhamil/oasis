#pragma once 

#include "Oasis/Common.h" 

namespace Oasis
{

struct EntityId; 
class EntityManager; 

class OASIS_API EntityFilter 
{
public: 
    EntityFilter(const std::vector<ClassId>& include, const std::vector<ClassId>& exclude); 
    EntityFilter() {} 

    bool Includes(ClassId id) const; 
    bool Excludes(ClassId id) const; 

    EntityFilter& Include(ClassId id); 
    EntityFilter& Exclude(ClassId id); 

    template <class T>
    EntityFilter& Include() 
    {
        return Include(GetClassId<T>()); 
    }

    template <class T> 
    EntityFilter& Exclude() 
    {
        return Exclude(GetClassId<T>()); 
    }

    bool Matches(const EntityManager& manager, const EntityId& id) const; 
    bool MatchesWith(const EntityManager& manager, const EntityId& id, ClassId compId) const; 
    bool MatchesWithout(const EntityManager& manager, const EntityId& id, ClassId compId) const; 

private: 
    std::vector<ClassId> include_; 
    std::vector<ClassId> exclude_; 
};

}