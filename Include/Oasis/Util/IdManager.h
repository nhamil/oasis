#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

template <class T> 
class OASIS_API IdManager 
{
public: 
    using Id = T; 

    IdManager() = default; 
    ~IdManager() = default; 

    Id Size() const { return size_; } 

    Id Get() 
    {
        if (released_.size()) 
        {
            // there is released id, use that 
            Id id = *released_.begin(); 
            released_.erase(released_.begin()); 
            return id; 
        }
        else 
        {
            return size_++; 
        }
    }

    bool Release(Id id) 
    {
        if (!IsValid(id)) return false; 

        released_.insert(id); 
        return true; 
    }

    bool IsValid(Id id) const 
    {
        return id >= 0 && id < size_ && released_.find(id) == released_.end(); 
    }

private: 
    Id size_ = 0; 
    std::set<Id> released_; 
};

using IdManager32 = IdManager<uint32>; 
using IdManager64 = IdManager<uint64>; 

}