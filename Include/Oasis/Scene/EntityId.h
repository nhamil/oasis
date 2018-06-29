#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

struct OASIS_API EntityId 
{
    EntityId() = default; 
    EntityId(uint32 id, uint32 version) : id(id), version(version) {} 

    uint32 id = 0; 
    uint32 version = 0; 

    bool operator==(const EntityId& other) const { return id == other.id && version == other.version; } 
    bool operator!=(const EntityId& other) const { return id != other.id || version != other.version; } 
};

}