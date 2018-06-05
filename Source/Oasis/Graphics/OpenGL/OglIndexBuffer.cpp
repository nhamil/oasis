#include "Oasis/Graphics/IndexBuffer.h"

#include <string.h>

#include <GL/glew.h> 

using namespace std;

namespace Oasis
{

IndexBuffer::IndexBuffer(int elements, BufferUsage usage)
    : IndexBuffer(elements, usage)
    , id_(0)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof (short), NULL, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() { ReleaseGpuData(); }

void IndexBuffer::UploadGpuData(int bytes, const void* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, GL_DYNAMIC_DRAW);
}

void IndexBuffer::UploadGpuSubData(int offset, int bytes, const void* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, bytes, data);
}

void IndexBuffer::ReleaseGpuData()
{
    if (id_)
    {
        glDeleteBuffers(1, &id_);
        id_ = 0;
    }
}

}

