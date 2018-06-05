#include "Oasis/Graphics/VertexBuffer.h"

#include <string.h>

namespace Oasis
{

VertexBuffer::VertexBuffer(int startElements, const VertexFormat& format, BufferUsage usage)
    : usage_(usage) 
    , format_(format)
{
    data_.resize(startElements * format.GetSize());
    CreateResource(); 
}

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::Update()
{
    if (dirty_) UploadResource(); 

    dirty_ = false;
}

void VertexBuffer::GetData(int start, int numElements, float* out) const
{
    int s = start * format_.GetSize();
    int e = numElements * format_.GetSize() * sizeof (float);

    memcpy(out, &data_[s], e);
}

void VertexBuffer::SetData(int start, int numElements, const float* in)
{
    dirty_ = true;
    start *= format_.GetSize();

    for (int i = 0; i < numElements * format_.GetSize(); i++)
    {
        data_[start + i] = in ? in[i] : 0;
    }
}

void VertexBuffer::SetElementCount(int numElements)
{
    if (data_.size() != (unsigned) numElements * format_.GetSize()) dirty_ = true;

    data_.resize(numElements * format_.GetSize());
}

}
