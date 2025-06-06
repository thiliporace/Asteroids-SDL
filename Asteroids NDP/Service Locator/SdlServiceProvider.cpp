//
//  SdlServiceProvider.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#include <iostream>
#include "SdlServiceProvider.hpp"

using namespace std;

SdlServiceProvider::SdlServiceProvider(){
    initializeSDL();
}

const void SdlServiceProvider::initializeSDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Error Init: " << SDL_GetError() << endl;
        return;
    }
    initializeSDLWindow();
    initializeSDLRenderer();
}

const void SdlServiceProvider::initializeSDLWindow(){
    window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    
    if (!window){
        cout << "Error Window: " << SDL_GetError() << endl;
        return;
    }
}

const void SdlServiceProvider::initializeSDLRenderer(){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!renderer){
        cout << "Error Renderer: " << SDL_GetError() << endl;
        return;
    }
}

SDL_Renderer* SdlServiceProvider::getRenderer(){
    return renderer;
}

SDL_Window* SdlServiceProvider::getWindow(){
    return window;
}

SdlServiceProvider::~SdlServiceProvider(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
