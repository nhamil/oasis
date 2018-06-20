#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

class OASIS_API ReferenceCounted 
{
public: 
    ReferenceCounted() {}
    virtual ~ReferenceCounted() {} 

    inline void AddRef() { count_++; }

    inline bool Release() 
    {
        bool count = --count_; 
        DeleteIfNeeded(); 
        return count == 0; 
    }

    inline int GetRefCount() const { return count_; } 

private: 
    ReferenceCounted(const ReferenceCounted& other); 
    ReferenceCounted& operator=(const ReferenceCounted& other); 

    inline void DeleteIfNeeded() 
    {
        if (count_ == 0) 
        {
            delete this; 
        }
    }

    int count_ = 1; 
};

}