#pragma once

#include "Oasis/Common.h"
#include "Oasis/Core/Config.h" 

namespace Oasis
{

class Application; 
class Display; 
class GraphicsDevice; 
class SceneManager; 

class OASIS_API Engine
{
public: 
    inline static Display* GetDisplay() { return display_; } 
    inline static GraphicsDevice* GetGraphicsDevice() { return graphics_; } 
    inline static Application* GetApplication() { return app_; } 
    inline static SceneManager* GetSceneManager() { return sceneManager_; } 

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
    static Display* display_; 
    static GraphicsDevice* graphics_; 
    static Application* app_; 
    static SceneManager* sceneManager_; 
    
    // engine variables 
    static float fps_; 
    static float ups_; 
    static bool running_; 
    static Config config_; 
}; 

}
