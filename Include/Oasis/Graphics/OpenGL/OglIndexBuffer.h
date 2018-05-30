#pragma once

#include "Oasis/Graphics/IndexBuffer.h"

#include <GL/glew.h>

#include <vector>

namespace Oasis
{

class OASIS_API OGLIndexBuffer : public IndexBuffer
{
public:
    OGLIndexBuffer(int elements, BufferUsage usage = BUFFER_USAGE_DYNAMIC);
    ~OGLIndexBuffer();

    GLuint GetId() const { return id_; }

private:
    void UploadGpuData(int bytes, const void* data);
    void UploadGpuSubData(int offset, int bytes, const void* data);
    void ReleaseGpuData();

    GLuint id_;
};

}

