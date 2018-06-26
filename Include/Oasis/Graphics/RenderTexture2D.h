#pragma once 

#include "Oasis/Graphics/Texture.h" 

namespace Oasis 
{

class OASIS_API RenderTexture2D : public Texture 
{
public: 
    RenderTexture2D(TextureFormat format, int width, int height, int multisample); 
    virtual ~RenderTexture2D(); 

    int GetSampleCount() const { return multisample_; } 

    bool IsMultisampled() const { return multisample_ > 1; } 

    void SetSampleCount(int samples); 

    void Resize(int width, int height); 

protected: 
    int multisample_ = 1; 
};

}