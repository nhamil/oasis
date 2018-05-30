#ifdef __linux__ 

#include "Oasis/Core/Timer.h" 

namespace Oasis 
{

Timer::Timer() 
{
    Reset(); 
} 

Timer::~Timer() {} 

void Timer::Stop() 
{
    if (running_) 
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_); 
        running_ = false; 
    }
} 

void Timer::Start() 
{
    running_ = true; 
} 

void Timer::Reset() 
{
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_); 
    stop_ = start_; 
} 

double Timer::GetSeconds() 
{
    if (running_) 
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_); 
    }

    return static_cast<double>(
        ((stop_.tv_sec - start_.tv_sec) * 1000000000L + 
         (stop_.tv_nsec - start_.tv_nsec)) / 1e9 
    ); 
}

}

#endif 