#include "Oasis/Graphics/VertexBuffer.h"

#include <string.h>

namespace Oasis
{

VertexBuffer::VertexBuffer(int startElements, const VertexFormat& format, BufferUsage usage)
    : usage_(usage) 
    , format_(format)
{
    data_.resize(startElements * format.GetSize());
}

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::Flush()
{
    if (dirty_) Upload(); 

    dirty_ = false;
}

void VertexBuffer::GetData(int start, int numElements, void* out) const
{
    int s = start * format_.GetSize();
    int e = numElements * format_.GetSize() * sizeof (float);

    memcpy(out, &data_[s], e);
}

void VertexBuffer::SetData(int start, int numElements, const void* in)
{
    dirty_ = true;
    start *= format_.GetSize();

    const float* arr = (const float*) in; 

    for (int i = 0; i < numElements * format_.GetSize(); i++)
    {
        data_[start + i] = in ? arr[i] : 0;
    }
}

void VertexBuffer::SetElementCount(int numElements)
{
    if (data_.size() != (unsigned) numElements * format_.GetSize()) dirty_ = true;

    data_.resize(numElements * format_.GetSize());
}

}
