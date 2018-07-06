#include "Oasis/Scene/SystemManager.h" 

#include "Oasis/Scene/Scene.h" 
#include "Oasis/Scene/System.h" 

#include <algorithm> 

namespace Oasis 
{

EntitySystemManager::EntitySystemManager(Scene& scene) 
    : scene_(scene), entityManager_(scene.GetEntityManager()) 
{

}

EntitySystemManager::~EntitySystemManager() 
{
    for (auto& entry : systems_) 
    {
        if (entry.autoDelete) 
        {
            delete entry.system; 
        }
    }
}

void EntitySystemManager::AddSystem(EntitySystem* system, bool autoDelete) 
{
    Entry entry(system, autoDelete); 

    if (system->GetScene()) 
    {
        system->GetScene()->RemoveSystem(system); 
    }

    system->SetScene(&scene_); 

    sorted_ = false; 
    systems_.push_back(entry); 
}

bool EntitySystemManager::RemoveSystem(EntitySystem* system) 
{
    int index = FindSystemIndex(system); 

    if (index != -1) 
    {
        // found 
        systems_[index].removeFlag = true; 
        sorted_ = false; 
        return true; 
    }
    else return false; 
}

bool EntitySystemManager::SetSystemEnabled(EntitySystem* system, bool enabled) 
{
    Entry* entry = FindSystemEntry(system); 

    if (entry) 
    {
        entry->enabled = enabled; 
        return true; 
    }
    else return false; 
}

bool EntitySystemManager::SortSystems() 
{
    if (sorted_) return false; 

    // remove systems that are flagged 
    for (unsigned i = 0; i < systems_.size(); i++) 
    {
        Entry& e = systems_[i]; 
        if (e.removeFlag) 
        {
            if (e.autoDelete) delete e.system; 

            systems_.erase(systems_.begin() + i); 
        }
    }

    // sort list for any new systems added 
    std::sort(systems_.begin(), systems_.end(), 
        [](
            const Entry& a, 
            const Entry& b  
        ) -> bool { 
            return a.system->GetPriority() < b.system->GetPriority(); 
        }
    ); 

    return true; 
}

void EntitySystemManager::Update(float dt) 
{
    SortSystems(); 

    // use this in case any systems are added 
    unsigned startSize = systems_.size(); 

    for (unsigned i = 0; i < startSize; i++) 
    {
        Entry& e = systems_[i]; 

        if (e.enabled && !e.removeFlag) 
        {
            e.system->Update(dt); 
        }
    }
}

void EntitySystemManager::Render() 
{
    SortSystems(); 

    // use this in case any systems are added 
    unsigned startSize = systems_.size(); 

    for (unsigned i = 0; i < startSize; i++) 
    {
        Entry& e = systems_[i]; 

        if (e.enabled && !e.removeFlag) 
        {
            e.system->Render();  
        }
    }
}

int EntitySystemManager::FindSystemIndex(EntitySystem* system) 
{
    for (unsigned i = 0; i < systems_.size(); i++) 
    {
        if (!systems_[i].removeFlag && systems_[i].system == system) return i; 
    }
    return -1; 
}

EntitySystemManager::Entry* EntitySystemManager::FindSystemEntry(EntitySystem* system) 
{
    for (unsigned i = 0; i < systems_.size(); i++) 
    {
        if (!systems_[i].removeFlag && systems_[i].system == system) return &systems_[i]; 
    }
    return nullptr; 
}

}