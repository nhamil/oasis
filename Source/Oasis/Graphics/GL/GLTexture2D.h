#pragma once 

#include "Oasis/Graphics/Texture2D.h" 
#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 
#include "Oasis/Graphics/GL/GLUtil.h" 

namespace Oasis 
{

class OASIS_API GLTexture2D : public Texture2D 
{
public: 
    GLTexture2D(GLGraphicsDevice* graphics, TextureFormat format, int width, int height); 
    ~GLTexture2D(); 

    void Update() override; 

    inline GLuint GetId() const { return id_; } 

private: 
    void Create(); 
    void Destroy(); 

    GLGraphicsDevice* graphics_ = nullptr; 
    GLuint id_ = 0; 
};

}