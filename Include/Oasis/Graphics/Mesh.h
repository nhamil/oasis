#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/GraphicsDevice.h"

#include <vector>

namespace Oasis
{

struct OASIS_API Submesh
{
    Submesh();
    ~Submesh(); 

    bool dirty = true;
    IndexBuffer* indexBuffer = nullptr;
    Primitive primitive = Primitive::TRIANGLE_LIST;
    std::vector<short> indices;
};

class OASIS_API Mesh
{
public:
    Mesh();
    ~Mesh();

    void Clear();
    void UploadToGPU();

    bool CalculateNormals();
    bool CalculateTangents();

    bool HasPositions() const { return positions_.size(); } 
    bool HasNormals() const { return normals_.size(); }
    bool HasTexCoords() const { return texCoords_.size(); }
    bool HasTangents() const { return tangents_.size(); }

    // attributes

    int GetVertexCount() const;
    void GetPositions(int start, int count, Vector3* out) const;
    void GetNormals(int start, int count, Vector3* out) const;
    void GetTexCoords(int start, int count, Vector2* out) const;
    void GetTangents(int start, int count, Vector3* out) const;

    void SetVertexCount(int count); 
    void SetPositions(const Vector3* positions);
    void SetNormals(const Vector3* normals);
    void SetTexCoords(const Vector2* texCoords);
    void SetTangents(const Vector3* tangents);

    VertexBuffer* GetVertexBuffer();

    // submeshes

    int GetSubmeshCount() const;
    int GetIndexCount(int submesh) const;
    void GetIndices(int submesh, int start, int count, short* in) const;

    void SetSubmeshCount(int count);
    bool SetIndices(int submesh, int count, const short* indices);

    IndexBuffer* GetIndexBuffer(int submesh);

private:
    OASIS_NO_COPY(Mesh)  

    bool verticesDirty_ = true;
    int vertexCount_ = 0;
    std::vector<Vector3> positions_;
    std::vector<Vector3> normals_;
    std::vector<Vector2> texCoords_;
    std::vector<Vector3> tangents_;
    VertexBuffer* vertexBuffer_ = nullptr;

    std::vector<Submesh> submeshes_;
};

}
