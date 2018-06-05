#include "Oasis/Graphics/VertexArray.h" 

namespace Oasis 
{

VertexArray::VertexArray() {}
VertexArray::~VertexArray() {} 

void VertexArray::Update() {}  

void VertexArray::SetIndexBuffer(IndexBuffer* ib) 
{
    indexBuffer_ = ib; 
} 

void VertexArray::SetVertexBuffers(int count, VertexBuffer** vbs) 
{
    vertexBuffers_.clear(); 
    for (int i = 0; i < count; i++) vertexBuffers_.push_back(vbs[i]); 
} 

}