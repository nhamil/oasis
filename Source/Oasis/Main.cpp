#include <iostream>

#include <Oasis/Core/ClassId.h> 
#include <Oasis/Math/MathUtil.h>

using namespace std;
using namespace Oasis; 

struct Position 
{
    float x, y; 
}; 

int main(void)
{
    cout << "Hello, Oasis!" << endl;

    cout << "ID for Vector2: " << GetClassId<Vector2>() << endl; 
    cout << "ID for Vector2: " << GetClassId<Vector3>() << endl; 
    cout << "ID for Vector2: " << GetClassId<Vector4>() << endl; 
    cout << "ID for float: " << GetClassId<float>() << endl; 

    return 0;
}
