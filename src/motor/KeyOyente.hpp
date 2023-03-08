#pragma once
#include<SDL.h>
class KeyOyente{
    private:
        KeyOyente();
        bool keys[350];
    public:
        static KeyOyente& get();
        static void keyPresionado(SDL_Event *e);
        static bool estaPresionado(int key){return get().keys[key];};
};