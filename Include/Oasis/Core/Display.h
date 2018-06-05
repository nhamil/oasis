#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Input/Keyboard.h" 

#include <SDL2/SDL.h> 

namespace Oasis 
{

class OASIS_API Display 
{
public: 
    inline Keyboard* GetKeyboard() { return &keys_; }

    inline const std::string& GetTitle() const { return title_; } 
    int GetWidth() const; 
    int GetHeight() const; 

    inline float GetAspectRatio() const { return (float) GetWidth() / GetHeight(); } 

    inline bool IsCloseRequested() const { return shouldClose_; } 

    void SetTitle(const std::string& title); 
    void SetSize(int width, int height); 

    void Center(); 

    void PollEvents(); 
    void SwapBuffers(); 

private: 
    explicit Display(const std::string& title = "Oasis Engine"); 
    ~Display(); 

    friend class Engine; 

    static int windowCount_; 

    std::string title_; 
    SDL_Window* window_ = nullptr; 
    SDL_GLContext glContext_ = nullptr; 
    bool shouldClose_ = false; 
    Keyboard keys_; 
};

}