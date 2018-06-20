#pragma once 

#include "Oasis/Graphics/IndexBuffer.h" 

#include <GL/glew.h> 

namespace Oasis 
{

class GLGraphicsDevice; 

class OASIS_API GLIndexBuffer : public IndexBuffer 
{
public: 
    GLIndexBuffer(GLGraphicsDevice* graphicsDevice, int startElements, BufferUsage usage); 
    ~GLIndexBuffer(); 

    inline GLuint GetId() const { return id_; } 

private: 
    void Upload() override; 
    void Create(); 
    void Destroy(); 

    GLGraphicsDevice* graphics_; 
    GLuint id_ = 0; 
};

}