#include <Oasis/Oasis.h> 

#include <iostream> 
#include <memory> 

using namespace Oasis; 
using namespace std; 

static const string VERTEX_SOURCE = R"(#version 120 
attribute vec3 a_Position; 
uniform mat4 oa_Model; 
uniform mat4 oa_View; 
uniform mat4 oa_Proj; 
void main() 
{
    gl_Position = oa_Proj * oa_View * oa_Model * vec4(a_Position, 1.0); 
}
)"; 

static const string FRAGMENT_SOURCE = R"(#version 120
uniform vec3 u_Color; 
void main() 
{
    gl_FragColor = vec4(u_Color, 1.0); 
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

    VertexBuffer* vbo; 
    IndexBuffer* ibo; 
    Shader* shader; 
    float angle; 
    Mesh mesh; 
};

namespace Oasis { class Material; }

void TestApp2::Init() 
{
    cout << "Init App" << endl; 

    auto g = Engine::GetGraphicsDevice();  

    const VertexFormat& format = VertexFormat::POSITION; 

    float verts[] =
    {
        -0.5, -0.5, 0,
         0.5, -0.5, 0,
         0.5,  0.5, 0,
        -0.5,  0.5, 0,
    };

    short inds[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    mesh.SetVertexCount(4); 
    mesh.SetPositions((Vector3*) verts); 

    mesh.SetSubmeshCount(1); 
    mesh.SetIndices(0, 6, inds); 

    mesh.Upload(); 

    shader = g->CreateShader(VERTEX_SOURCE, FRAGMENT_SOURCE); 
}

void TestApp2::Update(float dt) 
{
    angle += 0.5 * dt; 
}

void TestApp2::Render() 
{
    auto g = Engine::GetGraphicsDevice(); 
    auto w = Engine::GetDisplay(); 

    shader->SetVector3("u_Color", { 1, 0, 0 }); 
    shader->SetMatrix4("oa_View", Matrix4::Translation({0, 0, -2})); 
    shader->SetMatrix4("oa_Model", Matrix4::RotationY(angle)); 
    shader->SetMatrix4("oa_Proj", Matrix4::Perspective(70 * OASIS_TO_RAD, w->GetAspectRatio(), 0.1, 100.0)); 
    shader->Flush(); 

    g->SetShader(shader); 
    //g->SetIndexBuffer(ibo); 
    //g->SetVertexBuffer(vbo); 
    g->SetIndexBuffer(mesh.GetIndexBuffer(0)); 
    g->SetVertexBuffer(mesh.GetVertexBuffer()); 
    g->DrawIndexed(Primitive::TRIANGLE_LIST, 0, 2 * 6); 
}

void TestApp2::Exit() 
{
    cout << "Exit App" << endl; 

    shader->Release(); 
    //vbo->Release(); 
    //ibo->Release(); 
}

int main(int argc, char** argv) 
{
    TestApp2 app; 
    Engine::Start(&app); 

    return 0; 
}