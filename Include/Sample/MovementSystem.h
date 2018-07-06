#pragma once 

#include <Oasis/Oasis.h> 

#include "Sample/Components.h" 

using namespace Oasis; 

class MovementSystem : public EntitySystem 
{
public: 
    MovementSystem(); 

    void OnUpdate(Scene& scene, uint32 count, const EntityId* entities, float dt) override; 
};
