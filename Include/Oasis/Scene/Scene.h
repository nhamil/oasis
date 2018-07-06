#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Component.h" 
#include "Oasis/Scene/Entity.h" 
#include "Oasis/Scene/EntityManager.h" 
#include "Oasis/Scene/SystemManager.h" 

namespace Oasis
{

class EntitySystem; 

class OASIS_API Scene 
{
public: 
    Scene(); 
    ~Scene(); 

    EntityManager& GetEntityManager() { return entityManager_; } 
    EntitySystemManager& GetSystemManager() { return systemManager_; } 

    Entity CreateEntity(); 
    Entity GetEntity(const EntityId& id); 
    bool DestroyEntity(const Entity& entity); 

    void AddSystem(EntitySystem* system, bool autoDelete = true); 
    bool RemoveSystem(EntitySystem* system);    

    void Update(float dt); 
    void Render(); 

private: 
    EntityManager entityManager_; 
    EntitySystemManager systemManager_; 
};

}