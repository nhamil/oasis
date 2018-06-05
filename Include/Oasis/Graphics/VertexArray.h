#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/GraphicsResource.h" 

#include <vector>

namespace Oasis
{

class IndexBuffer;
class VertexBuffer;

class OASIS_API VertexArray : GraphicsResource 
{
public:
    void Update(); 

    void SetIndexBuffer(IndexBuffer* ib); 
    void SetVertexBuffers(int count, VertexBuffer** vbs); 
    inline void SetVertexBuffer(VertexBuffer* vb) { SetVertexBuffers(1, &vb); }

    inline bool HasIndexBuffer() const { return indexBuffer_ != NULL; }
    inline IndexBuffer* GetIndexBuffer() const { return indexBuffer_; }

    int GetVertexBufferCount() const { return vertexBuffers_.size(); }
    VertexBuffer* GetVertexBuffer(int index) const { return vertexBuffers_[index]; }

private:
    friend class Graphics; 

    VertexArray(); 
    ~VertexArray(); 

    OASIS_NO_COPY(VertexArray) 
    
    std::vector<VertexBuffer*> vertexBuffers_;
    IndexBuffer* indexBuffer_;
};

}
