#include "Oasis/Graphics/Shader.h" 

using namespace std; 

namespace Oasis 
{

Shader::Shader(const string& vs, const string& fs) 
    : vSource_(vs) 
    , fSource_(fs) 
{
    
}

Shader::~Shader() 
{
    
}

void Shader::Update() 
{
    UploadToGPU(); 
}

void Shader::ClearParameter(const string& name) 
{
    auto it = parameters_.find(name); 

    if (it != parameters_.end()) 
    {
        auto& param = it->second; 
        param.Reset();
        FlagUpdateParameter(name); 
    }
}

void Shader::SetParameter(const string& name, const Parameter& value) 
{
    auto it = parameters_.find(name); 

    if (it != parameters_.end()) 
    {
        auto& param = it->second; 
        param.Set(value); 
        if (param.dirty) FlagUpdateParameter(name); 
    }
}

}