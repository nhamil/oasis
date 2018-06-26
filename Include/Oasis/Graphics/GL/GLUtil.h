#pragma once 

#include "Oasis/Common.h" 

#include <GL/glew.h> 

class GLGraphicsDevice; 
class GLIndexBuffer; 
class GLRenderTexture2D; 
class GLShader; 
class GLTexture2D; 
class GLVertexBuffer; 

#if 0 

#define GLCALL(x) { \
    Logger::Debug("Calling GL function: ", #x, " from ", __FILE__, ":", __LINE__); \
    x; \
    int glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) Logger::Debug("GLError: ", glerror); }

#else 

#define GLCALL(x) { \
    x; \
    int glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) Logger::Debug("GLError: ", glerror, " at ", __FILE__, ":", __LINE__); }

#endif 