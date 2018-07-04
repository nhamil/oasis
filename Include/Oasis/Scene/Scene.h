#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Component.h" 
#include "Oasis/Scene/EntityManager.h" 

namespace Oasis
{

class EntitySystem; 

class OASIS_API Scene 
{
public: 
    Scene(); 
    ~Scene(); 

    EntityManager& GetEntityManager() { return entityManager_; } 

    void AddSystem(EntitySystem& system); 
    bool RemoveSystem(EntitySystem& system);    

    void Update(float dt); 
    void Render(); 

private: 
    EntityManager entityManager_; 
    std::vector<EntitySystem*> systems_; 
};

}