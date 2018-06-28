#pragma once 

#include "Oasis/Graphics/RenderTexture2D.h" 
#include "Oasis/Graphics/GL/GLUtil.h" 

namespace Oasis 
{

class GLGraphicsDevice; 
class GLTexture2D; 

class OASIS_API GLRenderTexture2D : public RenderTexture2D 
{
public: 
    GLRenderTexture2D(GLGraphicsDevice* graphics, TextureFormat format, int width, int height, int samples); 
    ~GLRenderTexture2D(); 

    void Update() override; 
    void ResolveTextureIfNeeded() override; 
    void UpdateBackupTexture() override; 

    GLuint GetMainId() const { return id_; } 
    GLuint GetBackupId() const { return backupId_; } 

    GLuint GetRenderbufferId() const { return renderbufferId_; } 

    void SetRenderedTo(); 

    void SetRTTParameters(); 
    void SetTextureParameters(); 

    bool IsInUse() const { return inUse_; } 
    void SetInUse(bool inUse) { inUse_ = inUse; } 

private: 
    void Create(); 
    void Destroy(); 

    void SetBackupParameters(bool force); 

    GLGraphicsDevice* graphics_; 
    GLuint id_ = 0; 
    GLuint backupId_ = 0; 
    GLuint renderbufferId_ = 0; 
    bool dirtyResolve_ = false; 
    bool dirtyBackup_ = false; 
    bool rttParameters_ = true; 
    bool inUse_ = false; 
};

}