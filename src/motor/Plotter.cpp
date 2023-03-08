#include "Plotter.hpp"

Plotter::Plotter(){} /*nada que inicializar*/

void Plotter::render_pixel(SDL_Renderer *r, Coordenadas p, SDL_Color color){
    /*designar como utilizar el alpha*/
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    /*asignar el color*/
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    /*pintar el pixel*/
    SDL_RenderDrawPoint(r,p.x,p.y);
}

void Plotter::render_linea(SDL_Renderer *r, Coordenadas p1, Coordenadas p2, SDL_Color color){
    /*implementar usando el algoritmo BRESSENHAM y el render_pixel
        NO USAR SDL_RenderDrawLine*/
}