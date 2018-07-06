#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

class OASIS_API ReferenceCount 
{
public: 
    int GetRefCount() const { return count_; } 
    int GetWeakRefCount() const { return weakCount_; } 

    void AddRef() 
    {
        count_++; 
    }

    bool Release() 
    {
        count_--; 
        return count_ == 0; 
    }

    void AddWeakRef() 
    {
        weakCount_++; 
    }

    void ReleaseWeak() 
    {
        weakCount_--; 
    }

private: 
    int count_ = 1; 
    int weakCount_ = 0; 
};

class OASIS_API ReferenceCounted 
{
public: 
    ReferenceCounted() {}
    virtual ~ReferenceCounted() {} 

    inline void AddRef() 
    { 
        if (!count_) count_ = new ReferenceCount(); 

        count_->AddRef(); 
    }

    inline bool Release() 
    {
        if (!count_) 
        {
            delete this; 
            return true; 
        }
        else 
        {
            bool remove = count_->Release(); 
            if (remove) delete this; 
            return remove; 
        }
    }

    inline int GetRefCount() const { return count_ ? count_->GetRefCount() : 1; } 

    inline int GetWeakRefCount() const { return count_ ? count_->GetWeakRefCount() : 0; }

    inline ReferenceCount* GetRefCountPtr() 
    {
        if (!count_) count_ = new ReferenceCount(); 

        return count_; 
    }

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

    ReferenceCount* count_ = nullptr; 
};

template <class T> 
class OASIS_API RefCountPtr 
{
public: 
    RefCountPtr() 
    {
        ptr_ = nullptr; 
    }

    RefCountPtr(T* ptr) 
    {
        ptr_ = ptr; 
    }

    RefCountPtr(const RefCountPtr<T>& other) 
    {
        ptr_ = other.ptr_; 
        AddReference(); 
    }

    RefCountPtr<T>& operator=(const RefCountPtr<T>& other) 
    {
        other.AddReference(); 
        ReleaseReference(); 
        ptr_ = other.ptr_; 
        return *this; 
    }

    ~RefCountPtr() 
    {
        ReleaseReference(); 
    }

    explicit operator bool() const 
    {
        return IsValid(); 
    }

    bool IsValid() const 
    {
        return ptr_ != nullptr; 
    }

    T* Get() const 
    {
        return ptr_; 
    }

    T* operator->() const 
    {
        return ptr_; 
    }

    T& operator*() const 
    {
        return *ptr_; 
    }

private: 
    void AddReference() 
    {
        if (ptr_) ptr_->AddRef(); 
    }

    void ReleaseReference() 
    {
        if (ptr_) ptr_->Release(); 
    }

    T* ptr_; 
};

template <class T> 
class OASIS_API WeakRefCountPtr 
{
public: 
    WeakRefCountPtr() 
    {
        SetPtr(nullptr); 
    }

    WeakRefCountPtr(const WeakRefCountPtr<T>& other) 
    {
        SetPtr(other.ptr_); 
        AddWeakReference(); 
    }

    WeakRefCountPtr(const RefCountPtr<T>& other) 
    {
        SetPtr(other.Get()); 
        AddWeakReference(); 
    }

    WeakRefCountPtr<T>& operator=(const WeakRefCountPtr<T>& other) 
    {
        other.AddWeakReference(); 
        ReleaseWeakReference(); 
        SetPtr(other.ptr_); 
        return *this; 
    }

    WeakRefCountPtr<T>& operator=(const RefCountPtr<T>& other) 
    {
        ReleaseWeakReference(); 
        SetPtr(other.Get()); 
        AddWeakReference(); 
        return *this; 
    }

    ~WeakRefCountPtr() 
    {
        ReleaseWeakReference(); 
    }

    explicit operator bool() const 
    {
        return IsValid(); 
    }

    bool IsValid() const 
    {
        return count_ && count_->GetRefCount() > 0; 
    }

    RefCountPtr<T> Lock() const 
    {
        if(IsValid()) 
        { 
            RefCountPtr<T> ptr(ptr_); 
            ptr_->AddRef(); 
            return ptr; 
        } else return RefCountPtr<T>(); 
    }

    T* Get() const 
    {
        return IsValid() ? ptr_ : nullptr; 
    }

    T* operator->() const
    {
        return Get(); 
    }

    T& operator*() const 
    {
        return *Get(); 
    }

private: 
    void SetPtr(T* ptr) 
    {
        ptr_ = ptr; 
        count_ = ptr ? ptr->GetRefCountPtr() : nullptr; 
    }

    void AddWeakReference() 
    {
        if (count_) count_->AddWeakRef(); 
    }

    void ReleaseWeakReference() 
    {
        if (count_) 
        {
            count_->ReleaseWeak(); 

            if (!IsValid() && count_->GetWeakRefCount() == 0) 
            {
                delete count_; 
                ptr_ = nullptr; 
                count_ = nullptr; 
            }
        }
    }

    T* ptr_; 
    ReferenceCount* count_; 
};

}