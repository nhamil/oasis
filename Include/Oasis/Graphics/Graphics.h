#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/BufferUsage.h" 
#include "Oasis/Graphics/VertexFormat.h" 
#include "Oasis/Math/MathUtil.h"

#include <string>

namespace Oasis
{

class IndexBuffer;
class VertexArray;
class Shader;
class Texture;
class Texture2D;
class VertexBuffer;

enum class Primitive
{
    LINE_LIST,
    LINE_STRIP,
    TRIANGLE_LIST,
    TRIANGLE_STRIP,

    count
};

class OASIS_API Graphics 
{
public: 
    void SetClearColor(float r, float g, float b); 
    void Clear(bool colorBuffer = true, bool depthBuffer = true); 

    void SetViewport(int x, int y, int w, int h); 

    void SetShader(Shader* shader); 
    void SetVertexArray(VertexArray* vertexArray); 

    void ClearParameter(const std::string& name); 
    void SetParameter(const std::string& name, const Parameter& value); 

    inline void SetParameterInt(const std::string& name, int value) { SetParameter(name, Parameter(value)); } 
    inline void SetParameterFloat(const std::string& name, float value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterVector2(const std::string& name, const Vector2& value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterVector3(const std::string& name, const Vector3& value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterVector4(const std::string& name, const Vector4& value) { SetParameter(name, Parameter(value)); } 
    inline void SetParameterMatrix3(const std::string& name, const Matrix3& value) { SetParameter(name, Parameter(value)); }  
    inline void SetParameterMatrix4(const std::string& name, const Matrix4& value) { SetParameter(name, Parameter(value)); }  

    void Draw(Primitive prim, int start, int primCount); 
    void DrawIndexed(Primitive prim, int start, int primCount); 

    Shader* CreateShader(const std::string& vSource, const std::string& fSource); 
    void DestroyShader(Shader* shader); 

    VertexArray* CreateVertexArray(); 
    void DestroyVertexArray(VertexArray* vertexArray); 

    IndexBuffer* CreateIndexBuffer(int numElements, BufferUsage usage = BufferUsage::DYNAMIC); 
    void DestroyIndexBuffer(IndexBuffer* indexBuffer); 

    VertexBuffer* CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage = BufferUsage::DYNAMIC); 
    void DestroyVertexBuffer(VertexBuffer* vertexBuffer); 

private: 
    friend class Engine; 

    void PreRender(); 
    void PostRender(); 

    void BindVertexArray(); 

    Graphics(); 
    ~Graphics(); 

    Vector3 clearColor_ = Vector3::ZERO; 
    Vector4 viewport_ = Vector4::ZERO; 
    VertexArray* curVertexArray_ = nullptr; 
};

#if 0 
class OASIS_API Graphics
{
public:
    virtual ~Graphics() {}

    virtual int GetMaxTextureCount() const = 0;

    virtual void PreRender() = 0;
    virtual void PostRender() = 0;

    virtual void SetViewport(int x, int y, int w, int h) = 0;

    virtual void SetClearColor(const Vector4& color) = 0;
    virtual void Clear() = 0;

    virtual void SetVertexArray(VertexArray* geom) = 0;
    virtual void SetShader(Shader* shader) = 0;

    virtual void SetTexture(int unit, Texture* tex) = 0;

    virtual void DrawArrays(Primitive prim, int start, int primCount) = 0;
    virtual void DrawIndexed(Primitive prim, int start, int primCount) = 0;

    virtual Uniform GetUniform(const std::string& name) = 0;
    virtual bool HasUniform(const std::string& name) = 0;
    virtual bool ClearUniform(const std::string& name) = 0;
    virtual bool SetUniform(const std::string& name, int value) = 0;
    virtual bool SetUniform(const std::string& name, float value) = 0;
    virtual bool SetUniform(const std::string& name, const Vector2& value) = 0;
    virtual bool SetUniform(const std::string& name, const Vector3& value) = 0;
    virtual bool SetUniform(const std::string& name, const Vector4& value) = 0;
    virtual bool SetUniform(const std::string& name, const Matrix3& value) = 0;
    virtual bool SetUniform(const std::string& name, const Matrix4& value) = 0;

    virtual IndexBuffer* CreateIndexBuffer(int numElements, BufferUsage usage = BufferUsage::DYNAMIC) = 0;

    virtual VertexBuffer* CreateVertexBuffer(int numElements, const VertexFormat& format, BufferUsage usage = BufferUsage::DYNAMIC) = 0;

    virtual VertexArray* CreateVertexArray() = 0;

    virtual Shader* CreateShader(const std::string& vertexSource, const std::string& fragmentSource) = 0;
};
#endif 

}
