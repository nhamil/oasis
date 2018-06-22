#include "Oasis/Graphics/GL/GLIndexBuffer.h"

#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 
#include "Oasis/Graphics/GL/GLUtil.h" 

#include <string.h>

#include <GL/glew.h> 

using namespace std;

namespace Oasis
{

GLIndexBuffer::GLIndexBuffer(GLGraphicsDevice* graphicsDevice, int startElements, BufferUsage usage) 
    : IndexBuffer(startElements, usage) 
    , graphics_(graphicsDevice) 
{
    Create(); 
}

GLIndexBuffer::~GLIndexBuffer() 
{
    Destroy(); 
}

void GLIndexBuffer::Create()
{
    if (id_) return; 

    GLCALL(glGenBuffers(1, &id_));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetElementCount() * sizeof (short), nullptr, GL_DYNAMIC_DRAW));
}

void GLIndexBuffer::UploadToGPU()
{
    if (!id_) Create(); 

    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetElementCount() * sizeof (short), &data_[0], GL_DYNAMIC_DRAW));
}

void GLIndexBuffer::Destroy()
{
    if (id_)
    {
        if (graphics_->GetIndexBuffer() == this) graphics_->SetIndexBuffer(nullptr); 

        GLCALL(glDeleteBuffers(1, &id_));
        id_ = 0;
    }
}

}

