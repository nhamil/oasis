#pragma once

#include "Oasis/Common.h"

#include "Oasis/Math/Transform.h"

namespace Oasis
{

class OASIS_API Camera
{
public:
    Camera();
    ~Camera();

private:
    Transform transform_;
};

}
