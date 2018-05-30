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
    if (m_running) 
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_stop); 
        m_running = false; 
    }
} 

void Timer::Start() 
{
    m_running = true; 
} 

void Timer::Reset() 
{
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_start); 
    m_stop = m_start; 
} 

double Timer::GetSeconds() 
{
    if (m_running) 
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_stop); 
    }

    return static_cast<double>(
        ((m_stop.tv_sec - m_start.tv_sec) * 1000000000L + 
         (m_stop.tv_nsec - m_start.tv_nsec)) / 1e9 
    ); 
}

}

#endif 