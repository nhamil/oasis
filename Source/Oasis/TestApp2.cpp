#include <Oasis/Oasis.h> 

#include <iostream> 
#include <memory> 

#define BLACK (char)0, (char)0, (char)0, (char)0 
#define WHITE (char)255, (char)255, (char)255, (char)255 

using namespace Oasis; 
using namespace std; 

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

    void Init() override; 
    void Update(float dt) override; 
    void Render() override; 
    void Exit() override; 

    Shader* shader; 
    Texture2D* texture; 
    float angle; 
    Mesh mesh; 
};

namespace Oasis { class Material; }

void TestApp2::Init() 
{
    cout << "Init App" << endl; 

    cout << "Size of Texture: " << sizeof (Texture) << endl; 

    auto g = Engine::GetGraphicsDevice();  

    float verts[] =
    {
        -0.5, -0.5, 0,
         0.5, -0.5, 0,
         0.5,  0.5, 0,
        -0.5,  0.5, 0,
    };

    float texCoords[] = 
    {
        0, 0, 
        1, 0, 
        1, 1, 
        0, 1, 
    };

    short inds[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    mesh.SetVertexCount(4); 
    mesh.SetSubmeshCount(1); 
    mesh.SetPositions((Vector3*) verts); 
    mesh.SetTexCoords((Vector2*) texCoords); 
    mesh.SetIndices(0, 6, inds); 
    mesh.UploadToGPU(); 

    shader = g->CreateShader(VERTEX_SOURCE, FRAGMENT_SOURCE); 

    texture = g->CreateTexture2D(TextureFormat::RGBA8, 8, 8); 

    char texData[] = 
    {
        BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, 
        WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, 
        BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, 
        WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, 
        BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, 
        WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, 
        BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, 
        WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, 
    };

    texture->SetData(0, 0, 8, 8, texData); 
    texture->FlushToGPU(); 
}

void TestApp2::Update(float dt) 
{
    angle += 2 * dt; 
}

void TestApp2::Render() 
{
    auto g = Engine::GetGraphicsDevice(); 
    auto w = Engine::GetDisplay(); 

    shader->SetVector3("u_Color", { 1, 1, 1 }); 
    shader->SetMatrix4("oa_View", Matrix4::Translation({0, 0, -1})); 
    shader->SetMatrix4("oa_Model", Matrix4::RotationY(angle)); 
    shader->SetMatrix4("oa_Proj", Matrix4::Perspective(70 * OASIS_TO_RAD, w->GetAspectRatio(), 0.1, 100.0)); 
    shader->SetTextureUnit("u_Texture", 0); 
    shader->FlushToGPU(); 

    g->SetTextureUnit(0, texture); 
    g->SetShader(shader); 
    g->SetIndexBuffer(mesh.GetIndexBuffer(0)); 
    g->SetVertexBuffer(mesh.GetVertexBuffer()); 
    g->DrawIndexed(Primitive::TRIANGLE_LIST, 0, 2 * 6); 
}

void TestApp2::Exit() 
{
    cout << "Exit App" << endl; 

    shader->Release(); 
}

int main(int argc, char** argv) 
{
    (void) argc; 
    (void) argv; 

    Engine::Start(new TestApp2); 

    return 0; 
}