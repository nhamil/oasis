#include "Oasis/Scene/Entity.h" 

namespace Oasis
{

Entity::Entity(EntityManager* manager, const EntityId& id) 
    : manager_(manager) 
    , id_(id) {} 

bool Entity::IsValid() const
{
    if (!manager_) return false; 
    return manager_->IsValidEntityId(id_); 
}

bool Entity::Has(ClassId compId) const 
{
    return manager_->HasComponent(id_, compId); 
}

void Entity::Set(EntityManager* manager, const EntityId& id) 
{
    manager_ = manager; 
    id_ = id; 
}

}