#include "Oasis/Scene/Entity.h" 

namespace Oasis
{

Entity::Entity(EntityManager* manager, const EntityId& id) 
    : manager_(manager) 
    , id_(id) {} 

bool Entity::IsValid() const
{
    if (!manager_) return false; 
    return manager_->IsValidId(id_); 
}

}