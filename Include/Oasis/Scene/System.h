#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Filter.h" 

namespace Oasis
{

class OASIS_API EntitySystem 
{
public: 
    const int DEFAULT_PRIORITY; 

    EntitySystem(int priority); 
    EntitySystem(); 

    inline Scene* GetScene() { return scene_; } 

    virtual void OnAdded() {}  

    virtual void OnRemoved() {} 

    virtual void Update(float dt, uint32 count, Entity* entities); 

    virtual void Render(uint32 count, Entity* entities); 

protected: 
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
    friend class Scene; 

    void SetScene(Scene* scene); 

    int32 priority_ = DEFAULT_PRIORITY; 
    Scene* scene_ = nullptr; 
    EntityFilter filter_; 
}; 

}