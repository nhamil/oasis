#include "Oasis/Core/Engine.h"

#include "Oasis/Core/Application.h" 
#include "Oasis/Core/Display.h" 
#include "Oasis/Core/Timer.h" 
#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 

using namespace std;

namespace Oasis
{

float Engine::ups_ = 0; 
float Engine::fps_ = 0; 
Application* Engine::app_ = nullptr; 
bool Engine::running_ = false; 
Config Engine::config_; 

Display* Engine::display_ = nullptr; 
GraphicsDevice* Engine::graphics_ = nullptr; 

int Engine::Start(Application* app)
{
    Logger::Debug("Starting engine..."); 

    config_ = app->GetConfig(); 

    if (IsRunning())
    {
        Logger::Error("Engine is already running, cannot start!"); 
        return -1;
    }

    if (!app) 
    {
        Logger::Error("Application is null, cannot start!"); 
        return -2; 
    }

    app_ = app; 

    running_ = true;

    display_ = new Display(); 
    graphics_ = new GLGraphicsDevice(); 

    return GameLoop();
}

void Engine::Stop()
{
    if (!running_)
    {
        Logger::Error("Engine attempted to stop but is not running!");
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

    //double frameTimer = 0;
    double skipFrames = 1.0 / config_.targetFps;

    //double tickTimer = 0;
    double skipTicks = 1.0 / config_.targetUps;

    double prevTime = timer.GetSeconds(); 
    double delay = 0; 

    double prevFrameTime = timer.GetSeconds(); 
    double frameDelay = 0; 

    while (running_) 
    {
        double curTime = timer.GetSeconds(); 
        double delta = curTime - prevTime; 
        prevTime = curTime; 
        delay += delta; 

        double curFrameTime = timer.GetSeconds(); 
        double frameDelta = curFrameTime - prevFrameTime; 
        prevFrameTime = curFrameTime; 
        frameDelay += frameDelta; 

        bool render = false; 

        while (delay >= skipTicks) 
        {
            render = true; 

            PreUpdate(dt);
            app_->Update(dt);
            PostUpdate(dt);

            delay -= skipTicks; 
            tickCount++;
        }

        // TODO change this 
        while (render && frameDelay >= skipFrames) 
        {
            PreRender();
            app_->Render();
            PostRender();

            frameDelay -= skipFrames; 
            frameCount++;
        }

        if (secondTimer.GetSeconds() >= 1)
        {
            Logger::Debug("FPS: ", frameCount, ", Ticks: ", tickCount); 
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
    delete app_; 

    // engine has been told to stop 
    Logger::Debug("Stopping engine...");

    delete display_; 
    display_ = nullptr; 

    delete graphics_; 
    graphics_ = nullptr; 

    app_ = nullptr; 

    Logger::Debug("Engine terminated!");

    return 0; 
}

void Engine::PreUpdate(float dt) 
{
    (void) dt; 
    display_->PollEvents(); 
}

void Engine::PostUpdate(float dt) 
{
    (void) dt; 
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
