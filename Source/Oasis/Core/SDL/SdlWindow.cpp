#include "Oasis/Core/SDL/SDLWindow.h"

#include <GL/glew.h>

#include <iostream>

using namespace std;

namespace Oasis
{

bool SDLWindow::sdlInit_ = false;

SDLWindow::SDLWindow(const std::string& title)
    : title_(title)
    , window_(NULL)
    , context_(NULL)
    , close_(false)
{
    // init SDL if it has not already been
    if (!sdlInit_) SDL_Init(SDL_INIT_EVERYTHING);

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

    context_ = SDL_GL_CreateContext(window_);
    SDL_GL_MakeCurrent(window_, context_);

    glewExperimental = GL_TRUE;
    glewInit();
}

SDLWindow::~SDLWindow()
{
    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);

    context_ = NULL;
    window_ = NULL;
}

const std::string& SDLWindow::GetTitle() const
{
    return title_;
}

int SDLWindow::GetWidth() const
{
    int width;
    SDL_GetWindowSize(window_, &width, NULL);
    return width;
}

int SDLWindow::GetHeight() const
{
    int height;
    SDL_GetWindowSize(window_, NULL, &height);
    return height;
}

void SDLWindow::SetTitle(const std::string& title)
{
    title_ = title;
    SDL_SetWindowTitle(window_, title.c_str());
}

void SDLWindow::SetSize(int width, int height)
{
    SDL_SetWindowSize(window_, width, height);
}

void SDLWindow::Center()
{
    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void SDLWindow::PollEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            close_ = true;
        }
    }
}

void SDLWindow::SwapBuffers()
{
    SDL_GL_SwapWindow(window_);
}

}
