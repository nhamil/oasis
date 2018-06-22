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

void Texture2D::Resize(int width, int height) 
{
    if (width != width_ || height != height_) 
    {
        width_ = width; 
        height_ = height; 

        data_.resize(width * height * GetTextureFormatByteCount(format_)); 
        dirty_ = true; 
    }
}

void Texture2D::SetData(int startx, int starty, int width, int height, const void* in) 
{
    dirty_ = true; 
    
    char* pixels = (char*) in; 

    int pxSize = GetTextureFormatByteCount(format_); 

    for (int y = 0; y < height; y++) 
    {
        // for (int x = 0; x < width; x++) 
        // {
        //     data_[(x + startx + (y + starty) * width) * 4 + 0] = pixels[(x + y * width) * 4 + 0]; 
        //     data_[(x + startx + (y + starty) * width) * 4 + 1] = pixels[(x + y * width) * 4 + 1]; 
        //     data_[(x + startx + (y + starty) * width) * 4 + 2] = pixels[(x + y * width) * 4 + 2]; 
        //     data_[(x + startx + (y + starty) * width) * 4 + 3] = pixels[(x + y * width) * 4 + 3]; 
        // }
        int startIndex = (startx + (y + starty) * width_) * pxSize; 
        int outIndex = y * width * pxSize; 
        int size = width * pxSize; 

        memcpy(&data_[startIndex], &pixels[outIndex], size); 
    }
}

}