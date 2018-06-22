#pragma once 

#include "Oasis/Common.h" 

namespace Oasis 
{

class IndexBuffer;
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

OASIS_API int GetAttributeSize(Attribute attrib);

enum class TextureFormat 
{
    RGBA8, 
    
    count 
};

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