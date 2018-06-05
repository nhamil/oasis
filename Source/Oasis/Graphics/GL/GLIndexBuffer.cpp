#include "Oasis/Graphics/IndexBuffer.h"

#include <string.h>

#include <GL/glew.h> 

using namespace std;

namespace Oasis
{

void IndexBuffer::CreateResource()
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetElementCount() * sizeof (short), NULL, GL_DYNAMIC_DRAW);
}

void IndexBuffer::UploadResource()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetElementCount() * sizeof (short), &data_[0], GL_DYNAMIC_DRAW);
}

void IndexBuffer::DestroyResource()
{
    if (id)
    {
        glDeleteBuffers(1, &id);
        id = 0;
    }
}

}

