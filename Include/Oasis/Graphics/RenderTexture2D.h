#pragma once 

#include "Oasis/Graphics/Texture.h" 

namespace Oasis 
{

class OASIS_API RenderTexture2D : public Texture 
{
public: 
    RenderTexture2D(TextureFormat format, int width, int height, int multisample); 
    virtual ~RenderTexture2D(); 

    virtual void ResolveTextureIfNeeded() = 0; 
    virtual void UpdateBackupTexture() = 0; 

    int GetSampleCount() const { return multisample_; } 

    bool IsMultisampled() const { return multisample_ > 1; } 

    void SetSampleCount(int samples); 

protected: 
    int multisample_ = 1; 
};

}