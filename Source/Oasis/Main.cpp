#include <iostream>

#include <Oasis/Oasis.h> 

#include <Oasis/Core/EventManager.h> 
#include <Oasis/Scene/Scene.h> 
#include <Oasis/Scene/System.h> 

using namespace std;
using namespace Oasis; 

// struct Tester : public Component
// {
//     Tester() 
//     {
//         cout << "ctor" << endl; 
//     }

//     Tester(const Tester& other) 
//     {
//         cout << "copy" << endl; 
//     }

//     Tester& operator=(const Tester& other) 
//     {
//         cout << "assign" << endl; 
//         return *this; 
//     }

//     ~Tester() 
//     {
//         cout << "dtor" << endl; 
//     }

//     void Print() 
//     {
//         cout << "Printing test" << endl; 
//     }
// };

struct Position : public Component
{
    Position() = default; 
    Position(const Position& other) : x(other.x), y(other.y) {} 
    Position(float x, float y) : x(x), y(y) {} 

    void Print() const
    {
        Logger::Info("(", x, ", ", y, ")"); 
    }

    float x = 0;
    float y = 0; 
};

struct Velocity : public Component
{
    Velocity() = default; 
    Velocity(const Velocity& other) : dx(other.dx), dy(other.dy) {} 
    Velocity(float x, float y) : dx(x), dy(y) {} 

    void Print() const
    {
        Logger::Info("(", dx, ", ", dy, ")"); 
    }

    float dx = 0;
    float dy = 0; 
};

class MovementSystem : public EntitySystem 
{
public: 
    MovementSystem() 
    {
        Include<Position>(); 
        Include<Velocity>(); 
    }

    void OnUpdate(EntityManager* entityManager, uint32 count, EntityId* entities, float dt) override 
    {
        Logger::Debug("Update Movement System (dt = ", dt, ")"); 

        for (uint32 i = 0; i < count; i++) 
        {
            EntityId e = entities[i]; 
            Position* pos = entityManager->GetComponent<Position>(e); 
            Velocity* vel = entityManager->GetComponent<Velocity>(e); 

            pos->x += vel->dx * dt; 
            pos->y += vel->dy * dt; 
        }
    }
};

class TestEvent : public Event {};

class TestEventHandler 
{
public: 
    void HandleTestEvent(TestEvent* event) 
    {
        Logger::Info("Handling TestEvent: ", event); 
    }

    void HandleTestEvent2(TestEvent* event) 
    {
        Logger::Info("Handling TestEvent 2: ", event); 
    }
};

int main(int argc, char** argv)
{
    (void) argc; 
    (void) argv; 

    Logger::Info("Hello, Oasis!"); 

    EntityManager manager; 
    EntityFilter filter; 
    filter.Include<Position>(); 

    manager.GetFilterCache().GetFilterId(filter); 

    auto id = manager.CreateEntityId(); 

    Logger::Info("Done"); 

    return 0;
}
