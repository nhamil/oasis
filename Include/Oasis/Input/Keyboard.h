#pragma once 

#include "Oasis/Common.h"

// TODO: remove this 
#include <SDL2/SDL.h> 

namespace Oasis 
{

enum class Key 
{
    KEY_A = SDLK_a, 
    KEY_B = SDLK_b, 
    KEY_C = SDLK_c, 
    KEY_D = SDLK_d, 
    KEY_E = SDLK_e, 
    KEY_F = SDLK_f, 
    KEY_G = SDLK_g, 
    KEY_H = SDLK_h, 
    KEY_I = SDLK_i, 
    KEY_J = SDLK_j, 
    KEY_K = SDLK_k, 
    KEY_L = SDLK_l, 
    KEY_M = SDLK_m, 
    KEY_N = SDLK_n, 
    KEY_O = SDLK_o, 
    KEY_P = SDLK_p, 
    KEY_Q = SDLK_q, 
    KEY_R = SDLK_r, 
    KEY_S = SDLK_s, 
    KEY_T = SDLK_t, 
    KEY_U = SDLK_u, 
    KEY_V = SDLK_v, 
    KEY_W = SDLK_w, 
    KEY_X = SDLK_x, 
    KEY_Y = SDLK_y, 
    KEY_Z = SDLK_z, 

    KEY_0 = SDLK_0,
    KEY_1 = SDLK_1, 
    KEY_2 = SDLK_2, 
    KEY_3 = SDLK_3, 
    KEY_4 = SDLK_4, 
    KEY_5 = SDLK_5, 
    KEY_6 = SDLK_6, 
    KEY_7 = SDLK_7, 
    KEY_8 = SDLK_8, 
    KEY_9 = SDLK_9, 

    KEY_SPACE = SDLK_SPACE, 
    KEY_RSHIFT = SDLK_RSHIFT, 
    KEY_LSHIFT = SDLK_LSHIFT, 
    KEY_RETURN = SDLK_RETURN,  

    KEY_ESCAPE = SDLK_ESCAPE, 

    COUNT = 4096 
}; 

class OASIS_API Keyboard 
{
public: 
    Keyboard(); 
    ~Keyboard(); 

    void Update(); 
    void SetKey(Key key, bool down); 

    bool IsKeyDown(Key key) const; 
    bool IsKeyJustDown(Key key) const; 

private: 
    bool keys_[(int) Key::COUNT]; 
    bool lastKeys_[(int) Key::COUNT]; 
}; 

}