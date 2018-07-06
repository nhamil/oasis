#pragma once

#include "Oasis/Common.h" 

#include "Oasis/Core/Application.h" 
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
#include "Oasis/Graphics/Renderer.h" 
#include "Oasis/Graphics/RenderTexture2D.h" 
#include "Oasis/Graphics/Shader.h" 
#include "Oasis/Graphics/Texture.h" 
#include "Oasis/Graphics/Texture2D.h" 
#include "Oasis/Graphics/VertexBuffer.h" 
#include "Oasis/Graphics/VertexFormat.h" 

#include "Oasis/Math/MathUtil.h" 

#include "Oasis/Scene/Component.h" 
#include "Oasis/Scene/Entity.h" 
#include "Oasis/Scene/Scene.h" 
#include "Oasis/Scene/SceneManager.h" 
#include "Oasis/Scene/System.h" 

#include "Oasis/Util/ClassId.h" 
#include "Oasis/Util/IdManager.h" 

#ifndef OASIS_MAIN 
    #define OASIS_MAIN(AppName) \
        int main(int argc, char** argv) { \
            (void) argc; \
            (void) argv; \
            return Engine::Start(new AppName); \
        }
#endif 