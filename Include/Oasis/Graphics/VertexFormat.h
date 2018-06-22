#pragma once

#include "Oasis/Common.h"
#include "Oasis/Graphics/Types.h" 

#include <vector>

namespace Oasis
{

class OASIS_API VertexFormat
{
public:
    static const VertexFormat POSITION;
    static const VertexFormat NORMAL;
    static const VertexFormat TANGENT;
    static const VertexFormat TEXTURE;
    static const VertexFormat COLOR;

    VertexFormat();
    VertexFormat(const VertexFormat& other);
    VertexFormat& operator=(const VertexFormat& other);
    ~VertexFormat() = default; 

    bool operator==(const VertexFormat& other) const;
    bool operator!=(const VertexFormat& other) const;

    VertexFormat& AddAttribute(Attribute attrib);

    Attribute GetAttribute(int index) const;

    int GetOffset(Attribute attrib) const;

    int GetAttributeCount() const;
    int GetSize() const;
private:
    std::vector<Attribute> elements_;
    int size_;
};

}

