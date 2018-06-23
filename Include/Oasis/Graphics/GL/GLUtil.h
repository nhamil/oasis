#pragma once 

#include "Oasis/Common.h" 

#include <GL/glew.h> 

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