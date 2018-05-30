#pragma once

#include "Oasis/Graphics/VertexBuffer.h"

#include <GL/glew.h>

#include <vector>

namespace Oasis
{

class OASIS_API OGLVertexBuffer : public VertexBuffer
{
public:
    OGLVertexBuffer(int elements, const VertexFormat& format, BufferUsage usage = BUFFER_USAGE_DYNAMIC);
    ~OGLVertexBuffer();

    GLuint GetId() const { return id_; };

private:
    void UploadGpuData(int bytes, const void* data);
    void UploadGpuSubData(int offset, int bytes, const void* data);
    void ReleaseGpuData();

    GLuint id_;
};

}
