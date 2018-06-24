#pragma once 

#include "Oasis/Graphics/RenderTexture2D.h" 
#include "Oasis/Graphics/GL/GLUtil.h" 

namespace Oasis 
{

class GLGraphicsDevice; 

class OASIS_API GLRenderTexture2D : public RenderTexture2D 
{
public: 
    GLRenderTexture2D(GLGraphicsDevice* graphics, TextureFormat format, int width, int height, int samples); 
    ~GLRenderTexture2D(); 

    GLuint GetId() const { return id_; } 

private: 
    void UploadToGPU() override; 
    void Create(); 
    void Destroy(); 

    GLGraphicsDevice* graphics_; 
    GLuint id_ = 0; 
};

}