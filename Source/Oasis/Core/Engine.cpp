#include "Oasis/Core/Engine.h"

#include "Oasis/Core/Application.h" 
#include "Oasis/Core/Display.h" 
#include "Oasis/Core/Timer.h" 
#include "Oasis/Graphics/Graphics.h" 

#include <iostream>

using namespace std;

namespace Oasis
{

float Engine::ups_ = 0; 
float Engine::fps_ = 0; 
Application* Engine::app_ = nullptr; 
bool Engine::running_ = false; 
Config Engine::config_; 

unordered_map<ClassId, void*> Engine::subsystems_; 
Display* Engine::display_ = nullptr; 
Graphics* Engine::graphics_ = nullptr; 

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

    app_ = app; 

    running_ = true;

    display_ = new Display(); 
    graphics_ = new Graphics(); 

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

int Engine::GameLoop() 
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

        if (display_->IsCloseRequested())
        {
            Engine::Stop();
        }
    }

    app_->Exit(); 

    // engine has been told to stop 
    cout << "Stopping engine..." << endl;

    delete display_; 
    display_ = nullptr; 

    delete graphics_; 
    graphics_ = nullptr; 

    app_ = nullptr; 

    cout << "Done!" << endl;

    return 0; 
}

void Engine::PreUpdate(float dt) 
{
    display_->PollEvents(); 
}

void Engine::PostUpdate(float dt) 
{

}

void Engine::PreRender() 
{
    graphics_->PreRender(); 
    graphics_->SetClearColor(0.6, 0.8, 0.9); 
    graphics_->Clear(); 
}

void Engine::PostRender() 
{
    graphics_->PostRender(); 
    display_->SwapBuffers(); 
}

}
