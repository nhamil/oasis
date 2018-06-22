#ifdef _WIN32

#include "Oasis/Core/Timer.h"

namespace Oasis
{

Timer::Timer()
    : running_(true)
{
    QueryPerformanceFrequency(&freq_);
    Reset();
}

Timer::~Timer() {}

void Timer::Stop()
{
    if (running_)
    {
        QueryPerformanceCounter(&stop_);
        running_ = false;
    }
}

void Timer::Start()
{
    running_ = true;
}

void Timer::Reset()
{
    QueryPerformanceCounter(&start_);
    stop_ = start_;
}

double Timer::GetSeconds()
{
    if (running_)
    {
        QueryPerformanceCounter(&stop_);
    }

    return static_cast<double>(stop_.QuadPart - start_.QuadPart) / freq_.QuadPart;
}

}

#endif // _WIN32
