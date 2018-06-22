#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Graphics/Types.h" 

namespace Oasis 
{

class Texture2D; 

class OASIS_API Texture : public ReferenceCounted 
{
public: 
    Texture(TextureType type, TextureFormat format, int width, int height) : type_(type), format_(format), width_(width), height_(height) {} 
    virtual ~Texture() {} 

    void FlushToGPU(); 

    inline TextureType GetType() const { return type_; } 

    inline TextureFormat GetFormat() const { return format_; } 

    inline int GetWidth() const { return width_; } 

    inline int GetHeight() const { return height_; } 

    Texture2D* GetTexture2D(); 

protected: 
    virtual void UploadToGPU() = 0; 

    TextureType type_; 
    TextureFormat format_; 
    int width_; 
    int height_; 
    bool dirty_ = true; 
};

}