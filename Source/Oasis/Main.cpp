#include <iostream>

#include <Oasis/Oasis.h> 

#include <Oasis/Scene/ECS.h> 
#include <Oasis/Scene/Component.h> 
#include <Oasis/Scene/ComponentPool.h> 

using namespace std;
using namespace Oasis; 

struct Tester 
{
    Tester() 
    {
        cout << "ctor" << endl; 
    }

    Tester(const Tester& other) 
    {
        cout << "copy" << endl; 
    }

    Tester& operator=(const Tester& other) 
    {
        cout << "assign" << endl; 
        return *this; 
    }

    ~Tester() 
    {
        cout << "dtor" << endl; 
    }

    void Print() 
    {
        cout << "Printing test" << endl; 
    }
};

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

int main(int argc, char** argv)
{
    cout << "Hello, Oasis!" << endl;

    cout << "ID for Vector2: " << GetClassId<Vector2>() << endl; 
    cout << "ID for Vector2: " << GetClassId<Vector3>() << endl; 
    cout << "ID for Vector2: " << GetClassId<Vector4>() << endl; 
    cout << "ID for float: " << GetClassId<float>() << endl; 

    ComponentPool<Position> pool; 

    uint32 a, b, c, d; 

    Position tmp; 

    a = pool.CreateComponent(&tmp); 

    Logger::Info("Id: ", a); 

    ((Position*) pool.GetComponent(a))->Print(); 

    tmp = { 3, 4 }; 
    b = pool.CreateComponent(&tmp); 
    ((Position*) pool.GetComponent(b))->Print(); 

    pool.DestroyComponent(a); 

    tmp = { 5, 6 }; 
    a = pool.CreateComponent(&tmp); 
    ((Position*) pool.GetComponent(a))->Print(); 

    return 0;
}
