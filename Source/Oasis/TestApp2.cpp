#include <Oasis/Oasis.h> 

#include <iostream> 

using namespace Oasis; 
using namespace std; 

class TestApp2 : public Application 
{
public: 
    virtual ~TestApp2() = default; 

    void Init() override; 
    void Update(float dt) override; 
    void Render() override; 
    void Exit() override; 

    VertexArray* vao; 
    VertexBuffer* vbo; 
    IndexBuffer* ibo; 
};

void TestApp2::Init() 
{
    cout << "Init App" << endl; 

    auto g = Engine::GetSubsystem<Graphics>(); 

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

    vao = g->CreateVertexArray(); 
    vbo = g->CreateVertexBuffer(4, format); 
    ibo = g->CreateIndexBuffer(6); 

    vbo->SetData(0, 4, verts); 
    vbo->Update(); 
    ibo->SetData(0, 6, inds); 
    ibo->Update(); 
    vao->SetVertexBuffer(vbo); 
    vao->SetIndexBuffer(ibo); 
}

void TestApp2::Update(float dt) 
{

}

void TestApp2::Render() 
{
    auto g = Engine::GetSubsystem<Graphics>(); 
    auto w = Engine::GetSubsystem<Display>(); 

    g->SetShader(nullptr); 
    g->SetParameterVector3("u_Color", { 1, 1, 0 }); 
    g->SetParameterMatrix4("oa_View", Matrix4::Translation(-5)); 
    g->SetParameterMatrix4("oa_Model", Matrix4::IDENTITY); 
    g->SetParameterMatrix4("oa_Proj", Matrix4::Perspective(70 * OASIS_TO_RAD, w->GetAspectRatio(), 0.1, 100.0)); 

    g->SetVertexArray(vao); 
    g->DrawIndexed(Primitive::TRIANGLE_LIST, 0, 2); 
}

void TestApp2::Exit() 
{
    cout << "Exit App" << endl; 

    auto g = Engine::GetSubsystem<Graphics>(); 

    g->DestroyVertexArray(vao); 
    g->DestroyVertexBuffer(vbo); 
    g->DestroyIndexBuffer(ibo); 
}

int main(int argc, char** argv) 
{
    TestApp2 app; 
    Engine::Start(&app); 

    return 0; 
}