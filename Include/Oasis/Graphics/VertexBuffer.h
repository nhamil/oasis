#pragma once

#include "Oasis/Common.h"

#include "Oasis/Graphics/VertexFormat.h"

namespace Oasis
{

class OASIS_API VertexBuffer : public GraphicsObject 
{
public:
    VertexBuffer(int startElements, const VertexFormat& format, BufferUsage usage);
    virtual ~VertexBuffer(); 
    
    void FlushToGPU();

    inline const VertexFormat& GetVertexFormat() const { return format_; }
    inline BufferUsage GetBufferUsage() const { return usage_; } 
    inline int GetElementCount() const { return data_.size() / format_.GetSize(); }
    void GetData(int start, int numElements, void* out) const;

    void SetVertexFormat(const VertexFormat& format); 
    void SetBufferUsage(BufferUsage usage); 
    void SetElementCount(int numElements);
    void SetData(int start, int numElements, const void* in);

protected:
    virtual void UploadToGPU() = 0; 

    BufferUsage usage_; 
    VertexFormat format_;
    std::vector<float> data_;
    bool dirty_ = true;
};

}
