#include "Oasis/Scene/SceneManager.h" 

#include "Oasis/Scene/Scene.h" 

namespace Oasis 
{

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {} 

bool SceneManager::IsValidScene(Scene* scene) const 
{
    if (!scene) return false; 

    if (&scene->GetSceneManager() != this) return false; 

    if (scenes_[scene->GetIndex()] != scene) return false; 

    return true; 
}

bool SceneManager::SetActiveScene(Scene* scene) 
{
    if (IsValidScene(scene)) 
    {
        active_ = scene; 
        return true; 
    }
    else 
    {
        active_ = nullptr; 
        return false; 
    }
}

Scene* SceneManager::SetActiveSceneByIndex(int index) 
{
    Scene* scene = GetSceneByIndex(index); 

    SetActiveScene(scene); 

    return scene; 
}

Scene* SceneManager::SetActiveSceneByName(const std::string& name) 
{
    Scene* scene = GetSceneByName(name); 

    SetActiveScene(scene); 

    return scene; 
}

Scene* SceneManager::CreateScene(const std::string& name) 
{
    Scene* scene = new Scene(*this, name, scenes_.size()); 

    scenes_.push_back(scene); 

    return scene; 
}

Scene* SceneManager::CreateAndSetScene(const std::string& name) 
{
    Scene* scene = CreateScene(name); 

    SetActiveScene(scene); 

    return scene; 
}

bool SceneManager::UnloadScene(Scene* scene) 
{
    if (!IsValidScene(scene)) return false; 

    scenes_[scene->GetIndex()] = nullptr; 

    delete scene; 
    return true; 
}

Scene* SceneManager::GetSceneByIndex(int index) 
{
    return scenes_[index]; 
}

Scene* SceneManager::GetSceneByName(const std::string& name) 
{
    for (unsigned i = 0; i < scenes_.size(); i++) 
    {
        Scene* s = scenes_[i]; 

        if (s && s->GetName() == name) return s; 
    }

    return nullptr; 
}

}