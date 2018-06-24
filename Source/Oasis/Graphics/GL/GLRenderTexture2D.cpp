#include "Oasis/Graphics/GL/GLRenderTexture2D.h" 

#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 

namespace Oasis 
{

GLRenderTexture2D::GLRenderTexture2D(GLGraphicsDevice* graphics, TextureFormat format, int width, int height, int samples) 
    : RenderTexture2D(format, width, height, samples) 
    , graphics_(graphics) 
{
    Create(); 
}

GLRenderTexture2D::~GLRenderTexture2D() 
{
    Destroy(); 
}

void GLRenderTexture2D::Create() 
{
    if (id_) return; 

    GLCALL(glGenTextures(1, &id_)); 

    // GLCALL(glBindTexture(GL_TEXTURE_2D, id_)); 
    graphics_->BindTexture2D(0, id_); 
    
    if (IsDepthTextureFormat(format_)) 
    {
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width_, height_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr)); 
    } 
    else 
    {
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr)); 
    }

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
}

void GLRenderTexture2D::UploadToGPU() 
{
    if (!id_) Create(); 
}

void GLRenderTexture2D::Destroy() 
{
    if (id_) 
    {
        graphics_->OnDestroy(this); 

        GLCALL(glDeleteTextures(1, &id_)); 
        id_ = 0; 
    }
}

}