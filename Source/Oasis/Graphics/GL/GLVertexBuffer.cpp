#include "Oasis/Graphics/GL/GLVertexBuffer.h"

#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 
#include "Oasis/Graphics/GL/GLUtil.h" 

#include <string.h>

#include <GL/glew.h> 

using namespace std;

namespace Oasis
{

GLVertexBuffer::GLVertexBuffer(GLGraphicsDevice* graphics, int elemCount, const VertexFormat& format, BufferUsage usage) 
    : VertexBuffer(elemCount, format, usage) 
    , graphics_(graphics) 
{
    Create(); 
}

GLVertexBuffer::~GLVertexBuffer() 
{
    Destroy(); 
}

void GLVertexBuffer::Create()
{
    if (id_) return; 

    GLCALL(glGenBuffers(1, &id_));
    // GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id_));
    graphics_->BindVertexBuffer(id_); 
    GLCALL(glBufferData(GL_ARRAY_BUFFER, GetElementCount() * GetVertexFormat().GetSize() * sizeof (float), nullptr, GL_DYNAMIC_DRAW));
}

void GLVertexBuffer::UploadToGPU()
{
    if (!id_) Create(); 

    // GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id_));
    graphics_->BindVertexBuffer(id_); 
    GLCALL(glBufferData(GL_ARRAY_BUFFER, GetElementCount() * GetVertexFormat().GetSize() * sizeof (float), &data_[0], GL_DYNAMIC_DRAW));
}

void GLVertexBuffer::Destroy()
{
    if (id_)
    {
        std::vector<VertexBuffer*> keepBuffers; 
        bool change = false; 

        for (int i = 0; i < graphics_->GetVertexBufferCount(); i++) 
        {
            if (graphics_->GetVertexBuffer(i) == this) 
            {
                change = true; 
            }
            else 
            {
                keepBuffers.push_back(graphics_->GetVertexBuffer(i)); 
            }
        }

        if (change) 
        {
            graphics_->SetVertexBuffers(keepBuffers.size(), &keepBuffers[0]); 
        }

        GLCALL(glDeleteBuffers(1, &id_));
        id_ = 0;
    }
}

}

