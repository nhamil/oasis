#ifdef __linux__ 

#include "Oasis/Core/TimeUtil.h" 

#include <time.h> 
#include <unistd.h> 

namespace Oasis 
{

namespace Time
{

uint64_t Millis() 
{
    struct timespec time; 

    clock_gettime(CLOCK_MONOTONIC, &time); 

    return (time.tv_sec * 1000 + time.tv_nsec / 1000000); 
}

void Sleep(uint64_t millis) 
{
    usleep(millis * 1000); // accepts microseconds 
}

}

}

#endif 