#pragma once 

#include "Oasis/Common.h" 

#include <ostream> 
#include <sstream> 

#define OASIS_LOG_TYPE(function, level) \
    template <class First, class... Rest> inline static bool function (First value, Rest... rest) { return Log(level, value, rest...); } 

namespace Oasis 
{

enum class LogLevel 
{
    FATAL = 0, 
    ERROR = 1, 
    WARNING = 2, 
    INFO = 3, 
    DEBUG = 4, 
    FINE = 5, 

    count = 6
};

inline const char* GetLogLevelName(LogLevel level) 
{
    switch (level) 
    {
    case LogLevel::FATAL: return "[FATAL] "; 
    case LogLevel::ERROR: return "[ERROR] "; 
    case LogLevel::WARNING: return "[WARN ] "; 
    case LogLevel::INFO: return "[INFO ] "; 
    case LogLevel::DEBUG: return "[DEBUG] "; 
    case LogLevel::FINE: return "[FINE ] "; 
    default: return ""; 
    }
}

class OASIS_API Logger 
{
public: 
    static void SetOutput(std::ostream* out); 

    static LogLevel GetLevel() { return level_; } 
    static void SetLevel(LogLevel level); 

    template <class First, class... Rest> 
    static bool Log(LogLevel level, First message, Rest... rest); 

    OASIS_LOG_TYPE(Fatal, LogLevel::FATAL) 
    OASIS_LOG_TYPE(Error, LogLevel::ERROR) 
    OASIS_LOG_TYPE(Warning, LogLevel::WARNING) 
    OASIS_LOG_TYPE(Info, LogLevel::INFO) 
    OASIS_LOG_TYPE(Debug, LogLevel::DEBUG) 
    OASIS_LOG_TYPE(Fine, LogLevel::FINE) 

private: 
    Logger() = delete; 
    ~Logger() = delete; 

    template <class First, class... Rest> 
    static void BuildString(std::stringstream& out, First first, Rest... rest); 
    static void BuildString(std::stringstream& out) { (void) out; } 

    static std::ostream* out_; 
    static LogLevel level_; 
};

template <class First, class... Rest> 
bool Logger::Log(LogLevel level, First first, Rest... rest) 
{
    if (level > level_ || !out_) return false; 

    std::stringstream out; 
    BuildString(out, first, rest...); 

    (*out_) << GetLogLevelName(level) << out.str() << std::endl; 

    return true; 
}

template <class First, class... Rest> 
void Logger::BuildString(std::stringstream& out, First first, Rest... rest) 
{
    out << first; 

    if (sizeof... (Rest)) 
    {
        BuildString(out, rest...); 
    }
} 

}