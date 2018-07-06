#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Scene/Component.h" 

namespace Oasis 
{

class Material; 
class Mesh; 

struct OASIS_API MeshContainer : public Component 
{
    WeakRefCountPtr<Mesh> mesh; 
    WeakRefCountPtr<Material> material; 
};

}