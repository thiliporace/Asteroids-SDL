//
//  main.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include <iostream>
#include <list>

#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "SdlManager.hpp"
#include "GameObject.hpp"

const float MS_PER_UPDATE = 0.016;

std::list<GameObject*> gameObjectsInScene;

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void update(){
    
}

void render(SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    
    for(GameObject* gameObject : gameObjectsInScene){
        SDL_RenderCopy(renderer, gameObject->getTexture(), NULL, &gameObject->position);
    }
    
    SDL_RenderPresent(renderer);
}

int main(int argc, const char * argv[]) {
    SdlManager* sdlManager = SdlManager::getInstance();
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    double lag = 0.0;
    //Objetos:
    GameObject* playerShip = new GameObject(400, 400, 40, 40, "playerShip.png");
    gameObjectsInScene.push_back(playerShip);
    
    while (!quit){
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        
        while (lag >= MS_PER_UPDATE){
            update();
            lag -= MS_PER_UPDATE;
        }
        
        render(renderer);
    }
    
    for (auto obj : gameObjectsInScene) delete obj;
    return 0;
}
