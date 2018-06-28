#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/ComponentPool.h" 

namespace Oasis 
{

struct OASIS_API EntityId 
{
    uint32 id; 
    uint32 version; 

    bool operator==(const EntityId& other) const { return id == other.id && version == other.version; } 
    bool operator!=(const EntityId& other) const { return id != other.id || version != other.version; } 
};

class OASIS_API EntityManager 
{
public: 
    EntityManager(); 
    ~EntityManager(); 

private: 
    
};

class OASIS_API Entity 
{
public: 
    Entity(EntityManager* manager_, const EntityId& id); 
    ~Entity() = default; 

    inline EntityManager* GetManager() { return manager_; } 

private: 
    friend class EntityManager; 

    EntityManager* manager_; 
    EntityId id_; 
};

}