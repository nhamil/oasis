#pragma once 

#include "Oasis/Graphics/VertexBuffer.h" 

#include <GL/glew.h> 

namespace Oasis 
{

class GLGraphicsDevice; 

class OASIS_API GLVertexBuffer : public VertexBuffer 
{
public: 
    GLVertexBuffer(GLGraphicsDevice* graphicsDevice, int startElements, const VertexFormat& format, BufferUsage usage); 
    ~GLVertexBuffer(); 

    inline GLuint GetId() const { return id_; } 

private: 
    void Upload() override; 
    void Create(); 
    void Destroy(); 

    GLGraphicsDevice* graphics_; 
    GLuint id_ = 0; 
};

}