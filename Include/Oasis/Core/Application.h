#pragma once

#include "Oasis/Oasis.h"
#include "Oasis/Core/Config.h"

namespace Oasis
{

class OASIS_API Application
{
public:
    Application() {} 
    virtual ~Application() {}

    virtual Config GetConfig() const { return Config(); }

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;
};

}
