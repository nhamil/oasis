#include "Oasis/Scene/Scene.h" 

#include "Oasis/Scene/System.h" 

#include <algorithm> 

namespace Oasis
{

Scene::Scene() {}

Scene::~Scene() {} 

void Scene::AddSystem(EntitySystem& system) 
{
    systems_.push_back(&system); 
    system.SetScene(this); 

    std::sort(systems_.begin(), systems_.end(), [](EntitySystem* a, EntitySystem* b) -> bool { return a->GetPriority() < b->GetPriority(); }); 
}

bool Scene::RemoveSystem(EntitySystem& system) 
{
    for (auto it = systems_.begin(); it != systems_.end(); ++it) 
    {
        if (*it == &system) 
        {
            systems_.erase(it); 
            return true; 
        }
    }

    return false; 
}

void Scene::Update(float dt) 
{
    for (auto system : systems_) 
    {
        system->Update(dt); 
    }
}

void Scene::Render() 
{
    for (auto system : systems_) 
    {
        system->Render(); 
    }
}

}