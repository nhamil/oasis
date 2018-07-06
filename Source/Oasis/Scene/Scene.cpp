#include "Oasis/Scene/Scene.h" 

#include "Oasis/Scene/SceneManager.h" 
#include "Oasis/Scene/System.h" 

#include <algorithm> 

namespace Oasis
{

Scene::Scene(SceneManager& manager, const std::string& name, int index) : entityManager_(), systemManager_(*this), sceneManager_(manager), sceneName_(name), sceneIndex_(index) {}

Scene::~Scene() {}

Entity Scene::CreateEntity() 
{
    return Entity(&entityManager_, entityManager_.CreateEntityId()); 
}

Entity Scene::GetEntity(const EntityId& id) 
{
    return Entity(&entityManager_, id); 
}

bool Scene::DestroyEntity(const Entity& entity) 
{
    return entityManager_.DestroyEntityId(entity.GetId()); 
}

void Scene::AddSystem(EntitySystem* system, bool autoDelete) 
{
    systemManager_.AddSystem(system, autoDelete); 
}

bool Scene::RemoveSystem(EntitySystem* system) 
{
    return systemManager_.RemoveSystem(system); 
}

void Scene::Update(float dt) 
{
    systemManager_.Update(dt); 
}

void Scene::Render() 
{
    systemManager_.Render(); 
}

}