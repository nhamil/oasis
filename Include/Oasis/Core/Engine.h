#pragma once

#include "Oasis/Common.h"
#include "Oasis/Core/Config.h" 

namespace Oasis
{

class Application; 
class Display; 
class Graphics; 

class OASIS_API Engine
{
public: 
    template <class T> 
    static void RegisterSubsystem(T* system); 

    template <class T> 
    static void UnregisterSubsystem(); 

    template <class T> 
    static T* GetSubsystem(); 

    template <class T> 
    static bool HasSubsystem(); 

    static int Start(Application* app); 
    static void Stop(); 

    inline static float GetFrameRate() { return fps_; }  
    inline static float GetUpdateRate() { return ups_; }  

    inline static bool IsRunning() { return running_; }  

private: 
    static int GameLoop(); 

    static void PreUpdate(float dt); 
    static void PostUpdate(float dt); 

    static void PreRender(); 
    static void PostRender(); 

    // systems 
    static std::unordered_map<ClassId, void*> subsystems_; 
    static Display* display_; 
    static Graphics* graphics_; 

    // engine variables 
    static float fps_; 
    static float ups_; 
    static bool running_; 
    static Application* app_; 
    static Config config_; 
}; 

template <class T> 
void Engine::RegisterSubsystem(T* system) 
{
    subsystems_[GetClassId<T>()] = system; 
}

template <class T> 
void Engine::UnregisterSubsystem() 
{
    subsystems_.erase(GetClassId<T>()); 
}

template <class T> 
bool Engine::HasSubsystem() 
{
    return GetSubsystem<T>() != nullptr; 
}

template <class T> 
T* Engine::GetSubsystem() 
{
    auto sys = subsystems_.find(GetClassId<T>()); 

    if (sys != subsystems_.end() && sys->second) 
    {
        return (T*) sys->second; 
    }
    else 
    {
        return nullptr; 
    }
}

template <>
inline Application* Engine::GetSubsystem<Application>() 
{
    return app_; 
}

template <> 
inline Graphics* Engine::GetSubsystem<Graphics>() 
{
    return graphics_; 
}

template <> 
inline Display* Engine::GetSubsystem<Display>() 
{
    return display_; 
}

}
