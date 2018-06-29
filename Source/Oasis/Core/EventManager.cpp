#include "Oasis/Core/EventManager.h" 

#include <algorithm> 

namespace Oasis 
{

void EventManager::Subscribe(ClassId eventId, EventCallbackBase* callback) 
{
    auto& list = callbacks_[eventId]; 

    list.push_back(callback); 

    std::sort(list.begin(), list.end(), [&](EventCallbackBase* a, EventCallbackBase* b) -> bool { return a->priority - b->priority; });
}

bool EventManager::Unsubscribe(ClassId eventId, EventCallbackBase* remove) 
{
    auto it = callbacks_.find(eventId); 

    if (it != callbacks_.end()) 
    {
        auto& list = it->second; 

        for (auto iter = list.begin(); iter != list.end(); ++iter)  
        {
            if ((*iter)->Equals(remove)) 
            {
                list.erase(iter); 
                return true; 
            }
        }
    }

    return false; 
}


void EventManager::SendEvent(ClassId eventId, Event* event) 
{
    auto it = callbacks_.find(eventId); 

    if (it != callbacks_.end()) 
    {
        auto& list = it->second; 

        for (auto callback : list) 
        {
            callback->Invoke(event); 
        }
    }
}

}