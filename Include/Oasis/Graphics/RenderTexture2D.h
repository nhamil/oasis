#pragma once 

#include "Oasis/Graphics/Texture.h" 

namespace Oasis 
{

class OASIS_API RenderTexture2D : public Texture 
{
public: 
    RenderTexture2D(TextureFormat format, int width, int height); 
    virtual ~RenderTexture2D(); 

    void Resize(int width, int height); 

private: 
};

}