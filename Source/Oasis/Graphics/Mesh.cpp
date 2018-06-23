#include "Oasis/Graphics/Mesh.h" 

#include "Oasis/Core/Engine.h" 
#include "Oasis/Graphics/IndexBuffer.h" 
#include "Oasis/Graphics/VertexBuffer.h" 

#define OASIS_MESH_SET_ATTRIBUTE(list, in) { \
    list.clear(); \
    list.reserve(vertexCount_); \
    if (in) \
    { \
        for (int i = 0; i < vertexCount_; i++) \
        { \
            list.push_back(in[i]); \
        } \
    } \
    verticesDirty_ = true; }

#define OASIS_MESH_GET_ATTRIBUTE(list, out) \
    for (int i = 0; i < count; i++) out[i] = list[i + start]; 

#define OASIS_MESH_PUSH_BACK_VEC2(list, vec) { \
    list.push_back(vec.x); \
    list.push_back(vec.y); }

#define OASIS_MESH_PUSH_BACK_VEC3(list, vec) { \
    list.push_back(vec.x); \
    list.push_back(vec.y); \
    list.push_back(vec.z); }

using namespace std; 

namespace Oasis 
{

Submesh::Submesh() 
{

}

Submesh::~Submesh() 
{
    if (indexBuffer) indexBuffer->Release(); 
}

Mesh::Mesh() 
{

}

Mesh::~Mesh() 
{
    if (vertexBuffer_) vertexBuffer_->Release(); 
}

void Mesh::Clear() 
{
    verticesDirty_ = true; 

    positions_.clear(); 
    normals_.clear(); 
    texCoords_.clear(); 
    tangents_.clear(); 
}

void Mesh::UploadToGPU() 
{
    // vertices 

    //cout << "Mesh: start upload" << endl; 

    if (verticesDirty_) {
        VertexFormat format; 

        if (HasPositions()) format.AddAttribute(Attribute::POSITION); 
        if (HasNormals()) format.AddAttribute(Attribute::NORMAL); 
        if (HasTexCoords()) format.AddAttribute(Attribute::TEXTURE); 
        if (HasTangents()) format.AddAttribute(Attribute::TANGENT); 

        //cout << "Mesh: create vertex buffer" << endl; 

        if (!vertexBuffer_) vertexBuffer_ = Engine::GetGraphicsDevice()->CreateVertexBuffer(vertexCount_, format); 
        else 
        {
            vertexBuffer_->SetVertexFormat(format); 
            vertexBuffer_->SetElementCount(vertexCount_); 
        }

        //cout << "Mesh: format vertices" << endl; 

        vector<float> vertices; 
        vertices.reserve(vertexCount_ * format.GetSize()); 

        for (int i = 0; i < vertexCount_; i++) 
        {
            if (HasPositions()) OASIS_MESH_PUSH_BACK_VEC3(vertices, positions_[i]); 
            if (HasNormals()) OASIS_MESH_PUSH_BACK_VEC3(vertices, normals_[i]); 
            if (HasTexCoords()) OASIS_MESH_PUSH_BACK_VEC2(vertices, texCoords_[i]); 
            if (HasTangents()) OASIS_MESH_PUSH_BACK_VEC3(vertices, tangents_[i]); 
        }

        //cout << "Mesh: upload vertices " << format.GetSize() << endl; 

        vertexBuffer_->SetData(0, vertexCount_, &vertices[0]); 
        vertexBuffer_->FlushToGPU(); 
        verticesDirty_ = false; 
    }

    //cout << "Mesh: done with vertices" << endl; 

    // indices 

    for (int submesh = 0; submesh < GetSubmeshCount(); submesh++) 
    {
        Submesh& sm = submeshes_[submesh]; 

        if (sm.dirty) 
        {
            int indCount = sm.indices.size(); 

            if (!sm.indexBuffer) sm.indexBuffer = Engine::GetGraphicsDevice()->CreateIndexBuffer(indCount); 
            sm.indexBuffer->SetElementCount(indCount); 
            sm.indexBuffer->SetData(0, indCount, &sm.indices[0]); 
            sm.indexBuffer->FlushToGPU(); 
            sm.dirty = false; 
        }
    }

    //cout << "Mesh: done with indices" << endl; 
}

int Mesh::GetVertexCount() const 
{
    return vertexCount_; 
}

void Mesh::GetPositions(int start, int count, Vector3* out) const 
{
    OASIS_MESH_GET_ATTRIBUTE(positions_, out); 
}

void Mesh::GetNormals(int start, int count, Vector3* out) const 
{
    OASIS_MESH_GET_ATTRIBUTE(normals_, out); 
}

void Mesh::GetTexCoords(int start, int count, Vector2* out) const 
{
    OASIS_MESH_GET_ATTRIBUTE(texCoords_, out); 
}

void Mesh::GetTangents(int start, int count, Vector3* out) const 
{
    OASIS_MESH_GET_ATTRIBUTE(tangents_, out); 
}

void Mesh::SetVertexCount(int count) 
{
    if (GetVertexCount() == count) return; // already correct no need to change 

    Clear(); 
    vertexCount_ = count; 
}

void Mesh::SetPositions(const Vector3* in) 
{
    OASIS_MESH_SET_ATTRIBUTE(positions_, in); 
}

void Mesh::SetNormals(const Vector3* in) 
{
    OASIS_MESH_SET_ATTRIBUTE(normals_, in); 
}

void Mesh::SetTexCoords(const Vector2* in) 
{
    OASIS_MESH_SET_ATTRIBUTE(texCoords_, in); 
}

void Mesh::SetTangents(const Vector3* in) 
{
    OASIS_MESH_SET_ATTRIBUTE(tangents_, in); 
}

VertexBuffer* Mesh::GetVertexBuffer() 
{
    return vertexBuffer_; 
}

int Mesh::GetSubmeshCount() const 
{
    return submeshes_.size(); 
}

int Mesh::GetIndexCount(int submesh) const 
{
    return submeshes_[submesh].indices.size(); 
}

void Mesh::GetIndices(int submesh, int start, int count, short* indices) const
{
    auto& data = submeshes_[submesh].indices; 

    for (int i = 0; i < count; i++) 
    {
        indices[i] = data[start + i]; 
    }
}

void Mesh::SetSubmeshCount(int count) 
{
    submeshes_.resize(count); 
}

bool Mesh::SetIndices(int submesh, int count, const short* indices) 
{
    Submesh& sm = submeshes_[submesh]; 

    sm.dirty = true; 
    sm.indices.resize(count); 

    for (int i = 0; i < count; i++) 
    {
        sm.indices[i] = indices[i]; 
    }

    return true; 
}

IndexBuffer* Mesh::GetIndexBuffer(int submesh) 
{
    return submeshes_[submesh].indexBuffer; 
}

}