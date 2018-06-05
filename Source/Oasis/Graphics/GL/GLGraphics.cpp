#include "Oasis/Graphics/Graphics.h" 

#include "Oasis/Core/Engine.h" 
#include "Oasis/Core/Display.h" 
#include "Oasis/Graphics/IndexBuffer.h" 
#include "Oasis/Graphics/Shader.h" 
#include "Oasis/Graphics/VertexArray.h" 
#include "Oasis/Graphics/VertexBuffer.h" 

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

Graphics::Graphics() {}
Graphics::~Graphics() {} 

void Graphics::PreRender() 
{
    Display* d = Engine::GetSubsystem<Display>(); 

    SetVertexArray(nullptr); 
    SetViewport(0, 0, d->GetWidth(), d->GetHeight()); 
    SetClearColor(0.7, 0.8, 0.9); 
    Clear(); 
}

void Graphics::PostRender() 
{

}

void Graphics::SetClearColor(float r, float g, float b) 
{
    clearColor_ = { r, g, b }; 
}

void Graphics::Clear(bool color, bool depth) 
{
    glClearColor(clearColor_.x, clearColor_.y, clearColor_.z, 1); 
    unsigned bits = 0; 

    if (!color && !depth) return; 

    if (color) bits |= GL_COLOR_BUFFER_BIT; 
    if (depth) bits |= GL_DEPTH_BUFFER_BIT; 

    glClear(bits); 
}

void Graphics::SetViewport(int x, int y, int w, int h) 
{
    viewport_ = Vector4(x, y, w, h); 
    glViewport(x, y, w, h); 
}

void Graphics::SetVertexArray(VertexArray* vertexArray) 
{
    curVertexArray_ = vertexArray; 
} 

void Graphics::Draw(Primitive prim, int start, int primCount) 
{
    // TODO 
}  

void Graphics::DrawIndexed(Primitive prim, int start, int primCount) 
{
    // TODO 
}  

Shader* Graphics::CreateShader(const string& vs, const string& fs) 
{
    return new Shader(vs, fs); 
}

void Graphics::DestroyShader(Shader* shader) 
{
    if (shader) 
    {
        // TODO destroy GL resource 
        delete shader; 
    }
}

VertexArray* Graphics::CreateVertexArray() 
{
    return new VertexArray(); 
}  

void Graphics::DestroyVertexArray(VertexArray* vertexArray) 
{
    // TODO destroy resources 
    // not needed for now, since using GL2
    delete vertexArray; 
}  

IndexBuffer* Graphics::CreateIndexBuffer(int numElements, BufferUsage usage)
{
    return new IndexBuffer(numElements, usage); 
}  

void Graphics::DestroyIndexBuffer(IndexBuffer* indexBuffer) 
{
    if (indexBuffer) 
    {
        indexBuffer->DestroyResource(); 
        delete indexBuffer; 
    }
}  

VertexBuffer* Graphics::CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage) 
{
    return new VertexBuffer(numElements, format, usage); 
}  

void Graphics::DestroyVertexBuffer(VertexBuffer* vertexBuffer) 
{
    if (vertexBuffer) 
    {
        vertexBuffer->DestroyResource(); 
        delete vertexBuffer; 
    }
}  

void Graphics::BindVertexArray()
{
    if (!curVertexArray_) return;

    IndexBuffer* ib = curVertexArray_->GetIndexBuffer();

    if (ib)
    {
        ib->Update();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int attribs[(int) Attribute::count];

    for (int i = 0; i < (int) Attribute::count; i++) attribs[i] = -1;

    for (int i = 0; i < curVertexArray_->GetVertexBufferCount(); i++)
    {
        VertexBuffer* vb = curVertexArray_->GetVertexBuffer(i);
        vb->Update();
        const VertexFormat& format = vb->GetVertexFormat();

        for (int j = 0; j < format.GetAttributeCount(); j++)
        {
            Attribute attrib = format.GetAttribute(j);

            if (attribs[(int) attrib] == -1)
            {
                attribs[(int) attrib] = i;
            }
        }
    }

    for (int i = 0; i < (int) Attribute::count; i++)
    {
        if (attribs[i] == -1)
        {
            glDisableVertexAttribArray(OGLShader::GetAttributeIndex((Attribute) i));
            //cout << "Disabling " << OGLShader::GetAttributeName((Attribute) i) << endl;
            continue;
        }

        OGLVertexBuffer* vb = (OGLVertexBuffer*) vertexArray_->GetVertexBuffer(attribs[i]);
        //cout << "Binding " << vb->GetId() << endl;
        glBindBuffer(GL_ARRAY_BUFFER, vb->GetId());

        //cout << "Enabling " << OGLShader::GetAttributeName((Attribute) i) << endl;
        glEnableVertexAttribArray(OGLShader::GetAttributeIndex((Attribute) i));

        /*cout << "attrib pointer "
            << i << " "
            << GetAttributeSize((Attribute) i) << " "
            << vb->GetFormat().GetSize() * sizeof (float) << " "
            << (vb->GetFormat().GetOffset((Attribute) i) * sizeof (float)) << endl;*/
        glVertexAttribPointer(i, GetAttributeSize((Attribute) i), GL_FLOAT, GL_FALSE, vb->GetFormat().GetSize() * sizeof (float), (void*) (vb->GetFormat().GetOffset((Attribute) i) * sizeof (float)));
    }
}

}