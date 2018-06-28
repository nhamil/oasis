#include "Oasis/Graphics/GL/GLTexture2D.h" 

namespace Oasis 
{

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

void GLTexture2D::Update() 
{
    if (!id_) Create(); 

    if (dirtyParams_) 
    {
        graphics_->BindTexture2D(0, id_); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0)); 
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmaps_ - 1)); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP_MODE[(int) wrapModeX_]));	
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP_MODE[(int) wrapModeY_])); 

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_MIN_FILTERS[(int) filter_]));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_MAG_FILTERS[(int) filter_]));
    }

    if (dirtyData_) 
    {
        GLCALL(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GetGLTextureFormat(format_), 
            width_, 
            height_, 
            0, 
            GetGLTextureInputFormat(format_), 
            GetGLTextureDataType(format_), 
            &data_[0] 
        ));
    }

    // TODO do parameters affect mipmaps? 
    if (dirtyData_ || dirtyParams_) 
    {
        GLCALL(glGenerateMipmap(GL_TEXTURE_2D)); 
    }

    dirtyData_ = false; 
    dirtyParams_ = false; 
}

void GLTexture2D::Create() 
{
    if (!id_) 
    {
        GLCALL(glGenTextures(1, &id_)); 
    }
}

void GLTexture2D::Destroy() 
{
    if (id_) 
    {
        graphics_->OnDestroy(this); 
        
        GLCALL(glDeleteTextures(1, &id_)); 
        id_ = 0; 
    }
}

}