#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Graphics/Types.h" 

namespace Oasis 
{

class Texture2D; 

class OASIS_API Texture 
{
public: 
    Texture(TextureType type, TextureFormat format, int width, int height) : type_(type), format_(format), width_(width), height_(height) {} 
    virtual ~Texture() {} 

    void FlushToGPU(); 

    inline TextureType GetType() const { return type_; } 

    Texture2D* GetTexture2D(); 

    inline TextureFormat GetFormat() const { return format_; } 

    inline int GetWidth() const { return width_; } 

    inline int GetHeight() const { return height_; } 

    inline TextureFilter GetFilter() const { return filter_; } 

    inline TextureWrapMode GetWrapMode() const { return wrapModeX_; } 

    inline TextureWrapMode GetWrapModeX() const { return wrapModeX_; } 

    inline TextureWrapMode GetWrapModeY() const { return wrapModeY_; } 

    inline void SetFilter(TextureFilter filter) { filter_ = filter; dirtyParams_ = true; } 

    inline void SetWrapModeX(TextureWrapMode mode) { wrapModeX_ = mode; dirtyParams_ = true; } 

    inline void SetWrapModeY(TextureWrapMode mode) { wrapModeY_ = mode; dirtyParams_ = true; } 

    inline void SetWrapMode(TextureWrapMode mode) { SetWrapModeX(mode); SetWrapModeY(mode); } 

protected: 
    virtual void UploadToGPU() = 0; 

    TextureType type_; 
    TextureFormat format_; 
    TextureFilter filter_ = TextureFilter::BILINEAR; 
    TextureWrapMode wrapModeX_ = TextureWrapMode::REPEAT; 
    TextureWrapMode wrapModeY_ = TextureWrapMode::REPEAT; 
    int width_; 
    int height_; 
    bool dirty_ = true; 
    bool dirtyParams_ = true; 
};

}