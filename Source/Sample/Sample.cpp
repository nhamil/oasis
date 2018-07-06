#include <Oasis/Oasis.h> 

#include "Sample/Components.h" 
#include "Sample/MeshRenderSystem.h" 
#include "Sample/MeshUtil.h" 
#include "Sample/MovementSystem.h" 

using namespace Oasis; 

class SampleApp : public Application 
{
public: 
    void Init() override; 
    void Update(float dt) override; 
    void Render() override; 
    void Exit() override; 
};

class Tester : public ReferenceCounted 
{
public: 
    Tester() 
    {
        Logger::Debug("ctor"); 
    }

    ~Tester() 
    {
        Logger::Debug("dtor"); 
    }

    void Print() 
    {
        Logger::Debug("RefCount: ", GetRefCount(), ", WeakRefCount: ", GetWeakRefCount()); 
    }
};

void SampleApp::Init() 
{
    Scene* scene = Engine::GetSceneManager()->CreateAndSetScene("SampleScene"); 

    scene->AddSystem(new MovementSystem()); 
    scene->AddSystem(new MeshRenderSystem()); 

    for (int z = -10; z <= 2; z++) 
    for (int y = -2; y <= 2; y++) 
    for (int x = -3; x <= 3; x++) 
    {
        Entity e = scene->CreateEntity(); 

        Transform* transform = e.Attach<Transform>(); 
        transform->position = Vector3(x, y, z - 3); 
        transform->rotation = Quaternion::AxisAngle(Vector3::UP, 15 * OASIS_TO_RAD);
        transform->scale = Vector3(0.25, 0.25, 0.25); 
        
        Velocity* velocity = e.Attach<Velocity>(); 
        velocity->positional = Vector3(rand() % 1000 * 0.0002 - 0.1, rand() % 1000 * 0.0002 - 0.1, rand() % 1000 * 0.0001 - 0.1); 
        velocity->rotational = Vector3(rand() % 40 * OASIS_TO_RAD, rand() % 40 * OASIS_TO_RAD, rand() % 40 * OASIS_TO_RAD); 

        MeshContainer* meshContainer = e.Attach<MeshContainer>(); 
        meshContainer->mesh = MeshUtil::CreateCube(); 
    }
}

void SampleApp::Update(float dt) 
{

}

void SampleApp::Render() 
{

}

void SampleApp::Exit() 
{

}

OASIS_MAIN(SampleApp) 
