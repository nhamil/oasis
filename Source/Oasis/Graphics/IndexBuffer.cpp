#include "Oasis/Graphics/IndexBuffer.h"

#include <string.h>

namespace Oasis
{

IndexBuffer::IndexBuffer(int startElements, BufferUsage usage)
    : usage_(usage) 
{
    data_.resize(startElements);
}

IndexBuffer::~IndexBuffer() {}

void IndexBuffer::Flush()
{
    if (dirty_) Upload(); 

    dirty_ = false;
}

void IndexBuffer::GetData(int start, int numElements, short* out) const
{
    int s = start;
    int e = numElements * sizeof (short);

    memcpy(out, &data_[s], e);
}

void IndexBuffer::SetBufferUsage(BufferUsage usage) 
{
    usage_ = usage; 
}

void IndexBuffer::SetElementCount(int numElements)
{
    if (data_.size() != (unsigned) numElements) dirty_ = true;

    data_.resize(numElements);
}

void IndexBuffer::SetData(int start, int numElements, const short* in)
{
    dirty_ = true;

    for (int i = 0; i < numElements; i++)
    {
        data_[start + i] = in ? in[i] : 0;
    }
}

}
