#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

class EntityManager; 
class EntitySystem; 
class Scene; 

class OASIS_API EntitySystemManager 
{
public: 
    EntitySystemManager(Scene& scene); 
    ~EntitySystemManager(); 

    inline Scene& GetScene() { return scene_; } 
    inline EntityManager& GetEntityManager() { return entityManager_; } 

    void AddSystem(EntitySystem* system, bool autoDelete = true); 
    bool RemoveSystem(EntitySystem* system); 
    bool SetSystemEnabled(EntitySystem* system, bool enabled = true); 

    void Update(float dt); 
    void Render(); 

private: 
    struct Entry 
    {
        EntitySystem* system; 
        bool autoDelete; 
        bool enabled = true; 
        bool removeFlag = false; 

        Entry(EntitySystem* system, bool autoDelete) 
            : system(system), autoDelete(autoDelete) {} 
    };

    bool SortSystems(); 

    Entry* FindSystemEntry(EntitySystem* system); 
    int FindSystemIndex(EntitySystem* system); 

    Scene& scene_; 
    EntityManager& entityManager_; 
    std::vector<Entry> systems_; 
    bool sorted_ = true; 
};

}