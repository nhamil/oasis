#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Component.h" 
#include "Oasis/Scene/Entity.h" 

namespace Oasis
{

class OASIS_API Scene 
{
public: 
    Scene(); 
    ~Scene(); 

    Entity CreateEntity(); 
    bool DestroyEntity(const Entity& entity); 

private: 
    EntityManager entityManager_; 
};

}