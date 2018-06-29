#pragma once 

#include "Oasis/Common.h" 

namespace Oasis
{

class Entity; 

class OASIS_API EntityFilter 
{
public: 
    EntityFilter(const std::vector<ClassId>& include, const std::vector<ClassId>& exclude); 
    EntityFilter() {} 

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

    bool Matches(const Entity& entity) const; 

private: 
    std::vector<ClassId> include_; 
    std::vector<ClassId> exclude_; 
};

}