#pragma once 

#include "Oasis/Common.h" 

#include <cstring> 

namespace Oasis
{

class OASIS_API Event {}; 

class OASIS_API EventCallbackBase  
{
public: 
    EventCallbackBase(int priority) : priority(priority) {} 
    virtual ~EventCallbackBase() {} 

    virtual void Invoke(Event*) = 0; 

    virtual bool Equals(EventCallbackBase* callback) const = 0; 

    const int priority; 
};

template <class EventType, class Callee> 
class OASIS_API ClassEventCallback : public EventCallbackBase 
{
public: 
    using Callback = void (Callee::*)(EventType*); 

    ClassEventCallback(Callee* callee, Callback callback, int priority) 
        : EventCallbackBase(priority), callee_(callee), callback_(callback) {} 

    void Invoke(Event* event) override
    {
        if (callee_) (*callee_.*callback_)((EventType*) event); 
    }

    bool Equals(EventCallbackBase* callback) const 
    {
        auto other = (decltype(this)) callback; 

        return callee_ == other->callee_ && callback_ == other->callback_ && priority == other->priority; 
    }

private: 
    Callee* callee_; 
    Callback callback_; 
};

class OASIS_API EventManager 
{
public:
    template <class EventType, class Callee> 
    using Callback = void (Callee::*)(EventType*); 

    template <class EventType, class Callee> 
    void Subscribe(Callee* callee, Callback<EventType, Callee> callbackFunction, int priority = 1000) 
    {
        Subscribe(GetClassId<EventType>(), new ClassEventCallback<EventType, Callee>(callee, callbackFunction, priority)); 
    } 

    template <class EventType, class Callee> 
    bool Unsubscribe(Callee* callee, Callback<EventType, Callee> callbackFunction, int priority = 1000) 
    {
        ClassEventCallback<EventType, Callee> callback(callee, callbackFunction, priority); 
        return Unsubscribe(GetClassId<EventType>(), &callback); 
    } 

    template <class EventType> void SendEvent(EventType* event) 
    {
        SendEvent(GetClassId<EventType>(), event); 
    }

private: 
    void Subscribe(ClassId eventId, EventCallbackBase* callback);   
    bool Unsubscribe(ClassId eventId, EventCallbackBase* callback); 

    void SendEvent(ClassId eventId, Event* event);  

    std::unordered_map<ClassId, std::vector<EventCallbackBase*>> callbacks_; 
};

}