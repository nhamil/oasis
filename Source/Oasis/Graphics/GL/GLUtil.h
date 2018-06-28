#pragma once 

#include "Oasis/Common.h" 

#include <GL/glew.h> 

namespace Oasis 
{

class GLGraphicsDevice; 
class GLIndexBuffer; 
class GLRenderTexture2D; 
class GLShader; 
class GLTexture2D; 
class GLVertexBuffer; 

const GLenum TEXTURE_MIN_FILTERS[] = 
{
    GL_NEAREST_MIPMAP_NEAREST, 
    GL_NEAREST_MIPMAP_LINEAR, 
    GL_LINEAR_MIPMAP_NEAREST, 
    GL_LINEAR_MIPMAP_LINEAR, 
};

const GLenum TEXTURE_MAG_FILTERS[] = 
{
    GL_NEAREST, 
    GL_NEAREST, 
    GL_LINEAR, 
    GL_LINEAR, 
};

const GLenum TEXTURE_WRAP_MODE[] = 
{
    GL_CLAMP_TO_EDGE, 
    GL_REPEAT, 
};

inline GLuint GetGLTextureFormat(TextureFormat format) 
{
    switch (format) 
    {
    case TextureFormat::RGBA8: return GL_RGBA8; 
    case TextureFormat::RGBA16F: return GL_RGBA16F; 
    case TextureFormat::RGBA32F: return GL_RGBA32F; 
    case TextureFormat::DEPTH16: return GL_DEPTH_COMPONENT16; 
    case TextureFormat::DEPTH24: return GL_DEPTH_COMPONENT24; 
    case TextureFormat::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8; 
    case TextureFormat::DEPTH32: return GL_DEPTH_COMPONENT32; 
    default: 
        Logger::Warning("Unknown OpenGL Texture Format: ", (int) format); 
        return 0; 
    }
}

inline GLuint GetGLTextureInputFormat(TextureFormat format) 
{
    switch (format) 
    {
    case TextureFormat::RGBA8: return GL_RGBA; 
    case TextureFormat::RGBA16F: return GL_RGBA; 
    case TextureFormat::RGBA32F: return GL_RGBA; 
    case TextureFormat::DEPTH16: return GL_DEPTH_COMPONENT; 
    case TextureFormat::DEPTH24: return GL_DEPTH_COMPONENT; 
    case TextureFormat::DEPTH24STENCIL8: return GL_DEPTH_COMPONENT; 
    case TextureFormat::DEPTH32: return GL_DEPTH_COMPONENT; 
    default: 
        Logger::Warning("Unknown OpenGL Texture Format: ", (int) format); 
        return 0; 
    }
}

inline GLuint GetGLTextureDataType(TextureFormat format) 
{
    switch (format) 
    {
    case TextureFormat::RGBA8: return GL_UNSIGNED_BYTE; 
    case TextureFormat::RGBA16F: return GL_UNSIGNED_BYTE; 
    case TextureFormat::RGBA32F: return GL_UNSIGNED_BYTE; 
    case TextureFormat::DEPTH16: return GL_UNSIGNED_INT; 
    case TextureFormat::DEPTH24: return GL_UNSIGNED_INT; 
    case TextureFormat::DEPTH24STENCIL8: return GL_UNSIGNED_INT; 
    case TextureFormat::DEPTH32: return GL_UNSIGNED_INT; 
    default: 
        Logger::Warning("Unknown OpenGL Texture Format: ", (int) format); 
        return 0; 
    }
}

}

#if 0 

#define GLCALL(x) { \
    Logger::Debug("Calling GL function: ", #x); \
    x; \
    int glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) Logger::Debug("GLError: ", glerror); }

#else 

#define GLCALL(x) { \
    x; \
    int glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) Logger::Debug("GLError: ", glerror, " at ", __FILE__, ":", __LINE__); }

#endif 