#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/System.h" 

namespace Oasis 
{

class OASIS_API MeshRenderer : public EntitySystem 
{
public: 
    MeshRenderer(); 
    ~MeshRenderer(); 

private: 
    virtual void OnRender(Scene& scene, uint32 count, const EntityId* entities) override; 
};

}