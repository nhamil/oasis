#include "Oasis/Graphics/Texture.h" 

#include "Oasis/Graphics/Texture2D.h" 

namespace Oasis 
{

void Texture::FlushToGPU() 
{
    if (dirty_) 
    {
        UploadToGPU(); 
    }

    dirty_ = false; 
}

Texture2D* Texture::GetTexture2D() 
{
    if (type_ == TextureType::TEXTURE_2D) 
    {
        return (Texture2D*) this; 
    }
    else 
    {
        return nullptr; 
    }
}

}