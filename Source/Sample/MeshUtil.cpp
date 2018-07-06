#include "Sample/MeshUtil.h" 

Mesh* MeshUtil::CreateCube() 
{
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

    Mesh* mesh = new Mesh(); 
    mesh->SetVertexCount(4 * 6); 
    mesh->SetSubmeshCount(1); 
    mesh->SetPositions((Vector3*) verts); 
    mesh->SetTexCoords((Vector2*) texCoords); 
    mesh->SetIndices(0, 6 * 6, inds); 
    mesh->UploadToGPU(); 

    return mesh; 
}