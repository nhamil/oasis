#pragma once

#include "Oasis/Oasis.h"

namespace Oasis
{

class Application; 
class Graphics;
class Keyboard; 
class Window;

namespace Engine
{

OASIS_API bool IsRunning();

OASIS_API int Start(Application* app);
OASIS_API void Stop();

OASIS_API float GetFrameRate(); 
OASIS_API float GetUpdateRate(); 

OASIS_API Graphics* GetGraphics();

OASIS_API Window* GetWindow();

OASIS_API Keyboard* GetKeyboard(); 

}

}
