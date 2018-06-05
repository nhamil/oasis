#include "Oasis/Core/Display.h" 

#include <GL/glew.h> 

using namespace std; 

namespace Oasis 
{

int Display::windowCount_ = 0; 

Display::Display(const string& title) 
    : title_(title) 
{
    if (!windowCount_++) 
    {
        // init SDL 
        SDL_Init(SDL_INIT_EVERYTHING); 
    }

    window_ = SDL_CreateWindow
    (
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    glContext_ = SDL_GL_CreateContext(window_);
    SDL_GL_MakeCurrent(window_, glContext_);

    glewExperimental = GL_TRUE;
    glewInit();
}

Display::~Display() 
{
    SDL_GL_DeleteContext(glContext_);
    SDL_DestroyWindow(window_);

    windowCount_--; 

    if (!windowCount_) 
    {
        // last window, stop SDL 
        SDL_Quit(); 
    }
}

int Display::GetWidth() const 
{
    int width;
    SDL_GetWindowSize(window_, &width, NULL);
    return width;
} 

int Display::GetHeight() const 
{
    int height;
    SDL_GetWindowSize(window_, NULL, &height);
    return height;
} 

void Display::SetTitle(const std::string& title) 
{
    title_ = title;
    SDL_SetWindowTitle(window_, title.c_str());
} 

void Display::SetSize(int width, int height) 
{
    SDL_SetWindowSize(window_, width, height);
}

void Display::Center() 
{
    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
} 

void Display::PollEvents() 
{
    SDL_Event e;

    keys_.Update(); 

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            shouldClose_ = true;
            break; 
        case SDL_KEYDOWN: 
            keys_.SetKey(Key(e.key.keysym.sym), true); 
            break; 
        case SDL_KEYUP: 
            keys_.SetKey(Key(e.key.keysym.sym), false); 
            break; 
        }
    }
} 

void Display::SwapBuffers() 
{
    SDL_GL_SwapWindow(window_);
}  

}