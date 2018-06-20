#pragma once

#include "Oasis/Common.h" 

#include "Oasis/Core/Application.h" 
#include "Oasis/Core/ClassId.h" 
#include "Oasis/Core/Config.h" 
#include "Oasis/Core/Display.h" 
#include "Oasis/Core/Engine.h"
#include "Oasis/Core/ReferenceCounted.h" 
#include "Oasis/Core/Timer.h" 
#include "Oasis/Core/TimeUtil.h" 

#include "Oasis/Input/Keyboard.h" 

#include "Oasis/Graphics/GraphicsDevice.h"
#include "Oasis/Graphics/IndexBuffer.h" 
#include "Oasis/Graphics/Mesh.h" 
#include "Oasis/Graphics/Shader.h" 
#include "Oasis/Graphics/VertexBuffer.h" 
#include "Oasis/Graphics/VertexFormat.h" 

#include "Oasis/Math/MathUtil.h" 

#ifndef OASIS_MAIN 
    #define OASIS_MAIN(AppName) \
        int main(int argc, char** argv) { \
            AppName oasisApp; \
            return Engine::Start(&oasisApp); \
        }
#endif 