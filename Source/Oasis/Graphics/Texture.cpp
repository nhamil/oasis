#include "Oasis/Graphics/Texture.h" 

#include "Oasis/Graphics/Texture2D.h" 

namespace Oasis 
{

Texture::Texture(TextureType type, TextureFormat format, int width, int height) 
    : type_(type) 
    , format_(format)
    , width_(width)
    , height_(height) {} 

Texture::~Texture() {} 

Texture2D* Texture::GetTexture2D() 
{
    if (GetType() == TextureType::TEXTURE_2D) 
    {
        return (Texture2D*) this; 
    }
    else 
    {
        return nullptr; 
    }
}

void Texture::Resize(TextureFormat format, int width, int height) 
{
    if (format_ == format && width_ == width && height_ == height) return; 

    dirtyData_ = true; 
    format_ = format; 
    width_ = width; 
    height_ = height; 
}

void Texture::SetFilter(TextureFilter filter) 
{
    if (filter_ != filter) 
    {
        filter_ = filter; 
        dirtyParams_ = true; 
    }
}

void Texture::SetWrapMode(TextureWrapMode mode) 
{
    SetWrapModeX(mode); 
    SetWrapModeY(mode); 
}

void Texture::SetWrapModeX(TextureWrapMode mode) 
{
    if (wrapModeX_ != mode) 
    {
        wrapModeX_ = mode; 
        dirtyParams_ = true; 
    }
}

void Texture::SetWrapModeY(TextureWrapMode mode) 
{
    if (wrapModeY_ != mode) 
    {
        wrapModeY_ = mode; 
        dirtyParams_ = true; 
    }
}

}