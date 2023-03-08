#include<SDL.h>
#include"src/SDLApp.hpp"
#include<iostream>
int main(int argc, char* argv[]){
    std::cout << "compilado" << "\n";

    return SDLApp::get().on_correr();
    //return 0;
}