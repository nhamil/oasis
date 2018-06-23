#pragma once 

#include "Oasis/Graphics/Texture.h" 

namespace Oasis 
{

class OASIS_API Texture2D : public Texture 
{
public: 
    Texture2D(TextureFormat format, int width, int height); 
    virtual ~Texture2D(); 

    void GetData(int x, int y, int width, int height, void* out) const; 

    int GetMipmapCount() const { return mipmaps_; } 

    void Resize(int width, int height); 

    void SetMipmapCount(int levels); 

    void SetData(int x, int y, int width, int height, const void* in); 

protected: 
    std::vector<char> data_; 
    int mipmaps_ = 1; 
};

}