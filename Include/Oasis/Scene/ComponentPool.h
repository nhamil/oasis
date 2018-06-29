#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Util/IdManager.h" 

#include <new> 

namespace Oasis
{

struct Component; 

class OASIS_API ComponentPoolBase 
{
public: 
    virtual ~ComponentPoolBase() {} 

    virtual Component* GetComponent(uint32 index) = 0; 

    virtual void Reserve(uint32 count) = 0; 

    virtual uint32 CreateComponent(const Component* from) = 0; 

    virtual bool DestroyComponent(uint32 id) = 0; 
};

template <class T> 
class OASIS_API ComponentPool : public ComponentPoolBase 
{
public: 
    ~ComponentPool() 
    {
        uint32 max = ids_.Size(); 
        for (uint32 i = 0; i < max; i++) 
        {
            DestroyComponent(i); 
        }
    }

    Component* GetComponent(uint32 index) override 
    {
        if (ids_.IsValid(index)) 
        {
            return (Component*) &data_[index * sizeof (T)]; 
        }
        else 
        {
            return nullptr; 
        }
    }

    void Reserve(uint32 count) override 
    {
        data_.reserve(count * sizeof (T)); 
    }

    uint32 CreateComponent(const Component* from) override 
    {
        uint32 id = ids_.Get(); 

        // TODO create 
        Reserve(ids_.Size()); 
        CreateComponentFromAddress(&data_[id * sizeof (T)], from); 

        return id; 
    }

    bool DestroyComponent(uint32 id) override 
    {
        bool existed = ids_.Release(id); 

        if (existed) 
        {
            DestroyComponentFromAddress(&data_[id * sizeof (T)]); 
        }

        return existed; 
    }

private: 
    std::vector<uint8> data_; 
    IdManager32 ids_; 

    void CreateComponentFromAddress(void* address, const Component* from)  
    {
        if (from) 
        {
            new(address) T(*((T*) from)); 
        }
        else 
        {
            new(address) T(); 
        }
    }

    void DestroyComponentFromAddress(void* address) 
    {
        ((T*) address)->~T(); 
    }
};

}