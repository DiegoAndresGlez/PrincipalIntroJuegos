#include <SDL.h>
#include <SDL_ttf.h>
#include "SDLApp.hpp"
#include "utilidad/Tiempo.hpp"
#include "motor/KeyOyente.hpp"
#include "motor/MouseOyente.hpp"
SDLApp::SDLApp(){
    this->vnt = nullptr;
    this->vntsurf = nullptr;
    this->render = nullptr;

    bg_color.r = 255; //rojo
    bg_color.g = 255; //verde
    bg_color.b = 255; //azul
    bg_color.a = 255; //alpha

    this->esta_corriendo = true;
    this->WIDTH = 1024;
    this->HEIGHT = 720;
};

//bool SDLApp::on_init(){return true;};
//void SDLApp::on_evento(SDL_Event* evento){};
//void SDLApp::on_frameupdate(double dt){};

void SDLApp::on_limpiar(){
    SDL_DestroyRenderer(get().render);
    SDL_FreeSurface(get().vntsurf);
    SDL_DestroyWindow(get().vnt);
    SDL_Quit();
};

SDLApp& SDLApp::get(){
    static SDLApp instancia;
    return instancia;
}

int SDLApp::on_correr(){
    //tiempo
    double inicio = Tiempo::get_tiempo();

    //revisar que todo se inicializo bien
    if(get().on_init()==false){return -1;}

    SDL_Event eventos;
    double dt = 0;
    while(get().estaCorriendo())
    {
        //captura eventos
        while(SDL_PollEvent(&eventos))
        {
            get().on_evento(&eventos);
        }

        //actualizamos si inicia o hay una diferencia de tiempo
        if(dt >= 0)
        {
            get().on_fisicaupdate(dt);
            get().on_frameupdate(dt);
        }

        //calculamos el tiempo del frame
        double fin = Tiempo::get_tiempo();
        dt = fin-inicio; //diferencia
        inicio = fin; //el nuevo frame inicia en este tiempo

    }
    //liberamos memoria
    get().on_limpiar();
    return 0;
}

bool SDLApp::on_init(){
    //revisar que SDL inicio bien
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }
    //crear la ventana
    get().vnt = SDL_CreateWindow(
        "Juego", //Titulo
        SDL_WINDOWPOS_UNDEFINED, //posicion X
        SDL_WINDOWPOS_UNDEFINED, //posicion Y
        get().WIDTH, //ancho
        get().HEIGHT, //alto
        SDL_WINDOW_OPENGL); //que use OPENGL
    
    //inicializar ttf
    TTF_Init();

    //revisar que se creo bien la ventana
    if(get().vnt == NULL){
        printf("No se creo la ventana por: %s", SDL_GetError());
        return false;
    }
    //la forma de procesar en GPU
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "opengl");
    //creamos el 'canvas'
    get().render = SDL_CreateRenderer(
        get().vnt, //la ventana
        -1, //driver
        SDL_RENDERER_ACCELERATED);
    //revisamos si se creo correctamente
    if(get().render == NULL){
        printf("No se creo el renderer por: %s", SDL_GetError());
        return false;
    }
    //agregamos el color del background del frame
    SDL_SetRenderDrawColor(
        get().render,       //canvas
        get().bg_color.r,   //rojo
        get().bg_color.g,   //verde
        get().bg_color.b,   //azul
        SDL_ALPHA_TRANSPARENT); //como usar el alpha

    return true;
}

void SDLApp::on_evento(SDL_Event* evento){
    if(evento->type == SDL_QUIT){
        get().esta_corriendo = false;
    }
    //eventos del mouse
    MouseOyente::get().evento_movimiento(evento);
    MouseOyente::get().evento_presionado(evento);
    MouseOyente::get().evento_scroll(evento);
    //que esta presionado
    KeyOyente::get().keyPresionado(evento);
}

void SDLApp::on_fisicaupdate(double dt){
    //printf("Esta presionado W: %d\n", KeyOyente::get().estaPresionado(SDLK_w));
}

void SDLApp::on_frameupdate(double dt){
    //limpiar frame
    SDL_RenderClear(get().render);

    //posicion del mouse
    int mx = MouseOyente::get().getX();
    int my = MouseOyente::get().getY();
    std::string pm = "mouse("+std::to_string(mx)+","+std::to_string(my)+")";
    render_texto(get().render, 815, 630, pm, 20, SDL_Color{0,0,0},"onuava");
    //mensaje X
    render_texto(
        get().render,
        (get().WIDTH/2)-100,
        (get().HEIGHT/2),
        "SI FUNCIONA",
        50,
        SDL_Color{0,0,255}
    );
    //fps
    render_texto(
        get().render,
        get().WIDTH-100,
        30,
        std::to_string((int)(1/dt))+" fps",
        18,
        SDL_Color{0,135,62},
        "onuava");

    //Mostrar frame
    SDL_RenderPresent(get().render);

    //resetear color del frame
    SDL_SetRenderDrawColor(
        get().render,
        get().bg_color.r,
        get().bg_color.g,
        get().bg_color.b,
        SDL_ALPHA_TRANSPARENT);

}

void SDLApp::render_texto(SDL_Renderer *ren, int x, int y, std::string texto, int fontsize, SDL_Color color, std::string font){
    //Agregar el font
    std::string ff = "assets//fonts//"+font+".ttf";
    TTF_Font* fontTipo = TTF_OpenFont(ff.c_str(), fontsize);
    //revisamos que si localizamos el font
    if(fontTipo == NULL){
        printf("No se encontro el FONT: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //creamos una superficie donde pintar
    SDL_Surface* surftexto = TTF_RenderText_Solid(
        fontTipo,
        texto.c_str(),
        color
    );
    //la convertimos en textura
    SDL_Texture *textexto = SDL_CreateTextureFromSurface(
        ren,
        surftexto
    );
    //lo pintamos en un cuadro que se mostrara en el canvas
    SDL_Rect rectexto;
    rectexto.x = x;
    rectexto.y = y;
    rectexto.w = surftexto->w;
    rectexto.h = surftexto->h;

    //mandarlo a mostrar al canvas
    SDL_RenderCopy(
        ren,
        textexto,
        NULL,
        &rectexto
    );

    //liberamos la memoria
    TTF_CloseFont(fontTipo);
    SDL_DestroyTexture(textexto);
    SDL_FreeSurface(surftexto);
}
