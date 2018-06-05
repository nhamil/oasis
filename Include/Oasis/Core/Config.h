#pragma once

#include "Oasis/Common.h"

namespace Oasis
{

enum class GraphicsBackend
{
    NONE = 0,
    OPENGL = 1,
    DONT_CARE = 2, 

    count
};

struct OASIS_API Config
{
    GraphicsBackend graphicsBackend = GraphicsBackend::DONT_CARE;
    double targetFps = 60;
    double targetUps = 60;
};

}
