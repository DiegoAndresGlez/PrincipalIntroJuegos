#pragma once
#include<SDL.h>
#include<vector>
#include<string>
class SDLApp{
    private:
        SDLApp();
        bool on_init();
        void on_evento(SDL_Event *evento);
        void on_fisicaupdate(double dt);
        void on_frameupdate(double dt);
        void on_limpiar();
        void render_texto(SDL_Renderer* ren,
                        int x,
                        int y,
                        std::string texto,
                        int fontsize,
                        SDL_Color color,
                        std::string font = "SunnySpells");

        bool esta_corriendo;
        int WIDTH;
        int HEIGHT;

        SDL_Window* vnt;
        SDL_Surface* vntsurf;
        SDL_Renderer* render;

    public:
        SDL_Color bg_color;
        static int on_correr();
        static void set_bgcolor(Uint8 rojo, Uint8 verde, Uint8 azul);
        static SDLApp& get();
        static bool estaCorriendo() {return get().esta_corriendo;};

};