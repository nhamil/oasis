#include "Oasis/Input/Keyboard.h"

namespace Oasis 
{

Keyboard::Keyboard() 
{
    for (int i = 0; i < KEY_COUNT; i++) lastKeys_[i] = keys_[i] = false; 
} 

Keyboard::~Keyboard() {} 

void Keyboard::Update() 
{
    for (int i = 0; i < KEY_COUNT; i++) lastKeys_[i] = keys_[i]; 
}

void Keyboard::SetKey(Key key, bool down) 
{
    if (key >= 0 && key < KEY_COUNT) keys_[key] = down; 
}

bool Keyboard::IsKeyDown(Key key) const 
{
    return keys_[key]; 
}

bool Keyboard::IsKeyJustDown(Key key) const 
{
    return keys_[key] && !lastKeys_[key]; 
}

}