#include "Oasis/Core/Logger.h" 

#include <iostream> 

using namespace std; 

namespace Oasis 
{

ostream* Logger::out_ = &cout; 
LogLevel Logger::level_ = LogLevel::DEBUG; 

void Logger::SetLevel(LogLevel level) 
{
    if (level_ == LogLevel::count) level_ = LogLevel::FINE; 

    level_ = level; 
}

}