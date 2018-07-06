#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

class Scene; 

class OASIS_API SceneManager 
{
public: 
    SceneManager(); 
    ~SceneManager(); 

    bool IsValidScene(Scene* scene) const; 

    Scene* GetActiveScene() { return active_; } 
    bool SetActiveScene(Scene* scene); 
    Scene* SetActiveSceneByName(const std::string& name); 
    Scene* SetActiveSceneByIndex(int index); 

    Scene* CreateScene(const std::string& name); 
    Scene* CreateAndSetScene(const std::string& name); 

    Scene* GetSceneByName(const std::string& name); 
    Scene* GetSceneByIndex(int index); 

    bool UnloadScene(Scene* scene); 

private: 
    std::vector<Scene*> scenes_; 
    Scene* active_ = nullptr; 
};

}