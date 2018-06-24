#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/Parameter.h" 
#include "Oasis/Graphics/Types.h" 
#include "Oasis/Graphics/VertexFormat.h" 
#include "Oasis/Math/MathUtil.h"

#include <string>

namespace Oasis
{

class OASIS_API GraphicsDevice 
{
public: 
    virtual ~GraphicsDevice() {} 

    virtual void SetClearColor(float r, float g, float b) = 0;  

    virtual void Clear(bool colorBuffer = true, bool depthBuffer = true) = 0;  

    virtual void SetViewport(int x, int y, int w, int h) = 0;  

    virtual void SetShader(Shader* shader) = 0;  

    virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0; 

    virtual void SetVertexBuffers(int count, VertexBuffer** vertexBuffers) = 0; 

    inline void SetVertexBuffer(VertexBuffer* vertexBuffer) { SetVertexBuffers(1, &vertexBuffer);  } 

    virtual void SetTextureUnit(int unit, Texture* texture) = 0; 

    virtual int GetMaxRenderTargetCount() = 0; 

    virtual void ClearRenderTargets(bool color = true, bool depth = true) = 0; 

    virtual void SetRenderTarget(int index, RenderTexture2D* texture) = 0; 

    virtual void SetDepthTarget(RenderTexture2D* texture) = 0; 

    virtual void Draw(Primitive prim, int start, int triCount) = 0;  

    virtual void DrawIndexed(Primitive prim, int start, int triCount) = 0;  

    virtual Shader* GetShader() = 0;

    virtual IndexBuffer* GetIndexBuffer() = 0;  

    virtual int GetVertexBufferCount() = 0; 

    virtual VertexBuffer* GetVertexBuffer(int index) = 0;  
    
    virtual int GetMaxTextureUnitCount() = 0; 

    virtual Texture* GetTextureUnit(int unit) = 0; 

    virtual Shader* CreateShader(const std::string& vSource, const std::string& fSource) = 0;  

    virtual IndexBuffer* CreateIndexBuffer(int numElements, BufferUsage usage = BufferUsage::DYNAMIC) = 0;  

    virtual VertexBuffer* CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage = BufferUsage::DYNAMIC) = 0;  

    virtual Texture2D* CreateTexture2D(TextureFormat format, int width, int height) = 0; 

    virtual RenderTexture2D* CreateRenderTexture2D(TextureFormat format, int width, int height, int multisamples = 1) = 0; 

private: 
    friend class Engine; 

    virtual void PreRender() = 0;  
    virtual void PostRender() = 0;  
};

}
