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

    void Update(float dt, uint32 count, Entity* entities) override 
    {
        Logger::Debug("Update Movement System (dt = ", dt, ")"); 

        for (uint32 i = 0; i < count; i++) 
        {
            Entity& e = entities[i]; 
            Position* pos = e.Get<Position>(); 
            Velocity* vel = e.Get<Velocity>(); 

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

    EventManager eventManager; 
    TestEventHandler handler; 

    eventManager.Subscribe<TestEvent>(&handler, TestEventHandler::HandleTestEvent); 
    eventManager.Subscribe<TestEvent>(&handler, TestEventHandler::HandleTestEvent2); 
    eventManager.SendEvent(new TestEvent()); 

    eventManager.Unsubscribe<TestEvent>(&handler, TestEventHandler::HandleTestEvent2); 
    eventManager.SendEvent(new TestEvent()); 

    Scene scene; 
    EntityFilter filter = EntityFilter().Include<Position>(); 

    for (int i = 0; i < 1; i++) 
    {
        Entity entity = scene.CreateEntity(); 

        Logger::Info("Match: ", filter.Matches(entity)); 

        entity.Attach<Position>(i, i * 2 + 1); 
        entity.Get<Position>()->Print(); 

        Logger::Info("Match: ", filter.Matches(entity)); 
    }

    Logger::Info("Done"); 

    return 0;
}
