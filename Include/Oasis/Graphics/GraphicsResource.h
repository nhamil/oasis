#pragma once 

#include "Oasis/Common.h" 

#include <GL/glew.h> 

class OASIS_API GraphicsResource 
{
public: 
    virtual ~GraphicsResource() = default; 

protected: 
    GLuint id = 0; 
};