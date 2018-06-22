#pragma once 

#include <iostream> 
#include <GL/glew.h> 

#if 1 

#define GLCALL(x) { \
    std::cout << "Calling GL function: " << #x /*<< " from " << __FILE__ << ":" << __LINE__*/ << std::endl; \
    x; \
    int glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) std::cout << "GLError: " << glerror << std::endl; }

#else 

#define GLCALL(x) { \
    x; \
    int glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) std::cout << "GLError: " << glerror << " at " << __FILE__ << ":" << __LINE__ << std::endl; }

#endif 