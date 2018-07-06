#include "Sample/MeshRenderSystem.h" 

#include "Sample/Components.h" 

using namespace std; 

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

MeshRenderSystem::MeshRenderSystem() 
{
    Include<Transform>(); 
    Include<MeshContainer>(); 

    CreateResources(); 
}

void MeshRenderSystem::CreateResources() 
{
    GraphicsDevice* gd = Engine::GetGraphicsDevice(); 

    shader_ = gd->CreateShader(VERTEX_SOURCE, FRAGMENT_SOURCE); 

    texture_ = gd->CreateTexture2D(TextureFormat::RGBA8, TEX_WIDTH, TEX_HEIGHT); 

    char texData[TEX_WIDTH * TEX_HEIGHT * 4]; 
    for (int i = 0; i < TEX_WIDTH * TEX_HEIGHT * 4; i++) 
    {
        texData[i] = (char) rand(); 
    }

    texture_->SetData(0, 0, TEX_WIDTH, TEX_HEIGHT, texData); 
    texture_->SetMipmapCount(10); 
    texture_->SetFilter(TextureFilter::LINEAR); 
    texture_->SetWrapMode(TextureWrapMode::REPEAT); 
    texture_->Update(); 
}

void MeshRenderSystem::OnRender(Scene& scene, uint32 count, const EntityId* entities) 
{
    GraphicsDevice* gd = Engine::GetGraphicsDevice(); 
    Display* d = Engine::GetDisplay(); 

    gd->SetShader(shader_); 
    gd->SetTextureUnit(0, texture_); 

    shader_->SetMatrix4("oa_View", Matrix4::IDENTITY); 
    shader_->SetMatrix4("oa_Proj", Matrix4::Perspective(90 * OASIS_TO_RAD, d->GetAspectRatio(), 0.1, 100.0)); 
    shader_->SetTextureUnit("u_Texture", 0); 

    for (uint32 i = 0; i < count; i++) 
    {
        Entity e = scene.GetEntity(entities[i]); 

        Transform* transform = e.Get<Transform>(); 
        MeshContainer* meshContainer = e.Get<MeshContainer>(); 

        shader_->SetVector3("u_Color", { 1, 1, 1 }); 
        shader_->SetMatrix4("oa_Model", transform->CreateMatrix()); 

        // Logger::Info(transform->CreateMatrix()); 

        IndexBuffer* ib = meshContainer->mesh->GetIndexBuffer(0); 
        VertexBuffer* vb = meshContainer->mesh->GetVertexBuffer(); 

        gd->SetIndexBuffer(ib); 
        gd->SetVertexBuffer(vb); 
        gd->DrawIndexed(Primitive::TRIANGLE_LIST, 0, 6 * 6); 
    }
}