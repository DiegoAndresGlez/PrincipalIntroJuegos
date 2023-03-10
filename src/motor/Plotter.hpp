#include<SDL.h>
#include "../utilidad/Estructuras.hpp"

class Plotter
{
    private:
        Plotter();
    public:
        static void render_pixel(SDL_Renderer *r, Coordenadas p, SDL_Color color);
        static void render_linea(SDL_Renderer *r, Coordenadas p1, Coordenadas p2, SDL_Color color);
};