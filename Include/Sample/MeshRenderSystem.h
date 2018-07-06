#pragma once 

#include <Oasis/Oasis.h> 

using namespace Oasis; 

class MeshRenderSystem : public EntitySystem 
{
public: 
    MeshRenderSystem(); 

    void OnRender(Scene& scene, uint32 count, const EntityId* entities) override; 

private: 
    void CreateResources(); 

    Shader* shader_; 
    Texture2D* texture_; 
};
