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

#include <cstdlib>
#include <string> 
#include <unordered_map> 
#include <unordered_set> 
#include <vector> 

#include "Oasis/Core/ClassId.h" 
#include "Oasis/Core/ReferenceCounted.h" 
