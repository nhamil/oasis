#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Component.h" 
#include "Oasis/Scene/EntityManager.h" 

namespace Oasis
{

class OASIS_API Scene 
{
public: 
    Scene(); 
    ~Scene(); 

    EntityManager& GetEntityManager() { return entityManager_; } 

private: 
    EntityManager entityManager_; 
};

}