#pragma once

#include "Oasis/Common.h"

#include "Oasis/Graphics/BufferUsage.h" 
#include "Oasis/Graphics/Graphics.h" 
#include "Oasis/Graphics/GraphicsResource.h"

#include <vector>

namespace Oasis
{

class OASIS_API IndexBuffer : public GraphicsResource
{
public:
    // upload data if it is dirty 
    void Update();

    inline BufferUsage GetBufferUsage() const { return usage_; } 
    inline int GetElementCount() const { return data_.size(); }
    void GetData(int start, int numElements, short* out) const;

    void SetBufferUsage(BufferUsage usage); 
    void SetElementCount(int numElements);
    void SetData(int start, int numElements, const short* in);

private:
    friend class Graphics; 

    IndexBuffer(int startElements, BufferUsage usage = BufferUsage::DYNAMIC);
    ~IndexBuffer();

    OASIS_NO_COPY(IndexBuffer) 

    void CreateResource(); 
    void UploadResource(); 
    void DestroyResource(); 

    BufferUsage usage_; 
    std::vector<short> data_;
    bool dirty_ = true;
};

}
