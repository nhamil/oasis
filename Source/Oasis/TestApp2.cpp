#include <Oasis/Oasis.h> 

#include "Oasis/Core/Logger.h"

#include <memory> 

#define BLACK (char)0, (char)0, (char)0, (char)0 
#define WHITE (char)255, (char)255, (char)255, (char)255 

using namespace Oasis; 
using namespace std; 

#define RT_WIDTH (1920) 
#define RT_HEIGHT (1080)

#define TEX_WIDTH (10) 
#define TEX_HEIGHT (10) 

static const string VERTEX_SOURCE = R"(#version 120 
attribute vec3 a_Position; 
attribute vec2 a_Texture; 

varying vec2 v_TexCoord; 

uniform mat4 oa_Model; 
uniform mat4 oa_View; 
uniform mat4 oa_Proj; 

void main() 
{
    v_TexCoord = a_Texture; 
    gl_Position = oa_Proj * oa_View * oa_Model * vec4(a_Position, 1.0); 
}
)"; 

static const string FRAGMENT_SOURCE = R"(#version 120
uniform sampler2D u_Texture; 
uniform vec3 u_Color; 

varying vec2 v_TexCoord; 

void main() 
{
    gl_FragColor = texture2D(u_Texture, v_TexCoord); 
    gl_FragColor.a = 1.0; 
}
)";

class TestApp2 : public Application 
{
public: 
    virtual ~TestApp2() = default; 

    Config GetConfig() const override 
    {
        Config conf; 
        conf.targetFps = -1; 
        return conf; 
    }

    void Init() override; 
    void Update(float dt) override; 
    void Render() override; 
    void Exit() override; 

    Shader* shader; 
    Texture2D* texture; 
    RenderTexture2D* colorBuffer; 
    RenderTexture2D* depthBuffer; 
    float angle; 
    Mesh mesh; 
    VertexBuffer* rectVbo; 
    IndexBuffer* rectIbo; 
};

namespace Oasis { class Material; }

void TestApp2::Init() 
{
    Logger::Info("Init App"); 

    auto g = Engine::GetGraphicsDevice();  

    float s = 1; 

    float verts[] =
    {
        -s,  s, -s,
        -s,  s,  s,
         s,  s,  s,
         s,  s, -s, 

        -s, -s, -s,
        -s, -s,  s,
         s, -s,  s,
         s, -s, -s, 

         s, -s, -s,
         s,  s, -s,
         s,  s,  s,
         s, -s,  s, 

        -s, -s, -s,
        -s,  s, -s,
        -s,  s,  s,
        -s, -s,  s, 

        -s, -s, s,
         s, -s, s,
         s,  s, s,
        -s,  s, s, 
        
        -s, -s, -s,
         s, -s, -s,
         s,  s, -s,
        -s,  s, -s, 
    };

    float texCoords[] = 
    {
        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 

        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 

        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 

        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 

        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 

        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 
    };

    short inds[] =
    {
        0, 1, 2,
        0, 2, 3, 

        4, 5, 6, 
        4, 6, 7, 

        8, 9, 10, 
        8, 10, 11, 

        12, 13, 14, 
        12, 14, 15, 

        16, 17, 18, 
        16, 18, 19, 

        20, 21, 22, 
        20, 22, 23, 
    };

    mesh.SetVertexCount(4 * 6); 
    mesh.SetSubmeshCount(1); 
    mesh.SetPositions((Vector3*) verts); 
    mesh.SetTexCoords((Vector2*) texCoords); 
    mesh.SetIndices(0, 6 * 6, inds); 
    mesh.UploadToGPU(); 

    shader = g->CreateShader(VERTEX_SOURCE, FRAGMENT_SOURCE); 

    texture = g->CreateTexture2D(TextureFormat::RGBA8, TEX_WIDTH, TEX_HEIGHT); 

    colorBuffer = g->CreateRenderTexture2D(TextureFormat::RGBA8, RT_WIDTH, RT_HEIGHT, 8); 
    depthBuffer = g->CreateRenderTexture2D(TextureFormat::DEPTH24, RT_WIDTH, RT_HEIGHT, 8); 

    char texData[TEX_WIDTH * TEX_HEIGHT * 4]; 
    for (int i = 0; i < TEX_WIDTH * TEX_HEIGHT * 4; i++) 
    {
        texData[i] = (char) rand(); 
    }

    texture->SetData(0, 0, TEX_WIDTH, TEX_HEIGHT, texData); 
    texture->SetMipmapCount(10); 
    texture->SetFilter(TextureFilter::TRILINEAR); 
    texture->SetWrapMode(TextureWrapMode::REPEAT); 
    texture->Update(); 

    VertexFormat format; 
    format.AddAttribute(Attribute::POSITION); 
    format.AddAttribute(Attribute::TEXTURE); 

    float rectVerts[] = {
        -1, -1, 0, 0, 0, 
        1, -1, 0, 1, 0, 
        1, 1, 0, 1, 1, 
        -1, 1, 0, 0, 1, 
    }; 

    short rectInds[] = {
        0, 1, 2, 
        0, 2, 3, 
    }; 

    rectVbo = g->CreateVertexBuffer(4, format); 
    rectVbo->SetData(0, 4, rectVerts); 
    rectVbo->Update(); 

    rectIbo = g->CreateIndexBuffer(6); 
    rectIbo->SetData(0, 6, rectInds);
    rectIbo->Update(); 
}

void TestApp2::Update(float dt) 
{
    angle += 1 * dt; 
}

void TestApp2::Render() 
{
    // Logger::Debug("TestApp2::Render Begin"); 

    auto g = Engine::GetGraphicsDevice(); 
    auto w = Engine::GetDisplay(); 

    g->SetClearColor(0.2, 0.2, 0.2); 

    // render to texture 
    g->ClearRenderTargets(); 
    g->SetRenderTarget(0, colorBuffer); 
    g->SetDepthTarget(depthBuffer); 
    g->SetViewport(0, 0, colorBuffer->GetWidth(), colorBuffer->GetHeight()); 
    g->Clear(); 

    shader->SetVector3("u_Color", { 1, 1, 1 }); 
    shader->SetMatrix4("oa_Model", Matrix4::RotationY(1.3 * angle) * Matrix4::RotationX(1.7 * angle) * Matrix4::RotationZ(2.1 * angle)); 
    shader->SetMatrix4("oa_Proj", Matrix4::Perspective(90 * OASIS_TO_RAD, w->GetAspectRatio(), 0.1, 100.0)); 
    shader->SetTextureUnit("u_Texture", 0); 

    g->SetTextureUnit(0, texture); 
    g->SetShader(shader); 
    g->SetIndexBuffer(mesh.GetIndexBuffer(0)); 
    g->SetVertexBuffer(mesh.GetVertexBuffer()); 

    // int x = 0, y = 0, z = 0; 

    for (int x = -5; x <= 5; x++) 
    {
        for (int y = -5; y <= 5; y++) 
        {
            for (int z = -4; z <= 0; z++) 
            {
                shader->SetMatrix4("oa_View", Matrix4::Translation({x * 4.0f + 2, y * 4.0f + 2, z * 4 + -8 + 9 * (float) std::sin(angle * 0.5)})); 
                shader->Update(); 

                g->DrawIndexed(Primitive::TRIANGLE_LIST, 0, 6 * 6); 
            }
        }
    }

    // Logger::Debug("TestApp2::Render Render to Screen"); 

    // render texture to screen 
    g->ClearRenderTargets(); 
    g->SetViewport(0, 0, w->GetWidth(), w->GetHeight()); 

    shader->SetVector3("u_Color", { 1, 1, 1 }); 
    shader->SetMatrix4("oa_View", Matrix4::IDENTITY); 
    shader->SetMatrix4("oa_Model", Matrix4::IDENTITY); 
    shader->SetMatrix4("oa_Proj", Matrix4::IDENTITY); 
    shader->SetTextureUnit("u_Texture", 0); 
    shader->Update(); 

    g->SetTextureUnit(0, colorBuffer); 
    g->SetIndexBuffer(rectIbo); 
    g->SetVertexBuffer(rectVbo); 
    g->DrawIndexed(Primitive::TRIANGLE_LIST, 0, 6); 

    // Logger::Debug("TestApp2::Render Finish"); 
}

void TestApp2::Exit() 
{
    Logger::Info("Exit App"); 

    shader->Release(); 
    texture->Release(); 
}

int main(int argc, char** argv) 
{
    (void) argc; 
    (void) argv; 

    Engine::Start(new TestApp2); 

    return 0; 
}