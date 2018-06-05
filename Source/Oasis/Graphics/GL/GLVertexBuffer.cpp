#include "Oasis/Graphics/VertexBuffer.h"

#include <string.h>

#include <GL/glew.h> 

using namespace std;

namespace Oasis
{

void VertexBuffer::CreateResource()
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, GetElementCount() * GetVertexFormat().GetSize() * sizeof (short), NULL, GL_DYNAMIC_DRAW);
}

void VertexBuffer::UploadResource()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, GetElementCount() * GetVertexFormat().GetSize() * sizeof (short), &data_[0], GL_DYNAMIC_DRAW);
}

void VertexBuffer::DestroyResource()
{
    if (id)
    {
        glDeleteBuffers(1, &id);
        id = 0;
    }
}

}

