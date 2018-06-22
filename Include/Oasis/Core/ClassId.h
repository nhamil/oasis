#pragma once 

#include "Oasis/Common.h"

#include <typeinfo> 

namespace Oasis 
{

using ClassId = unsigned long long; 

template <class T> 
OASIS_API ClassId GetClassId() 
{
    return reinterpret_cast<ClassId>(&typeid(T)); 
}

template <class T> 
OASIS_API ClassId GetClassId(const T& value) 
{
    return GetClassId<T>(); 
}

}