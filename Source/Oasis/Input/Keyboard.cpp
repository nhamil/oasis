#include "Oasis/Input/Keyboard.h"

namespace Oasis 
{

Keyboard::Keyboard() 
{
    for (int i = 0; i < (int) Key::COUNT; i++) lastKeys_[i] = keys_[i] = false; 
} 

Keyboard::~Keyboard() {} 

void Keyboard::Update() 
{
    for (int i = 0; i < (int) Key::COUNT; i++) lastKeys_[i] = keys_[i]; 
}

void Keyboard::SetKey(Key key, bool down) 
{
    int code = (int) key; 
    if (code >= 0 && code < (int) Key::COUNT) keys_[code] = down; 
}

bool Keyboard::IsKeyDown(Key key) const 
{
    int code = (int) key; 
    return keys_[code]; 
}

bool Keyboard::IsKeyJustDown(Key key) const 
{
    int code = (int) key; 
    return keys_[code] && !lastKeys_[code]; 
}

}