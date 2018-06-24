#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 

#include "Oasis/Core/Engine.h" 
#include "Oasis/Core/Display.h" 
#include "Oasis/Graphics/GL/GLIndexBuffer.h" 
#include "Oasis/Graphics/GL/GLRenderTexture2D.h" 
#include "Oasis/Graphics/GL/GLShader.h"
#include "Oasis/Graphics/GL/GLTexture2D.h" 
#include "Oasis/Graphics/GL/GLUtil.h"  
#include "Oasis/Graphics/GL/GLVertexBuffer.h" 

#include <GL/glew.h> 

#include <string> 

using namespace std; 

namespace Oasis 
{

static const string GL_VS = R"(#version 120 
attribute vec3 a_Position; 
uniform mat4 oa_Model; 
uniform mat4 oa_View; 
uniform mat4 oa_Proj; 
void main() 
{
    gl_Position = oa_Proj * oa_View * oa_Model * vec4(a_Position, 1.0); 
}
)"; 

static const string GL_FS = R"(#version 120
uniform vec3 u_Color; 
void main() 
{
    gl_FragColor = vec4(u_Color, 1.0); 
}
)";

static const GLuint PRIMITIVE_TYPES[(int) Primitive::count] =
{
    GL_LINES,
    GL_LINE_STRIP,
    GL_TRIANGLES,
    GL_TRIANGLE_STRIP
};

GLGraphicsDevice::GLGraphicsDevice() 
{
    for (int i = 0; i < GetMaxTextureUnitCount(); i++) 
    {
        textureUnits_[i] = nullptr; 
    }
    for (int i = 0; i < GetMaxRenderTargetCount(); i++) 
    {
        renderTargets_[i] = nullptr; 
    }
}

GLGraphicsDevice::~GLGraphicsDevice() {} 

void GLGraphicsDevice::PreRender() 
{
    Display* d = Engine::GetDisplay(); 

    GLCALL(glEnable(GL_BLEND)); 
    GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA)); 
    GLCALL(glEnable(GL_DEPTH_TEST)); 

    SetShader(nullptr); 
    SetVertexBuffer(nullptr); 
    SetIndexBuffer(nullptr); 
    SetViewport(0, 0, d->GetWidth(), d->GetHeight()); 
    SetClearColor(0.7, 0.8, 0.9); 
    Clear(); 

    if (!fbo_) 
    {
        GLCALL(glGenFramebuffers(1, &fbo_)); 
    }
}

void GLGraphicsDevice::PostRender() 
{

}

void GLGraphicsDevice::SetClearColor(float r, float g, float b) 
{
    clearColor_ = { r, g, b }; 
}

void GLGraphicsDevice::Clear(bool color, bool depth) 
{
    SetupFramebuffer(); 

    GLCALL(glClearColor(clearColor_.x, clearColor_.y, clearColor_.z, 1)); 
    unsigned bits = 0; 

    if (!color && !depth) return; 

    if (color) bits |= GL_COLOR_BUFFER_BIT; 
    if (depth) bits |= GL_DEPTH_BUFFER_BIT; 

    GLCALL(glClear(bits)); 
}

void GLGraphicsDevice::SetShader(Shader* shader) 
{
    shaderProgram_ = dynamic_cast<GLShader*>(shader); 
}

void GLGraphicsDevice::SetIndexBuffer(IndexBuffer* ib) 
{
    indexBuffer_ = dynamic_cast<GLIndexBuffer*>(ib); 
}

void GLGraphicsDevice::SetVertexBuffers(int count, VertexBuffer** vbs) 
{
    vertexBuffers_.clear(); 

    for (int i = 0; i < count; i++) 
    {
        GLVertexBuffer* vb = dynamic_cast<GLVertexBuffer*>(vbs[i]); 
        if (vb) vertexBuffers_.push_back(vb); 
    }
}

void GLGraphicsDevice::SetTextureUnit(int unit, Texture* texture) 
{
    Texture* set = nullptr; 

    if (texture) 
    {
        // make sure texture is a GLTexture 
        switch (texture->GetType()) 
        {
        case TextureType::TEXTURE_2D: 
            set = dynamic_cast<GLTexture2D*>(texture); 
            break; 
        case TextureType::RENDER_TEXTURE_2D: 
            set = dynamic_cast<GLRenderTexture2D*>(texture); 
            break; 
        case TextureType::TEXTURE_3D: 
            // TODO 
            break; 
        case TextureType::TEXTURE_CUBE: 
            // TODO 
            break; 
        case TextureType::TEXTURE_2D_ARRAY: 
            // TODO 
            break; 
        default: break; 
        }

        textureUnits_[unit] = set; 
    }
    else 
    {
        textureUnits_[unit] = nullptr; 
    }
}

void GLGraphicsDevice::SetViewport(int x, int y, int w, int h) 
{
    viewport_ = Vector4(x, y, w, h); 
    GLCALL(glViewport(x, y, w, h)); 
}

void GLGraphicsDevice::Draw(Primitive prim, int start, int triCount) 
{
    // TODO 
    (void) prim; 
    (void) start; 
    (void) triCount; 
}  

void GLGraphicsDevice::DrawIndexed(Primitive prim, int start, int triCount) 
{
    (void) prim; 

    if (!indexBuffer_) return; 

    if (PrepareToDraw()) 
    {
        GLCALL(glDrawElements(/*PRIMITIVE_TYPES[(int) prim]*/ GL_TRIANGLES, triCount, GL_UNSIGNED_SHORT, (void*)(start * sizeof (short)))); 
    }    
}  

Shader* GLGraphicsDevice::CreateShader(const string& vs, const string& fs) 
{
    return new GLShader(this, vs, fs); 
}

IndexBuffer* GLGraphicsDevice::CreateIndexBuffer(int numElements, BufferUsage usage)
{
    return new GLIndexBuffer(this, numElements, usage); 
}  

VertexBuffer* GLGraphicsDevice::CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage) 
{
    return new GLVertexBuffer(this, numElements, format, usage); 
}  

Texture2D* GLGraphicsDevice::CreateTexture2D(TextureFormat format, int width, int height) 
{
    return new GLTexture2D(this, format, width, height); 
}

RenderTexture2D* GLGraphicsDevice::CreateRenderTexture2D(TextureFormat format, int width, int height, int samples) 
{
    return new GLRenderTexture2D(this, format, width, height, samples); 
}

int GLGraphicsDevice::GetMaxRenderTargetCount() 
{
    return 4; 
}

void GLGraphicsDevice::ClearRenderTargets(bool color, bool depth) 
{
    if (color) 
    {
        for (int i = 0; i < GetMaxRenderTargetCount(); i++) 
        {
            renderTargets_[i] = nullptr; 
        }
    }
    
    if (depth) 
    {
        depthTarget_ = nullptr; 
    }
}

void GLGraphicsDevice::SetRenderTarget(int index, RenderTexture2D* texture) 
{
    renderTargets_[index] = texture ? dynamic_cast<GLRenderTexture2D*>(texture) : nullptr; 
}

void GLGraphicsDevice::SetDepthTarget(RenderTexture2D* texture) 
{
    depthTarget_ = texture ? dynamic_cast<GLRenderTexture2D*>(texture) : nullptr; 
}

bool GLGraphicsDevice::PrepareToDraw() 
{
    if (!shaderProgram_) return false; 

    shaderProgram_->FlushToGPU(); 

    if (indexBuffer_) indexBuffer_->FlushToGPU(); 
    
    for (int i = 0; i < GetVertexBufferCount(); i++) 
    {
        if (vertexBuffers_[i]) vertexBuffers_[i]->FlushToGPU(); 
    }

    // TODO 
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_->GetId())); 
    GLCALL(glUseProgram(shaderProgram_->GetId())); 

    int attribs[(int) Attribute::count]; 

    for (int i = 0; i < (int) Attribute::count; i++) attribs[i] = -1; 

    for (int i = 0; i < GetVertexBufferCount(); i++) 
    {
        if (!vertexBuffers_[i]) continue; 

        GLVertexBuffer* vb = vertexBuffers_[i]; 
        const VertexFormat& format = vb->GetVertexFormat(); 

        for (int j = 0; j < format.GetAttributeCount(); j++) 
        {
            Attribute attrib = format.GetAttribute(j); 

            if (attribs[(int) attrib] == -1) attribs[(int) attrib] = i; 
        }
    }

    for (int i = 0; i < (int) Attribute::count; i++) 
    {
        if (attribs[i] == -1) 
        {
            GLCALL(glDisableVertexAttribArray(GLShader::GetAttributeIndex((Attribute) i))); 
            continue; 
        }

        GLVertexBuffer* vb = vertexBuffers_[attribs[i]]; 
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vb->GetId())); 
        GLCALL(glEnableVertexAttribArray(GLShader::GetAttributeIndex((Attribute) i))); 
        GLCALL(glVertexAttribPointer(
            GLShader::GetAttributeIndex((Attribute) i),  
            GetAttributeSize((Attribute) i), 
            GL_FLOAT, 
            GL_FALSE, 
            vb->GetVertexFormat().GetSize() * sizeof (float), 
            (void*) (vb->GetVertexFormat().GetOffset((Attribute) i) * sizeof (float)))); 
        /*cout << "Mesh: Attribute " 
            << " " << vb->GetId()
            << " " << GLShader::GetAttributeIndex((Attribute) i)
            << " " << GetAttributeSize((Attribute) i) 
            << " " << vb->GetVertexFormat().GetSize() * sizeof (float) 
            << " " << (vb->GetVertexFormat().GetOffset((Attribute) i) * sizeof (float)) 
            << " " << endl; */
    }

    for (int i = 0; i < GetMaxTextureUnitCount(); i++) 
    {
        GLCALL(glActiveTexture(GL_TEXTURE0 + i)); 

        Texture* tex = textureUnits_[i]; 

        if (tex) 
        {
            tex->FlushToGPU(); 

            switch (tex->GetType()) 
            {
            case TextureType::TEXTURE_2D:  
                GLCALL(glBindTexture(GL_TEXTURE_2D, ((GLTexture2D*) tex)->GetId())); 
                break; 
            case TextureType::RENDER_TEXTURE_2D:  
                GLCALL(glBindTexture(GL_TEXTURE_2D, ((GLRenderTexture2D*) tex)->GetId())); 
                break; 
            default: 
                GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); 
                break; 
            }
        }
        else 
        {
            GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); 
        }
    }

    SetupFramebuffer(); 

    return true; 
}

void GLGraphicsDevice::SetupFramebuffer() 
{
    if (HasCustomRenderTarget()) 
    {
        // bind 
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, fbo_)); 

        vector<GLuint> drawBuffers; 

        for (int i = 0; i < GetMaxRenderTargetCount(); i++) 
        {
            if (renderTargets_[i]) 
            {
                // TODO change if RenderTextureCube is added 
                GLRenderTexture2D* tex = (GLRenderTexture2D*) renderTargets_[i]; 

                tex->FlushToGPU(); 

                // Logger::Debug(tex->GetId()); 
                GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex->GetId(), 0)); 
                drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i); 
            }

            if (depthTarget_) 
            {
                GLRenderTexture2D* tex = (GLRenderTexture2D*) depthTarget_; 

                tex->FlushToGPU(); 

                GLCALL(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex->GetId(), 0)); 
            }

            // Logger::Debug("DrawBuffers: ", drawBuffers.size()); 
            GLCALL(glDrawBuffers(drawBuffers.size(), &drawBuffers[0])); 

            int status; 

            GLCALL(status = glCheckFramebufferStatus(GL_FRAMEBUFFER)); 

            if (status != GL_FRAMEBUFFER_COMPLETE) 
            {
                Logger::Warning("Framebuffer is not complete: ", status); 
            }
        }
    }
    else 
    {
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0)); 
    }
}

bool GLGraphicsDevice::HasCustomRenderTarget() 
{
    if (depthTarget_) return true; 

    for (int i = 0; i < GetMaxRenderTargetCount(); i++) 
    {
        if (renderTargets_[i]) return true; 
    }

    return false; 
}

}