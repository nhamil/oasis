#pragma once

#include "Oasis/Common.h"

#include "Oasis/Graphics/Graphics.h" 
#include "Oasis/Graphics/GraphicsResource.h" 
#include "Oasis/Graphics/VertexFormat.h"

#include <vector>

namespace Oasis
{

class OASIS_API VertexBuffer : public GraphicsResource 
{
public:
    void Update();

    inline const VertexFormat& GetVertexFormat() const { return format_; }
    inline BufferUsage GetBufferUsage() const { return usage_; } 
    inline int GetElementCount() const { return data_.size() / format_.GetSize(); }
    void GetData(int start, int numElements, float* out) const;

    void SetBufferUsage(BufferUsage usage); 
    void SetElementCount(int numElements);
    void SetData(int start, int numElements, const float* in);

private:
    friend class Graphics; 

    VertexBuffer(int startElements, const VertexFormat& format, BufferUsage usage = BufferUsage::DYNAMIC);
    ~VertexBuffer();

    OASIS_NO_COPY(VertexBuffer) 

    void CreateResource(); 
    void UploadResource(); 
    void DestroyResource(); 

    BufferUsage usage_; 
    VertexFormat format_;
    std::vector<float> data_;
    bool dirty_ = true;
};

}
