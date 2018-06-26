#include "Oasis/Graphics/RenderTexture2D.h" 

namespace Oasis 
{

RenderTexture2D::RenderTexture2D(TextureFormat format, int width, int height, int multisample) 
    : Texture(TextureType::RENDER_TEXTURE_2D, format, width, height) 
    , multisample_(multisample) 
{

}

RenderTexture2D::~RenderTexture2D() {} 

void RenderTexture2D::Resize(int width, int height) 
{
    width_ = width; 
    height_ = height; 
    dirty_ = true; 
}

void RenderTexture2D::SetSampleCount(int samples) 
{
    if (multisample_ != samples) 
    {
        multisample_ = samples; 
        dirtyParams_ = true; 
    }
}

}