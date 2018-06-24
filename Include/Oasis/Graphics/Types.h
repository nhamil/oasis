#pragma once 

#include "Oasis/Common.h" 
#include "Oasis/Graphics/GraphicsObject.h" 

namespace Oasis 
{

class IndexBuffer;
class RenderTexture2D; 
class Shader; 
class Texture; 
class Texture2D; 
class VertexBuffer;

enum class Primitive
{
    LINE_LIST,
    LINE_STRIP,
    TRIANGLE_LIST,
    TRIANGLE_STRIP,

    count
};

enum class Attribute
{
    POSITION,
    NORMAL,
    TANGENT,
    TEXTURE,
    COLOR,

    count
};

inline int GetAttributeSize(Attribute attrib)
{
    switch (attrib)
    {
    case Attribute::TANGENT: return 3;
    case Attribute::POSITION: return 3;
    case Attribute::NORMAL: return 3;
    case Attribute::COLOR: return 4;
    case Attribute::TEXTURE: return 2;
    default: return 0;
    }
}

enum class TextureFormat 
{
    RGBA8, 
    RGBA16F, 
    RGBA32F, 
    DEPTH16, 
    DEPTH24, 
    DEPTH24STENCIL8, 
    DEPTH32, 
    
    count 
};

inline bool IsDepthTextureFormat(TextureFormat format) 
{
    switch (format) 
    {
    case TextureFormat::DEPTH16: 
    case TextureFormat::DEPTH24: 
    case TextureFormat::DEPTH24STENCIL8: 
    case TextureFormat::DEPTH32: 
        return true; 
    default: 
        return false; 
    }
}

inline bool IsStencilTextureFormat(TextureFormat format) 
{
    return format == TextureFormat::DEPTH24STENCIL8; 
}

inline bool IsColorTextureFormat(TextureFormat format) 
{
    return !IsDepthTextureFormat(format); 
}

enum class TextureType 
{
    UNKNOWN, 
    TEXTURE_2D, 
    TEXTURE_3D, 
    TEXTURE_CUBE, 
    TEXTURE_2D_ARRAY, 
    RENDER_TEXTURE_2D, 

    count 
};

enum class TextureFilter 
{
    NEAREST, 
    LINEAR, 
    BILINEAR, 
    TRILINEAR, 

    count 
};

enum class TextureWrapMode  
{
    CLAMP, 
    REPEAT, 

    count 
};

inline int GetTextureFormatByteCount(TextureFormat format) 
{
    switch (format) 
    {
    case TextureFormat::RGBA8: return 4; 
    default: return 0; 
    }
}

enum class BufferUsage
{
    STATIC,
    DYNAMIC,
    STREAM,

    count
};

}