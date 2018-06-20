#include "Oasis/Graphics/GL/GLGraphicsDevice.h" 

#include "Oasis/Core/Engine.h" 
#include "Oasis/Core/Display.h" 
#include "Oasis/Graphics/GL/GLIndexBuffer.h" 
#include "Oasis/Graphics/GL/GLShader.h"
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

GLGraphicsDevice::GLGraphicsDevice() {}
GLGraphicsDevice::~GLGraphicsDevice() {} 

void GLGraphicsDevice::PreRender() 
{
    Display* d = Engine::GetDisplay(); 

    SetShader(nullptr); 
    //SetVertexBuffer(nullptr); 
    //SetIndexBuffer(nullptr); 
    SetViewport(0, 0, d->GetWidth(), d->GetHeight()); 
    SetClearColor(0.7, 0.8, 0.9); 
    Clear(); 
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

void GLGraphicsDevice::SetViewport(int x, int y, int w, int h) 
{
    viewport_ = Vector4(x, y, w, h); 
    GLCALL(glViewport(x, y, w, h)); 
}

void GLGraphicsDevice::Draw(Primitive prim, int start, int triCount) 
{
    // TODO 
}  

void GLGraphicsDevice::DrawIndexed(Primitive prim, int start, int triCount) 
{
    if (!indexBuffer_) return; 
    if (!shaderProgram_) return; 

    indexBuffer_->Flush(); 
    shaderProgram_->Flush(); 

    for (int i = 0; i < GetVertexBufferCount(); i++) 
    {
        if (vertexBuffers_[i]) vertexBuffers_[i]->Flush(); 
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
            i, 
            GetAttributeSize((Attribute) i), 
            GL_FLOAT, 
            GL_FALSE, 
            vb->GetVertexFormat().GetSize() * sizeof (float), 
            (void*) (vb->GetVertexFormat().GetOffset((Attribute) i) * sizeof (float)))); 
    }

    GLCALL(glDrawElements(/*PRIMITIVE_TYPES[(int) prim]*/ GL_TRIANGLES, triCount, GL_UNSIGNED_SHORT, (void*)(start * sizeof (short)))); 
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

}