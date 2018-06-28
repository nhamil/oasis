#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Graphics/Types.h" 

namespace Oasis 
{

class Texture2D; 

class OASIS_API Texture : public GraphicsObject 
{
public: 
    Texture(TextureType type, TextureFormat format, int width, int height); 

    virtual ~Texture();  

    virtual void Update() = 0; 

    Texture2D* GetTexture2D(); 

    inline TextureType GetType() const { return type_; }  

    inline TextureFormat GetFormat() const { return format_; } 

    inline int GetWidth() const { return width_; } 

    inline int GetHeight() const { return height_; } 

    inline TextureFilter GetFilter() const { return filter_; } 

    inline TextureWrapMode GetWrapMode() const { return wrapModeX_; } 

    inline TextureWrapMode GetWrapModeX() const { return wrapModeX_; } 

    inline TextureWrapMode GetWrapModeY() const { return wrapModeY_; } 

    virtual void Resize(TextureFormat format, int width, int height); 

    virtual void SetFilter(TextureFilter filter); 

    virtual void SetWrapMode(TextureWrapMode mode); 

    virtual void SetWrapModeX(TextureWrapMode mode); 

    virtual void SetWrapModeY(TextureWrapMode mode); 

protected: 
    TextureType type_; 
    TextureFormat format_; 
    int width_; 
    int height_; 
    TextureFilter filter_ = TextureFilter::BILINEAR; 
    TextureWrapMode wrapModeX_ = TextureWrapMode::REPEAT; 
    TextureWrapMode wrapModeY_ = TextureWrapMode::REPEAT; 
    bool dirtyParams_ = true; 
    bool dirtyData_ = true; 
};

}