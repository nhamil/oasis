#include "Oasis/Graphics/OpenGL/OGLVertexBuffer.h"

#include <string.h>

#include <iostream>

using namespace std;

namespace Oasis
{

OGLVertexBuffer::OGLVertexBuffer(int elements, const VertexFormat& format, BufferUsage usage)
    : VertexBuffer(elements, format, usage)
    , id_(0)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, elements * format.GetSize() * sizeof (float), NULL, GL_DYNAMIC_DRAW);
}

OGLVertexBuffer::~OGLVertexBuffer() { ReleaseGpuData(); }

void OGLVertexBuffer::ReleaseGpuData()
{
    if (id_)
    {
        glDeleteBuffers(1, &id_);
        id_ = 0;
    }
}

void OGLVertexBuffer::UploadGpuData(int bytes, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_DYNAMIC_DRAW);
}

void OGLVertexBuffer::UploadGpuSubData(int offset, int bytes, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferSubData(GL_ARRAY_BUFFER, offset, bytes, data);
}

}
