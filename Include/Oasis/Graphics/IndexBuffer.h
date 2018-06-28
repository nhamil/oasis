#pragma once

#include "Oasis/Common.h"

#include "Oasis/Graphics/Types.h" 

#include <vector>

namespace Oasis
{

class OASIS_API IndexBuffer : public GraphicsObject 
{
public:
    IndexBuffer(int startElements, BufferUsage usage); 
    virtual ~IndexBuffer(); 

    // upload data if it is dirty 
    void Update();

    inline BufferUsage GetBufferUsage() const { return usage_; } 
    inline int GetElementCount() const { return data_.size(); }
    void GetData(int start, int numElements, short* out) const;

    void SetBufferUsage(BufferUsage usage); 
    void SetElementCount(int numElements);
    void SetData(int start, int numElements, const short* in);

protected:
    virtual void UploadToGPU() = 0; 

    BufferUsage usage_; 
    std::vector<short> data_;
    bool dirty_ = true;
};

}
