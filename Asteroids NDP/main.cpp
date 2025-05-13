//
//  main.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>

#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "SdlManager.hpp"
#include "GameObject.hpp"
#include "PlayerGameObject.hpp"
#include "PlayerBullet.hpp"
#include "AsteroidSpawner.hpp"
#include "CollisionDetection.hpp"

using namespace std;

//60 FPS
const float MS_PER_UPDATE = 0.016;

//Variaveis pra delay no tiro do jogador
const float delayBetweenShots = 0.2f;
float currentTimeBetweenShots;
float lastTimeBulletShot;

//Variavel pra delay no spawn de asteroides
const float delayBetweenAsteroids = 0.5f;
float asteroidsDelayTimer;

//Objeto do Player:
std::unique_ptr<PlayerGameObject> playerShip = std::make_unique<PlayerGameObject>(400, 400, 40, 40, "playerShip.png");
PlayerGameObject* playerShipPtr = playerShip.get();

AsteroidSpawner asteroidSpawner(*static_cast<GameObject*>(playerShipPtr));

//Singleton pra funções comuns do SDL
SdlManager* sdlManager = SdlManager::getInstance();

//Armazena todos os objetos na cena pra atualizar todos de uma vez
std::list<std::unique_ptr<GameObject>> gameObjectsInScene; //Ponteiros inteligentes pra evitar problemas com gerenciamento de memória

CollisionDetection collisionDetection = CollisionDetection();

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void checkAsteroidBulletCollision(){
    for(auto& objectA : gameObjectsInScene){
        if(dynamic_cast<PlayerBullet*>(objectA.get()) == nullptr) continue;
        
        for (auto& objectB : gameObjectsInScene){
            AsteroidGameObject* asteroidObject = dynamic_cast<AsteroidGameObject*>(objectB.get());
            if(asteroidObject == nullptr || !asteroidObject->canBeHit()) continue;
            
            if (collisionDetection.checkCollision(objectA->position, objectB->position)){
                AsteroidGameObject* asteroidObject = static_cast<AsteroidGameObject*>(objectB.get());
                
                if (asteroidObject->getAsteroidType() == SMALL){
                    objectB->setIsAlive(false);
                }
                else{
                    gameObjectsInScene.push_back(asteroidSpawner.SpawnAsteroid(SMALL,objectB->position.x,objectB->position.y));
                    objectB->setIsAlive(false);
                }
                
                objectA->setIsAlive(false);
                break;
            }
        }
    }

}

//TODO: Taxa de atualizacao dispara quando mexe no mouse
void update(){
    
    asteroidsDelayTimer += 0.016;
    if (asteroidsDelayTimer > delayBetweenAsteroids){
        asteroidsDelayTimer = 0;
        gameObjectsInScene.push_back(asteroidSpawner.SpawnAsteroid());
    }
    
    checkAsteroidBulletCollision();
    
    for (auto& gameObject : gameObjectsInScene){
        if (!gameObject->getIsAlive()) {
            gameObjectsInScene.remove(gameObject);
            break;
        }
        gameObject->update();
    }
    
    
}

void render(SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    
    for(auto& gameObject : gameObjectsInScene){
        if (!gameObject->getIsAlive() || !gameObject->getTexture()) continue;
                
        SDL_RenderCopyExF(renderer, gameObject->getTexture(), NULL, &gameObject->position, gameObject->rotation, NULL, SDL_FLIP_NONE);
    }
    
    SDL_RenderPresent(renderer);
}

int main(int argc, const char * argv[]) {
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    double lag = 0.0;
    
    gameObjectsInScene.push_back(asteroidSpawner.SpawnAsteroid());
    gameObjectsInScene.push_back(std::move(playerShip));
    
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
                
                case SDL_MOUSEBUTTONDOWN:
                    currentTimeBetweenShots = getCurrentTime();
                    if (currentTimeBetweenShots - lastTimeBulletShot > delayBetweenShots){
                        lastTimeBulletShot = currentTimeBetweenShots;
                        gameObjectsInScene.push_back(std::make_unique<PlayerBullet>(playerShipPtr->position.x,
                            playerShipPtr->position.y,30, 30, "playerBullet.png",3,playerShipPtr->currentXSpeed,
                            playerShipPtr->currentYSpeed,playerShipPtr->rotation));
                    }
                    break;
            }
            const Uint8* keystate = SDL_GetKeyboardState(NULL);
                
            if (keystate[SDL_SCANCODE_W]) {
                playerShipPtr->setIsMoving(true);
                playerShipPtr->calculateMovementDirection();
            }
            else {
                playerShipPtr->setIsMoving(false);
            }
                
            if (keystate[SDL_SCANCODE_A]){
                playerShipPtr->rotation -= 15;
            }
            if (keystate[SDL_SCANCODE_D]){
                playerShipPtr->rotation += 15;
            }
            
        }
        
        while (lag >= MS_PER_UPDATE){
            update();
            lag -= MS_PER_UPDATE;
        }
        
        render(renderer);
    }
    
    return 0;
}
