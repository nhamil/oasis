#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/EntityManager.h" 

namespace Oasis 
{

class OASIS_API Entity 
{
public: 
    Entity(EntityManager* manager_, const EntityId& id); 
    ~Entity() = default; 

    inline EntityManager* GetManager() { return manager_; } 

    inline const EntityId& GetId() const { return id_; } 

    bool IsValid() const; 

    bool Has(ClassId id) const; 

    void Set(EntityManager* manager_, const EntityId& id); 

    template <class T> 
    bool Has() const
    {
        return manager_->HasComponent<T>(id_); 
    }

    template <class T> 
    T* Get() 
    {
        return manager_->GetComponent<T>(id_); 
    }

    template <class T, class ... Args> 
    T* Attach(Args... args) 
    {
        return manager_->AttachComponent<T>(id_, args...); 
    }

    template <class T> 
    bool Detach() 
    {
        return manager_->DetachComponent<T>(id_); 
    }

private: 
    EntityManager* manager_; 
    EntityId id_; 
};

}