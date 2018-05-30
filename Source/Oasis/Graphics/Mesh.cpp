#include "Oasis/Graphics/Mesh.h"

#include <iostream>

using namespace std;

namespace Oasis
{

Submesh::Submesh()
    : update(true)
    , vertexArray(NULL)
    , indexBuffer(NULL)
    , primitive(PRIMITIVE_TRIANGLE_LIST)
    , indices() {}

Mesh::Mesh()
    : updateVertices_(true)
    , vertexCount_(0)
    , positions_()
    , normals_()
    , texCoords_()
    , tangents_()
    , vertexBuffer_(NULL)
    , submeshes_()
{
    SetSubmeshCount(1);
}

Mesh::~Mesh()
{
    Release();
}

void Mesh::Release()
{
    updateVertices_ = true;

    for (unsigned i = 0; i < submeshes_.size(); i++)
    {
        Submesh& sm = submeshes_[i];

        if (sm.vertexArray) sm.vertexArray->Release();
        if (sm.indexBuffer) sm.indexBuffer->Release();
    }

    submeshes_.clear();

    if (vertexBuffer_)
    {
        vertexBuffer_->Release();
        delete vertexBuffer_;
        vertexBuffer_ = NULL;
    }
}

void Mesh::Clear()
{
    // clear vertices
    vertexCount_ = 0;
    positions_.clear();
    normals_.clear();
    texCoords_.clear();
    tangents_.clear();
    updateVertices_ = true;

    // clear and remove indices
    for (unsigned i = 0; i < submeshes_.size(); i++)
    {
        Submesh& sm = submeshes_[i];

        if (sm.vertexArray) sm.vertexArray->Release();
        if (sm.indexBuffer) sm.indexBuffer->Release();
    }

    submeshes_.clear();
    SetSubmeshCount(1);
}

void Mesh::Upload()
{
    Graphics* g = Engine::GetGraphics();
    // TODO finish

    if (updateVertices_)
    {
        if (positions_.size())
        {
            int floatsPerElement = 3;

            VertexFormat format;
            format.AddAttribute(ATTRIBUTE_POSITION);

            if (normals_.size()) { floatsPerElement += 3; format.AddAttribute(ATTRIBUTE_NORMAL); }
            if (texCoords_.size()) { floatsPerElement += 2; format.AddAttribute(ATTRIBUTE_TEXTURE); }
            if (tangents_.size()) { floatsPerElement += 3; format.AddAttribute(ATTRIBUTE_TANGENT); }

            if (!vertexBuffer_)
            {
                vertexBuffer_ = g->CreateVertexBuffer(vertexCount_, format);
            }
            else
            {
                vertexBuffer_->SetElementCount(vertexCount_);
            }

            float element[floatsPerElement];

            for (int i = 0; i < vertexCount_; i++)
            {
                int j = 0;

                element[j++] = positions_[i].x;
                element[j++] = positions_[i].y;
                element[j++] = positions_[i].z;

                if (normals_.size())
                {
                    element[j++] = normals_[i].x;
                    element[j++] = normals_[i].y;
                    element[j++] = normals_[i].z;
                }

                if (texCoords_.size())
                {
                    element[j++] = texCoords_[i].x;
                    element[j++] = texCoords_[i].y;
                }

                if (tangents_.size())
                {
                    element[j++] = tangents_[i].x;
                    element[j++] = tangents_[i].y;
                    element[j++] = tangents_[i].z;
                }

                vertexBuffer_->SetData(i, 1, element);
            }

            vertexBuffer_->Upload();
        }
        else if (vertexBuffer_)
        {
            vertexBuffer_->Release();
            delete vertexBuffer_;
            vertexBuffer_ = NULL;
        }
    }

    // set buffers of all submeshes
    for (unsigned i = 0; i < submeshes_.size(); i++)
    {
        Submesh& s = submeshes_[i];

        if (!s.indexBuffer) s.indexBuffer = g->CreateIndexBuffer(s.indices.size());
        s.indexBuffer->SetData(0, s.indices.size(), &s.indices[0]);
        s.indexBuffer->Upload();

        if (!s.vertexArray) s.vertexArray = g->CreateVertexArray();
        s.vertexArray->SetVertexBuffer(vertexBuffer_);
        s.vertexArray->SetIndexBuffer(s.indexBuffer);
        s.vertexArray->Upload();
    }
}

bool Mesh::CalculateNormals()
{
    // TODO finish
    return false;
}

bool Mesh::CalculateTangents()
{
    // TODO finish
    return false;
}

void Mesh::ClearAttributes()
{
    positions_.clear();
    normals_.clear();
    texCoords_.clear();
    tangents_.clear();
}

void Mesh::SetPositions(int count, const Vector3* positions)
{
    updateVertices_ = true;

    if (vertexCount_ != count)
    {
        vertexCount_ = count;
        ClearAttributes();
    }

    positions_.clear();
    for (int i = 0; i < count; i++) positions_.push_back(positions[i]);
}

void Mesh::SetNormals(const Vector3* normals)
{
    updateVertices_ = true;

    normals_.clear();
    for (int i = 0; i < vertexCount_; i++) normals_.push_back(normals[i]);
}

void Mesh::SetTexCoord(const Vector2* texCoords)
{
    updateVertices_ = true;

    texCoords_.clear();
    for (int i = 0; i < vertexCount_; i++) texCoords_.push_back(texCoords[i]);
}

void Mesh::SetTangents(const Vector3* tangents)
{
    updateVertices_ = true;

    tangents_.clear();
    for (int i = 0; i < vertexCount_; i++) tangents_.push_back(tangents[i]);
}

int Mesh::GetVertexCount() const
{
    return vertexCount_;
}

void Mesh::GetPositions(int start, int count, Vector3* in) const
{
    for (int i = 0; i < count; i++)
    {
        in[i] = positions_[i + start];
    }
}

void Mesh::GetNormals(int start, int count, Vector3* in) const
{
    for (int i = 0; i < count; i++)
    {
        in[i] = normals_[i + start];
    }
}

void Mesh::GetTexCoords(int start, int count, Vector2* in) const
{
    for (int i = 0; i < count; i++)
    {
        in[i] = texCoords_[i + start];
    }
}

void Mesh::GetTangents(int start, int count, Vector3* in) const
{
    for (int i = 0; i < count; i++)
    {
        in[i] = tangents_[i + start];
    }
}

VertexBuffer* Mesh::GetVertexBuffer()
{
    return vertexBuffer_;
}

void Mesh::SetSubmeshCount(int count)
{
    int curSize = (int) submeshes_.size();

    for (int i = curSize; i > count; i--)
    {
        // remove more than count submeshes
        submeshes_.pop_back();
    }

    curSize = (int) submeshes_.size();

    for (int i = curSize; i < count; i++)
    {
        // add submeshes to make count correct
        submeshes_.push_back(Submesh());
    }
}

void Mesh::SetIndices(int submesh, int count, const short* indices)
{
    Submesh& s = submeshes_[submesh];
    s.update = true;

    s.indices.clear();

    for (int i = 0; i < count; i++)
    {
        s.indices.push_back(indices[i]);
    }
}

int Mesh::GetSubmeshCount() const
{
    return submeshes_.size();
}

int Mesh::GetIndexCount(int submesh) const
{
    return submeshes_[submesh].indices.size();
}

void Mesh::GetIndices(int submesh, int start, int count, short* in) const
{
    const Submesh& s = submeshes_[submesh];
    for (int i = 0; i < count; i++)
    {
        in[i] = s.indices[i + start];
    }
}

VertexArray* Mesh::GetVertexArray(int submesh)
{
    return submeshes_[submesh].vertexArray;
}

IndexBuffer* Mesh::GetIndexBuffer(int submesh)
{
    return submeshes_[submesh].indexBuffer;
}

}
