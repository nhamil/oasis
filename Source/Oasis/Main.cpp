#include <iostream>

#include <Oasis/Oasis.h> 
#include <Oasis/Core/ClassId.h> 
#include <Oasis/Math/MathUtil.h>

using namespace std;
using namespace Oasis; 

struct Position 
{
    float x, y; 
}; 

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

int main(int argc, char** argv)
{
    cout << "Hello, Oasis!" << endl;

    cout << "ID for Vector2: " << GetClassId<Vector2>() << endl; 
    cout << "ID for Vector2: " << GetClassId<Vector3>() << endl; 
    cout << "ID for Vector2: " << GetClassId<Vector4>() << endl; 
    cout << "ID for float: " << GetClassId<float>() << endl; 

    RefCounted<Tester> ptr = new Tester(); 

    cout << ptr.GetRefCount() << endl; 

    {
        auto ptr2 = ptr; 

        cout << ptr.GetRefCount() << endl; 
    }

    ptr->Print(); 

    cout << ptr.GetRefCount() << endl; 

    cin.get(); 

    return 0;
}
