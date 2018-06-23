#include "Oasis/Core/Logger.h" 

#include <iostream> 

using namespace std; 

namespace Oasis 
{

const char* LOG_LEVEL[] = 
{
    "[FATAL] ", 
    "[ERROR] ", 
    "[WARN ] ", 
    "[INFO ] ", 
    "[DEBUG] ", 
    "[FINE ] ", 
};

ostream* Logger::out_ = &cout; 
LogLevel Logger::level_ = LogLevel::DEBUG; 

void Logger::SetLevel(LogLevel level) 
{
    if (level_ == LogLevel::count) level_ = LogLevel::FINE; 

    level_ = level; 
}

bool Logger::Log(LogLevel level, const char* message) 
{
    if (out_ && (int) level <= (int) level_) 
    {
        (*out_) << LOG_LEVEL[(int) level] << message; 
        return true; 
    }
    return false; 
}

}