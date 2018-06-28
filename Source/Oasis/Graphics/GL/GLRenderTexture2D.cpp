#include "Oasis/Graphics/GL/GLRenderTexture2D.h" 

#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 
#include "Oasis/Graphics/GL/GLTexture2D.h" 

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

    GLuint format = GetGLTextureFormat(format_); 
    GLuint dataType = GetGLTextureDataType(format_); 
    GLuint inputFormat = GetGLTextureInputFormat(format_); 

    GLCALL(glGenTextures(1, &id_)); 

    // GLCALL(glBindTexture(GL_TEXTURE_2D, id_)); 
    graphics_->BindTexture2D(0, id_); 
    
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, inputFormat, dataType, nullptr)); 

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    // if multisampled, create a renderbuffer 

    if (multisample_ > 1) 
    {
        GLCALL(glGenRenderbuffers(1, &renderbufferId_)); 

        GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, renderbufferId_)); 

        GLCALL(glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisample_, format, width_, height_)); 
    }
}

void GLRenderTexture2D::ResolveTextureIfNeeded() 
{
    if (dirtyResolve_) 
    {
        graphics_->ResolveRenderTexture2D(this); 
        dirtyResolve_ = false; 
        dirtyBackup_ = true; 
    }
}

void GLRenderTexture2D::Update() 
{
    if (!id_) Create(); 

    if (dirtyData_) 
    {
        // size has changed 
        GLuint format = GetGLTextureFormat(format_); 
        GLuint dataType = GetGLTextureDataType(format_); 
        GLuint inputFormat = GetGLTextureInputFormat(format_); 

        graphics_->BindTexture2D(0, id_); 

        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, inputFormat, dataType, nullptr)); 

        if (renderbufferId_) 
        {
            GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, renderbufferId_)); 
            GLCALL(glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisample_, format, width_, height_)); 
        }

        if (backupId_) 
        {
            graphics_->BindTexture2D(0, backupId_); 
            GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, inputFormat, dataType, nullptr)); 
            dirtyBackup_ = true; 
        }
    }

    if (dirtyParams_) 
    {
        if (!rttParameters_) 
        {
            SetTextureParameters(); 
        }

        if (backupId_) 
        {
            SetBackupParameters(true); 
        }
    }

    dirtyData_ = false; 
    dirtyParams_ = false; 
}

void GLRenderTexture2D::UpdateBackupTexture() 
{
    if (!backupId_) 
    {
        GLCALL(glGenTextures(1, &backupId_)); 
        graphics_->BindTexture2D(0, backupId_); 
        SetBackupParameters(true); 

        GLuint format = GetGLTextureFormat(format_); 
        GLuint dataType = GetGLTextureDataType(format_); 
        GLuint inputFormat = GetGLTextureInputFormat(format_); 

        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, inputFormat, dataType, nullptr)); 
        dirtyBackup_ = true; 
    }

    if (dirtyBackup_) 
    {
        graphics_->CopyToBackupTexture(id_, backupId_, width_, height_, !IsDepthTextureFormat(format_)); 
    }
}

void GLRenderTexture2D::Destroy() 
{
    if (id_) 
    {
        graphics_->OnDestroy(this); 

        GLCALL(glDeleteTextures(1, &id_)); 
        id_ = 0; 

        if (renderbufferId_) 
        {
            GLCALL(glDeleteRenderbuffers(1, &renderbufferId_)); 
            renderbufferId_ = 0; 
        }

        if (backupId_) 
        {
            GLCALL(glDeleteTextures(1, &backupId_)); 
            backupId_ = 0; 
        }
    }
}

void GLRenderTexture2D::SetRTTParameters() 
{
    if (!rttParameters_) 
    {
        // TODO set RTT parameters 
        rttParameters_ = true; 

        graphics_->BindTexture2D(0, id_); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));	
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    }
}

void GLRenderTexture2D::SetTextureParameters() 
{
    if (dirtyParams_) 
    {
        SetBackupParameters(false); 
    }

    if (!rttParameters_) 
    {
        graphics_->BindTexture2D(0, id_); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0)); 
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0)); //mipmaps_ - 1)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP_MODE[(int) wrapModeX_]));	
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP_MODE[(int) wrapModeY_])); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_MIN_FILTERS[(int) filter_]));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_MAG_FILTERS[(int) filter_]));
    }

    dirtyParams_ = false; 
}

void GLRenderTexture2D::SetBackupParameters(bool force) 
{
    if (backupId_ && (dirtyParams_ || force)) 
    {
        graphics_->BindTexture2D(0, backupId_); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0)); 
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0)); //mipmaps_ - 1)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP_MODE[(int) wrapModeX_]));	
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP_MODE[(int) wrapModeY_])); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_MIN_FILTERS[(int) filter_]));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_MAG_FILTERS[(int) filter_]));
    }
}

void GLRenderTexture2D::SetRenderedTo() 
{
    if (IsMultisampled()) 
    {
        dirtyResolve_ = true; 
    }

    dirtyBackup_ = true; 
}

}