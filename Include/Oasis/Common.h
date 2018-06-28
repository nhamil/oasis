#pragma once 

#ifdef _WIN32
    #ifdef OASIS_EXPORT
        #define OASIS_API __declspec(dllexport)
    #else
        #define OASIS_API __declspec(dllimport)
    #endif
#else
    #define OASIS_API
#endif

#define OASIS_NO_COPY(Type) \
    Type(const Type& other) = delete; \
    Type& operator=(const Type& other) = delete; 

#include <cstdint> 
#include <cstdlib>
#include <set> 
#include <string> 
#include <unordered_map> 
#include <unordered_set> 
#include <vector> 

namespace Oasis 
{

    using int8 = std::int8_t; 
    using int16 = std::int16_t; 
    using int32 = std::int32_t; 
    using int64 = std::int64_t; 

    using uint8 = std::uint8_t; 
    using uint16 = std::uint16_t; 
    using uint32 = std::uint32_t; 
    using uint64 = std::uint64_t; 

}

#include "Oasis/Core/Logger.h" 
#include "Oasis/Core/ReferenceCounted.h" 
#include "Oasis/Util/ClassId.h" 

#include "Oasis/Core/Object.h" 