#pragma once 

#include "Oasis/Common.h" 

#include <ostream> 



namespace Oasis 
{

enum class LogLevel 
{
    FATAL, 
    ERROR, 
    WARNING, 
    INFO, 
    DEBUG, 
    FINE, 

    count 
};

class OASIS_API Logger 
{
public: 
    static void SetOutput(std::ostream* out); 

    static LogLevel GetLevel() { return level_; } 
    static void SetLevel(LogLevel level); 

    static bool Log(LogLevel level, const char* message); 
    static bool Log(LogLevel level, const std::string& message) { return Log(level, message.c_str()); }  

private: 
    Logger() = delete; 
    ~Logger() = delete; 

    static std::ostream* out_; 
    static LogLevel level_; 
};

}