#include "Oasis/Core/Engine.h"

#include "Oasis/Core/Application.h"
#include "Oasis/Core/Timer.h"

#include "Oasis/Core/SDL/SDLWindow.h"

#include "Oasis/Graphics/OpenGL/OGLGraphics.h"

#include <iostream>

using namespace std;

namespace Oasis
{

int GameLoop(); 

namespace // private data
{
    bool running_ = false;
    float fps_ = 0, ups_ = 0; 

    Config config_; 
    Application* app_ = NULL; 
    Graphics* graphics_ = NULL;
    Window* window_ = NULL;
}

bool Engine::IsRunning()
{
    return running_;
}

int Engine::Start(Application* app)
{
    cout << "Starting engine..." << endl;

    if (IsRunning())
    {
        cerr << "Engine is already running, cannot start!" << endl;
        return -1;
    }

    if (!app) 
    {
        cerr << "Application is null, cannot start!" << endl; 
        return -2; 
    }

    config_ = app->GetConfig(); 

    running_ = true;

    app_ = app; 
    window_ = new SDLWindow();
    graphics_ = new OGLGraphics();

    return GameLoop();
}

void Engine::Stop()
{
    if (!running_)
    {
        cerr << "Engine attempted to stop but is not running!" << endl;
    }

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

Keyboard* Engine::GetKeyboard() 
{
    return &window_->GetKeyboard(); 
}

void PreUpdate(float dt)
{
    window_->PollEvents();
}

void PostUpdate(float dt)
{

}

void PreRender()
{
    graphics_->PreRender();
}

void PostRender()
{
    graphics_->PostRender();
    window_->SwapBuffers();
}

int GameLoop() 
{
    app_->Init(); 

    int tickCount = 0;
    int frameCount = 0;

    float dt = 1.0 / config_.targetUps;

    Timer timer;
    Timer secondTimer;

    double frameTimer = 0;
    double skipFrames = 1.0 / config_.targetFps;

    double tickTimer = 0;
    double skipTicks = 1.0 / config_.targetUps;

    while (running_) 
    {
        int loop = 0;

        while (loop++ < 10 && tickTimer < timer.GetSeconds())
        {
            PreUpdate(dt);
            app_->Update(dt);
            PostUpdate(dt);

            tickTimer += skipTicks;
            tickCount++;
        }

        if (frameTimer < timer.GetSeconds())
        {
            PreRender();
            app_->Render();
            PostRender();

            frameTimer += skipFrames;
            frameCount++;
        }

        if (secondTimer.GetSeconds() >= 1)
        {
            cout << "FPS: " << frameCount << ", Ticks: " << tickCount << endl;
            fps_ = frameCount;
            ups_ = tickCount;
            tickCount = frameCount = 0;

            secondTimer.Reset();
        }

        if (window_->IsCloseRequested())
        {
            Engine::Stop();
        }
    }

    app_->Exit(); 

    // engine has been told to stop 
    cout << "Stopping application..." << endl;

    //delete graphics_;
    graphics_ = NULL;

    //delete window_;
    window_ = NULL;

    app_ = NULL; 

    cout << "Done!" << endl;

    return 0; 
}

}
