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

    void Resize(int width, int height); 
    void SetData(int x, int y, int width, int height, const void* in); 

    int GetMipmapCount() const { return mipmaps_; } 

    void SetMipmapCount(int levels); 

protected: 
    std::vector<char> data_; 
    int mipmaps_ = 1; 
};

}