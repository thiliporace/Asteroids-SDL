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
//const float MS_PER_UPDATE = 0.016;
const float MS_PER_UPDATE = 0.008;

//Variavel pra spawn do jogador
const float playerSpawnTime = 3;

//Variaveis pra delay no tiro do jogador
const float delayBetweenShots = 0.2f;
float currentTimeBetweenShots;
float lastTimeBulletShot;

//Variavel pra delay no spawn de asteroides
const float delayBetweenAsteroids = 0.5f;
float asteroidsDelayTimer;

//Objeto do Player:
std::unique_ptr<PlayerGameObject> playerShip;
PlayerGameObject* playerShipPtr;

std::unique_ptr<AsteroidSpawner> asteroidSpawner;
AsteroidSpawner* asteroidSpawnerPtr;

//Singleton pra funções comuns do SDL
SdlManager* sdlManager = SdlManager::getInstance();

//Armazena todos os objetos na cena pra atualizar todos de uma vez
std::list<std::unique_ptr<GameObject>> gameObjectsInScene; //Ponteiros inteligentes pra evitar problemas com gerenciamento de memória

CollisionDetection collisionDetection = CollisionDetection();

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void spawnAsteroidSpawner(){
    asteroidSpawner = std::make_unique<AsteroidSpawner>(*playerShipPtr);
    asteroidSpawnerPtr = asteroidSpawner.get();
}

void spawnPlayer(){
    playerShip = std::make_unique<PlayerGameObject>(400, 400, 40, 40, "playerShip.png");
    playerShipPtr = playerShip.get();
    gameObjectsInScene.push_back(std::move(playerShip));
    
    asteroidSpawner.reset();
    spawnAsteroidSpawner();
}

Uint32 respawnPlayer(Uint32 interval, void* params){
    spawnPlayer();
    return 0;
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
                    gameObjectsInScene.push_back(asteroidSpawnerPtr->SpawnAsteroid(SMALL,objectB->position.x,objectB->position.y));
                    objectB->setIsAlive(false);
                }
                
                objectA->setIsAlive(false);
                break;
            }
        }
    }

}

//TODO: Desacoplar taxa de quadros com velocidade do jogo
void update(float deltaTime){
    asteroidsDelayTimer += 0.03 * deltaTime;
    if (asteroidsDelayTimer > delayBetweenAsteroids){
        asteroidsDelayTimer = 0;
        if (asteroidSpawnerPtr != nullptr) gameObjectsInScene.push_back(asteroidSpawnerPtr->SpawnAsteroid());
    }
    
    checkAsteroidBulletCollision();
    
    for (auto& gameObject : gameObjectsInScene){
        if (!gameObject->getIsAlive()) {
            if(dynamic_cast<PlayerGameObject*>(gameObject.get()) != nullptr) SDL_AddTimer(playerSpawnTime * 1000,respawnPlayer,NULL);
            gameObjectsInScene.remove(gameObject);
            break;
        }
        gameObject->update(deltaTime);
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

void handlePlayerMovement(){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    if (playerShipPtr == nullptr || !playerShipPtr->getIsAlive()) return;
        
    if (keystate[SDL_SCANCODE_W]) {
        playerShipPtr->setIsMoving(true);
    }
    else {
        playerShipPtr->setIsMoving(false);
    }
    
    if (keystate[SDL_SCANCODE_A]){
        playerShipPtr->setIsRotating(true, false);
    }
    else if (keystate[SDL_SCANCODE_D]){
        playerShipPtr->setIsRotating(false, true);
    }
    else{
        playerShipPtr->setIsRotating(false, false);
    }
}

int main(int argc, const char * argv[]) {
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    
    double lag = 0.0;
    double fpsCounter = 0.0;
    
    int frames = 0;
    
    spawnPlayer();
    
    spawnAsteroidSpawner();
    
    gameObjectsInScene.push_back(asteroidSpawnerPtr->SpawnAsteroid());
    
    while (!quit){
        
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        fpsCounter += elapsed;
        
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (playerShipPtr == nullptr || !playerShipPtr->getIsAlive()) break;
                    currentTimeBetweenShots = getCurrentTime();
                    if (currentTimeBetweenShots - lastTimeBulletShot > delayBetweenShots){
                        lastTimeBulletShot = currentTimeBetweenShots;
                        gameObjectsInScene.push_back(std::make_unique<PlayerBullet>(playerShipPtr->position.x,
                            playerShipPtr->position.y,30, 30, "playerBullet.png",3,playerShipPtr->currentXSpeed,
                            playerShipPtr->currentYSpeed,playerShipPtr->rotation));
                    }
                    break;
            }
            
        }
        
        handlePlayerMovement();
        
        //Usando o Game Programming Pattern Update pra manter uma taxa de frames fixa, com um time step fixo e uma renderização variável (como não passamos lag residual pra renderização, em máquinas mais lentas a renderização pode ocorrer menos frequentemente que o update, causando artefatos visuais. Como essa máquina é meio goat (bode) a renderização sempre roda mais rápidp (uns 1000fps enquanto o update roda a 144fps))
        while (lag >= MS_PER_UPDATE){
            frames++;
            update(lag * 25);
            lag -= MS_PER_UPDATE;
        }
        
        if (fpsCounter >= 1.0f){
            fpsCounter = 0;
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
        }
        
        render(renderer);
    }
    
    return 0;
}
