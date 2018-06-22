#include "Oasis/Graphics/VertexFormat.h"

namespace Oasis
{

const VertexFormat VertexFormat::POSITION = VertexFormat().AddAttribute(Attribute::POSITION);
const VertexFormat VertexFormat::NORMAL = VertexFormat().AddAttribute(Attribute::NORMAL);
const VertexFormat VertexFormat::TANGENT = VertexFormat().AddAttribute(Attribute::TANGENT);
const VertexFormat VertexFormat::TEXTURE = VertexFormat().AddAttribute(Attribute::TEXTURE);
const VertexFormat VertexFormat::COLOR = VertexFormat().AddAttribute(Attribute::COLOR);

VertexFormat::VertexFormat()
    : elements_()
    , size_(0) {}

VertexFormat::VertexFormat(const VertexFormat& other)
    : elements_(other.elements_)
    , size_(other.size_) {}

VertexFormat& VertexFormat::operator=(const VertexFormat& other)
{
    if (this == &other) return *this;

    elements_ = other.elements_;
    size_ = other.size_;
    return *this;
}

bool VertexFormat::operator==(const VertexFormat& other) const
{
    return elements_ == other.elements_;
}

bool VertexFormat::operator!=(const VertexFormat& other) const
{
    return !(*this == other);
}

VertexFormat& VertexFormat::AddAttribute(Attribute attrib)
{
    elements_.push_back(attrib);
    size_ += GetAttributeSize(attrib);

    return *this;
}

Attribute VertexFormat::GetAttribute(int index) const
{
    return elements_[index];
}

int VertexFormat::GetAttributeCount() const
{
    return elements_.size();
}

int VertexFormat::GetSize() const
{
    return size_;
}

int VertexFormat::GetOffset(Attribute attrib) const
{
    int off = 0;

    for (unsigned i = 0; i < elements_.size(); i++)
    {
        if (elements_[i] == attrib) return off;

        off += GetAttributeSize(elements_[i]);
    }

    return 0;
}

}
