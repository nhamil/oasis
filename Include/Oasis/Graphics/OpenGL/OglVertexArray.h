#pragma once

#include "Oasis/Oasis.h"

#include "Oasis/Graphics/VertexArray.h"
#include "Oasis/Graphics/IndexBuffer.h"
#include "Oasis/Graphics/VertexBuffer.h"

#include <vector>

namespace Oasis
{

class OASIS_API OGLVertexArray : public VertexArray
{
public:
    OGLVertexArray();
    ~OGLVertexArray();

private:
    void SetGpuBuffers(int count, VertexBuffer** vbs, IndexBuffer* ib);
    void ReleaseGpuData() {}

    IndexBuffer* indexBuffer_;
    std::vector<VertexBuffer*> vertexBuffers_;
};

}
