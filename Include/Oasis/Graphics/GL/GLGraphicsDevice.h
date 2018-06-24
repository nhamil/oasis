#pragma once 

#include "Oasis/Graphics/GraphicsDevice.h" 
#include "Oasis/Graphics/GL/GLIndexBuffer.h" 
#include "Oasis/Graphics/GL/GLShader.h" 
#include "Oasis/Graphics/GL/GLVertexBuffer.h" 

namespace Oasis 
{

class GLIndexBuffer; 
class GLShader; 
class GLVertexBuffer; 

struct OASIS_API GLContext 
{
    struct AttribArray 
    {
        GLuint64 offset = 0; 
        GLuint count = 0;
        GLuint size = 0; 
        GLuint vbo = 0; 
    };

    struct Framebuffer 
    {
        GLenum drawBuffer[4] {}; 
        GLuint colorBuffer[4] {}; 
        GLuint depthBuffer = 0; 
        unsigned numBuffers = 0; 
    };

    Framebuffer fboContents; 
    AttribArray attribArray[8] {}; 
    bool attribArrayEnabled[8] {};  
    GLuint texture[8] {};
    GLuint ibo = 0;  
    GLuint vbo = 0; 
    GLuint textureUnit = 0; 
    GLuint program = 0; 
    GLuint fbo = 0; 
};

class OASIS_API GLGraphicsDevice : public GraphicsDevice 
{
public: 
    GLGraphicsDevice(); 
    ~GLGraphicsDevice(); 

    void SetClearColor(float r, float g, float b) override;   

    void Clear(bool colorBuffer = true, bool depthBuffer = true) override;   

    void SetViewport(int x, int y, int w, int h) override;   

    void SetShader(Shader* shader) override;   

    void SetIndexBuffer(IndexBuffer* indexBuffer) override;  

    void SetVertexBuffers(int count, VertexBuffer** vertexBuffers) override; 

    void SetTextureUnit(int unit, Texture* texture) override; 

    virtual int GetMaxRenderTargetCount() override;  

    virtual void ClearRenderTargets(bool color, bool depth) override;  

    virtual void SetRenderTarget(int index, RenderTexture2D* texture) override;  

    virtual void SetDepthTarget(RenderTexture2D* texture) override;  

    void Draw(Primitive prim, int start, int triCount) override;   

    void DrawIndexed(Primitive prim, int start, int triCount) override;   

    inline Shader* GetShader() override { return shaderProgram_; }   

    inline IndexBuffer* GetIndexBuffer() override { return indexBuffer_; }   

    inline int GetVertexBufferCount() override { return vertexBuffers_.size(); }    

    inline VertexBuffer* GetVertexBuffer(int index) override { return vertexBuffers_[index]; }    
    
    inline int GetMaxTextureUnitCount() override { return 8; } 

    inline Texture* GetTextureUnit(int unit) override { return textureUnits_[unit]; }  

    Shader* CreateShader(const std::string& vSource, const std::string& fSource) override;   

    IndexBuffer* CreateIndexBuffer(int numElements, BufferUsage usage = BufferUsage::DYNAMIC) override;   

    VertexBuffer* CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage = BufferUsage::DYNAMIC) override;   

    Texture2D* CreateTexture2D(TextureFormat format, int width, int height) override; 

    RenderTexture2D* CreateRenderTexture2D(TextureFormat format, int width, int height, int multisamples = 1) override; 

    // TODO implement 
    void OnDestroy(Texture* texture) { (void) texture; } 
    void OnDestroy(VertexBuffer* buffer) { (void) buffer; } 
    void OnDestroy(IndexBuffer* buffer) { (void) buffer; } 
    void OnDestroy(Shader* shader) { (void) shader; } 

    bool SetVertexAttribArrayEnabled(GLuint index, bool enabled); 
    bool SetVertexAttribPointer(GLuint index, GLuint vbo, GLuint count, GLuint size, GLuint64 offset); 
    bool BindVertexBuffer(GLuint id); 
    bool BindIndexBuffer(GLuint id); 
    bool BindShader(GLuint id); 
    bool BindTexture2D(GLuint index, GLuint id); 
    bool BindFramebuffer(GLuint id); 

private: 
    void PreRender();   
    void PostRender(); 

    bool PrepareToDraw(); 

    bool HasCustomRenderTarget(); 
    void SetupFramebuffer(); 

    Vector4 clearColor_; 
    Vector4 viewport_; 
    GLShader* shaderProgram_; 
    GLIndexBuffer* indexBuffer_; 
    std::vector<GLVertexBuffer*> vertexBuffers_; 
    Texture* textureUnits_[8]; 
    Texture* renderTargets_[4]; 
    Texture* depthTarget_ = nullptr; 
    GLuint fbo_ = 0; 

    GLContext context_; 
};

}