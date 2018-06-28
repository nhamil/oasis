#include "Oasis/Graphics/Texture2D.h" 

#include <string.h> 

namespace Oasis 
{

Texture2D::Texture2D(TextureFormat format, int width, int height) 
    : Texture(TextureType::TEXTURE_2D, format, width, height) 
{
    data_.resize(width * height * GetTextureFormatByteCount(format)); 
}

Texture2D::~Texture2D() {}

void Texture2D::SetMipmapCount(int levels) 
{
    if (levels < 1) levels = 1; 

    if (mipmaps_ != levels) 
    {
        mipmaps_ = levels; 
        dirtyParams_ = true; 
    }
}

void Texture2D::GetData(int startx, int starty, int width, int height, void* out) const 
{
    char* pixels = (char*) out; 

    int pxSize = GetTextureFormatByteCount(format_); 

    for (int y = 0; y < height; y++) 
    {
        int startIndex = (startx + (y + starty) * width_) * pxSize; 
        int outIndex = y * width * pxSize; 
        int size = width * pxSize; 

        memcpy(&pixels[outIndex], &data_[startIndex], size); 
    }
}

void Texture2D::Resize(TextureFormat format, int width, int height) 
{
    Texture::Resize(format, width, height); 

    data_.resize(width * height * GetTextureFormatByteCount(format_)); 
}

void Texture2D::SetData(int startx, int starty, int width, int height, const void* in) 
{
    dirtyData_ = true; 

    char* pixels = (char*) in; 

    int pxSize = GetTextureFormatByteCount(format_); 

    for (int y = 0; y < height; y++) 
    {
        int startIndex = (startx + (y + starty) * width_) * pxSize; 
        int outIndex = y * width * pxSize; 
        int size = width * pxSize; 

        memcpy(&data_[startIndex], &pixels[outIndex], size); 
    }
}

}