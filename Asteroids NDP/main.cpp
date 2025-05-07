//
//  main.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include <iostream>
#include <list>
#include <cmath>

#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "SdlManager.hpp"
#include "GameObject.hpp"
#include "PlayerGameObject.hpp"

const float MS_PER_UPDATE = 0.016;
const float playerShipMoveSpeed = 2;

std::list<GameObject*> gameObjectsInScene;

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

void calculateMovementDirection(GameObject* playerShip){
    playerShip->currentXSpeed += std::cos(degreesToRadians(90 - playerShip->rotation)) * playerShipMoveSpeed;
    playerShip->currentYSpeed += std::sin(degreesToRadians(90 - playerShip->rotation)) * playerShipMoveSpeed;

}

void update(){
    for (GameObject* gameObject : gameObjectsInScene){
        gameObject->position.x += gameObject->currentXSpeed;
        gameObject->position.y -= gameObject->currentYSpeed;
    }
}

void render(SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    
    for(GameObject* gameObject : gameObjectsInScene){
        SDL_RenderCopyEx(renderer, gameObject->getTexture(), NULL, &gameObject->position, gameObject->rotation, NULL, SDL_FLIP_NONE);
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
    PlayerGameObject* playerShip = new PlayerGameObject(400, 400, 40, 40, "playerShip.png");
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
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                            calculateMovementDirection(playerShip);
                            break;
                        case SDL_SCANCODE_A:
                            playerShip->rotation -= 20;
                            break;
                        case SDL_SCANCODE_D:
                            playerShip->rotation += 20;
                            break;
                        default:
                            break;
                    }
                case SDL_KEYUP:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                            std::lerp(playerShip->currentXSpeed, 0, 0.5);
                            std::lerp(playerShip->currentYSpeed, 0, 0.5);
                            break;
                        default:
                            break;
                    }
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
