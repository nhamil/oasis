#include "Oasis/Core/Engine.h"

#include "Oasis/Core/Application.h"
#include "Oasis/Core/Timer.h"

#include "Oasis/Core/SDL/SDLWindow.h"

#include "Oasis/Graphics/OpenGL/OGLGraphics.h"

#include <iostream>

using namespace std;

namespace Oasis
{

namespace // private data
{
    bool running_ = false;

    Graphics* graphics_ = NULL;
    Window* window_ = NULL;
}

bool Engine::IsRunning()
{
    return running_;
}

void Engine::Start(const Config& conf)
{
    cout << "Starting engine..." << endl;

    if (IsRunning())
    {
        cerr << "Engine is already running, cannot start!" << endl;
        return;
    }

    running_ = true;

    window_ = new SDLWindow();
    graphics_ = new OGLGraphics();

    return;
}

void Engine::Stop()
{
    if (!running_)
    {
        cerr << "Engine attempted to stop but is not running!" << endl;
    }

    cout << "Stopping application..." << endl;

    //delete graphics_;
    graphics_ = NULL;

    //delete window_;
    window_ = NULL;

    cout << "Done!" << endl;

    running_ = false;
}

Graphics* Engine::GetGraphics()
{
    return graphics_;
}

Window* Engine::GetWindow()
{
    return window_;
}

void Engine::PreUpdate(float dt)
{
    window_->PollEvents();
}

void Engine::PostUpdate(float dt)
{

}

void Engine::PreRender()
{
    graphics_->PreRender();
}

void Engine::PostRender()
{
    graphics_->PostRender();
    window_->SwapBuffers();
}

}
