#include "Oasis/Scene/Filter.h" 

#include "Oasis/Scene/Entity.h" 

namespace Oasis 
{

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

bool EntityFilter::Matches(const Entity& entity) const 
{
    for (auto comp : include_) 
    {
        if (!entity.Has(comp)) return false; 
    }

    for (auto comp : exclude_) 
    {
        if (entity.Has(comp)) return false; 
    }

    return true; 
}

}