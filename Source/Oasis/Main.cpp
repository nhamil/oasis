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

    void OnUpdate(Scene& scene, uint32 count, const EntityId* entities, float dt) override 
    {
        Logger::Debug("Update Movement System (dt = ", dt, ")"); 
        Logger::Debug("Count: ", count); 

        for (uint32 i = 0; i < count; i++) 
        {
            Entity e = scene.GetEntity(entities[i]); 
            Position* pos = e.Get<Position>(); 
            Velocity* vel = e.Get<Velocity>(); 

            Logger::Info("ID: ", e.GetId().id, " ", e.GetId().version); 
            pos->Print(); 
            vel->Print(); 

            pos->x += vel->dx * dt; 
            pos->y += vel->dy * dt; 
        }
    }
};

int main(int argc, char** argv)
{
    (void) argc; 
    (void) argv; 

    Logger::Info("Hello, Oasis!"); 

    Scene scene; 
    
    scene.AddSystem(new MovementSystem()); 

    for (int i = 0; i < 3; i++) 
    {
        auto e = scene.CreateEntity(); 
        e.Attach<Position>(i, i + 1); 
        e.Attach<Velocity>(i, 2 * i + 1); 
    }

    scene.Update(1.0f / 16.0f); 
    Logger::Info("New Frame"); 
    scene.Update(1.0f / 16.0f); 

    Logger::Info("Done"); 

    return 0;
}
