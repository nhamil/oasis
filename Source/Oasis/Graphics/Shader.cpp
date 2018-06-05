#include "Oasis/Graphics/Shader.h" 

using namespace std; 

namespace Oasis 
{

static const int OGL_ATTRIBUTE_INDEX[ATTRIBUTE_COUNT] =
{
    0, 1, 2, 3, 4
};

static const string OGL_ATTRIBUTE_NAME[ATTRIBUTE_COUNT] =
{
    "a_Position",
    "a_Normal",
    "a_Bitangent",
    "a_Texture",
    "a_Color"
};

Shader::Shader(const string& vs, const string& fs) 
{

}

Shader::~Shader() {}

}