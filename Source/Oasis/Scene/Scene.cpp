#include "Oasis/Scene/Scene.h" 

namespace Oasis
{

Scene::Scene() {}

Scene::~Scene() {} 

Entity Scene::CreateEntity() 
{
    return Entity(&entityManager_, entityManager_.CreateEntityId()); 
}

bool Scene::DestroyEntity(const Entity& e) 
{
    return entityManager_.DestroyEntityId(e.GetId()); 
}

}