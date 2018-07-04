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
    Position(const Position& other) = default;  
    Position(float x, float y) : x(x), y(y) {} 

    void Print() const
    {
        Logger::Info("Pos(", x, ", ", y, ")"); 
    }

    float x = 0;
    float y = 0; 
};

struct Velocity : public Component
{
    Velocity() = default; 
    Velocity(const Velocity& other) = default; 
    Velocity(float x, float y) : dx(x), dy(y) {} 

    void Print() const
    {
        Logger::Info("Vel(", dx, ", ", dy, ")"); 
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

    void OnUpdate(EntityManager* entityManager, uint32 count, const EntityId* entities, float dt) override 
    {
        Logger::Debug("Update Movement System (dt = ", dt, ")"); 

        EntityManager* em = GetEntityManager(); 

        for (uint32 i = 0; i < count; i++) 
        {
            EntityId e = entities[i]; 
            Position* pos = em->GetComponent<Position>(e); 
            Velocity* vel = em->GetComponent<Velocity>(e); 

            Logger::Info("ID: ", e.id, " ", e.version); 
            Logger::Info(pos, " ", vel); 
            pos->Print(); 
            vel->Print(); 

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

    Scene scene; 
    MovementSystem movementSystem; 

    scene.AddSystem(movementSystem); 

    EntityManager& em = scene.GetEntityManager(); 

    for (int i = 0; i < 3; i++) 
    {
        auto e = em.CreateEntityId(); 
        Logger::Info("ID: ", e.id, " ", e.version); 
        em.AttachComponent<Position>(e, i, i + 1)->Print(); 
        em.AttachComponent<Velocity>(e, i, 2 * i + 1)->Print();
        
        Logger::Info(em.GetComponent<Position>(e), " ", em.GetComponent<Velocity>(e)); 
    }

    Logger::Info(""); 

    for (int i = 0; i < 3; i++) 
    {
        auto e = EntityId(i, 1); 
        Logger::Info("ID: ", e.id, " ", e.version); 
        em.GetComponent<Position>(e)->Print(); 
        em.GetComponent<Velocity>(e)->Print();
        
        Logger::Info(em.GetComponent<Position>(e), " ", em.GetComponent<Velocity>(e)); 
    }

    Logger::Info(""); 

    scene.Update(1); 

    Logger::Info("Done"); 

    return 0;
}
