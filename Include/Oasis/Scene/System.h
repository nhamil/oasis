#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Filter.h" 

namespace Oasis
{

class Scene; 

class OASIS_API EntitySystem 
{
public: 
    static const int DEFAULT_PRIORITY; 

    EntitySystem(int priority); 
    EntitySystem(); 
    virtual ~EntitySystem(); 

    inline Scene* GetScene() { return scene_; } 

    inline int GetPriority() const { return priority_; } 

    void Update(float dt); 

    void Render(); 

protected: 
    virtual void OnAdded() {}  

    virtual void OnRemoved() {} 

    virtual void OnUpdate(Scene& scene, uint32 count, const EntityId* entities, float dt);  

    virtual void OnRender(Scene& scene, uint32 count, const EntityId* entities);  

    template <class T> 
    void Include() 
    {
        filter_.Include<T>(); 
    }

    template <class T> 
    void Exclude() 
    {
        filter_.Exclude<T>(); 
    }

private: 
    friend class EntitySystemManager; 

    void SetScene(Scene* scene); 

    int32 priority_ = DEFAULT_PRIORITY; 
    Scene* scene_ = nullptr; 
    EntityFilter filter_; 
    uint32 filterId_ = 0; 
}; 

}