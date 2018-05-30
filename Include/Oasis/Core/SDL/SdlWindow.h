#pragma once

#include "Oasis/Core/Window.h"

#include <SDL2/SDL.h>

namespace Oasis
{

class OASIS_API SDLWindow : public Window
{
public:
    explicit SDLWindow(const std::string& title = "Oasis Engine");
    virtual ~SDLWindow();

    virtual const std::string& GetTitle() const;
    virtual int GetWidth() const;
    virtual int GetHeight() const;

    bool IsCloseRequested() const { return close_; }

    virtual void SetTitle(const std::string& title);
    virtual void SetSize(int width, int height);

    virtual void Center();

    virtual void PollEvents();
    virtual void SwapBuffers();

private:
    static bool sdlInit_;

    std::string title_;
    SDL_Window* window_;
    SDL_GLContext context_;
    bool close_;
};

}
