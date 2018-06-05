#pragma once

#include "Oasis/Common.h"

namespace Oasis
{

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

enum class TextureFilter
{
    NEAREST,
    BILINEAR,
    TRILINEAR,

    count
};
enum class Axis
{
    AXIS_X,
    AXIS_Y,
    AXIS_Z,

    AXIS_COUNT
};

enum class WrapMode
{
    CLAMP,
    REPEAT,

    count
} ;

class OASIS_API Texture
{
public:
    virtual ~Texture() = default; 

    virtual void Release() = 0;

    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    virtual TextureFilter GetFilter() const = 0;
    virtual WrapMode GetWrapMode(Axis axis) const = 0;
    virtual int GetMipmapLevels() const = 0;

    virtual void SetSize(int width, int height) = 0;

    virtual void SetFilter(TextureFilter filter) = 0;
    virtual void SetWrapMode(WrapMode mode) = 0;
    virtual void SetWrapMode(Axis axis, WrapMode mode) = 0;
    virtual void SetMipmapLevels(int levels) = 0;
};

}
