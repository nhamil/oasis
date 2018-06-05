#pragma once

#include "Oasis/Common.h"

#ifdef _WIN32
#include "Oasis/OasisWindows.h"
#else // linux 
#include <time.h> 
#endif 

namespace Oasis
{

class OASIS_API Timer
{
public:
    Timer();
    ~Timer();

    void Stop();
    void Start();
    void Reset();

    double GetSeconds();

private:
    #ifdef _WIN32
    LARGE_INTEGER freq_;
    LARGE_INTEGER start_;
    LARGE_INTEGER stop_;
    bool running_;
    #else // linux 
    struct timespec start_, stop_; 
    bool running_; 
    #endif // _WIN32
};

}
