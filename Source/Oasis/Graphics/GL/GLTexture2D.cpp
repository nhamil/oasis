#include "Oasis/Graphics/GL/GLTexture2D.h" 

namespace Oasis 
{

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

GLTexture2D::GLTexture2D(GLGraphicsDevice* graphics, TextureFormat format, int width, int height) 
    : Texture2D(format, width, height) 
    , graphics_(graphics) 
{
    Create(); 
}

GLTexture2D::~GLTexture2D() 
{
    Destroy(); 
}

void GLTexture2D::UploadToGPU() 
{
    if (!id_) Create(); 

    if (dirtyParams_) 
    {
        GLCALL(glActiveTexture(GL_TEXTURE0)); 
        GLCALL(glBindTexture(GL_TEXTURE_2D, id_)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0)); 
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmaps_)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP_MODE[(int) wrapModeX_]));	
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP_MODE[(int) wrapModeY_])); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_MIN_FILTERS[(int) filter_]));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_MAG_FILTERS[(int) filter_]));
    }

    if (dirty_) 
    {
        GLCALL(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA8, 
            width_, 
            height_, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            &data_[0] 
        ));
    }

    GLCALL(glGenerateMipmap(GL_TEXTURE_2D)); 
}

void GLTexture2D::Create() 
{
    if (!id_) 
    {
        GLCALL(glGenTextures(1, &id_)); 

        GLCALL(glActiveTexture(GL_TEXTURE0)); 
        GLCALL(glBindTexture(GL_TEXTURE_2D, id_)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0)); 
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GLCALL(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA8, 
            width_, 
            height_, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            nullptr
        ));

        GLCALL(glEnable(GL_TEXTURE_2D)); 
    }
}

void GLTexture2D::Destroy() 
{
    if (id_) 
    {
        for (int i = 0; i < graphics_->GetMaxTextureUnitCount(); i++) 
        {
            if (graphics_->GetTextureUnit(i) == this) graphics_->SetTextureUnit(i, nullptr); 
        }

        GLCALL(glDeleteTextures(1, &id_)); 
        id_ = 0; 
    }
}

}