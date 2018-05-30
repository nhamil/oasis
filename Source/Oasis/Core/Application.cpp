#include "Oasis/Core/Application.h"

#include "Oasis/Core/Engine.h"
#include "Oasis/Core/Timer.h"
#include "Oasis/Core/Window.h"

#include <iostream>

using namespace std;

namespace Oasis
{

Application::Application()
    : running_(false)
    , fps_(0)
    , ups_(0) {}

int Application::Start()
{
    if (running_) return -1;

    running_ = true;

    Config conf = GetConfig();

    Engine::Start(conf);

    Init();

    int tickCount = 0;
    int frameCount = 0;

    float dt = 1.0 / conf.targetUps;

    Timer timer;
    Timer secondTimer;

    double frameTimer = 0;
    double skipFrames = 1.0 / conf.targetFps;

    double tickTimer = 0;
    double skipTicks = 1.0 / conf.targetUps;

    while (running_)
    {
        int loop = 0;

        while (loop++ < 10 && tickTimer < timer.GetSeconds())
        {
            Engine::PreUpdate(dt);
            Update(dt);
            Engine::PostUpdate(dt);

            tickTimer += skipTicks;
            tickCount++;
        }

        if (frameTimer < timer.GetSeconds())
        {
            Engine::PreRender();
            Render();
            Engine::PostRender();

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

        if (Engine::GetWindow()->IsCloseRequested())
        {
            Stop();
        }
    }

    Exit();

    Engine::Stop();

    return 0;
}

void Application::Stop()
{
    running_ = false;
}

}
