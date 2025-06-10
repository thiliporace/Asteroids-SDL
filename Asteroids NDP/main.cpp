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
#include "Label.hpp"

using namespace std;

//60 FPS
//const float MS_PER_UPDATE = 0.016;
//240 FPS
const float MS_PER_UPDATE = 0.004;

//Variavel pra spawn do jogador
const float playerSpawnTime = 3;

//Variaveis pra delay no tiro do jogador
const float delayBetweenShots = 0.05f;
float currentTimeBetweenShots;
float lastTimeBulletShot;

//Variavel pra delay no spawn de asteroides
const float delayBetweenAsteroids = 0.06f;
float asteroidsDelayTimer;

//Objeto do Player:
std::shared_ptr<PlayerGameObject> playerShip; //Usando shared_ptr porque várias partes do código precisam da referencia dele.

std::shared_ptr<AsteroidSpawner> asteroidSpawner;

int points = 0;
std::shared_ptr<Label> pointsLabel = std::make_shared<Label>(50,50,points,"");

int lives = 4;
std::shared_ptr<Label> livesLabel = std::make_shared<Label>(50,100,lives,"Lives: ");

//Singleton pra funções comuns do SDL
SdlManager* sdlManager = SdlManager::getInstance();

//Armazena todos os objetos na cena pra atualizar todos de uma vez
std::list<std::shared_ptr<GameObject>> gameObjectsInScene; //Ponteiros inteligentes pra evitar problemas com gerenciamento de memória

CollisionDetection collisionDetection = CollisionDetection();

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void spawnAsteroidSpawner(){
    asteroidSpawner = std::make_shared<AsteroidSpawner>(*playerShip);
}

void spawnPlayer(){
    playerShip = std::make_shared<PlayerGameObject>(400, 400, 40, 40, "playerShip.png");
    gameObjectsInScene.push_back(playerShip);
    
    asteroidSpawner.reset();
    spawnAsteroidSpawner();
}

Uint32 respawnPlayer(Uint32 interval, void* params){
    if (lives <= 0) return 0;
    
    spawnPlayer();
    return 0;
}

void checkAsteroidBulletCollision(){
    for(auto& objectA : gameObjectsInScene){
        for (auto& objectB : gameObjectsInScene){
            
            if (objectA == objectB) {
                continue;
            }

            PlayerBullet* bullet = nullptr;
            AsteroidGameObject* asteroid = nullptr;

            if (dynamic_cast<PlayerBullet*>(objectA.get()) && dynamic_cast<AsteroidGameObject*>(objectB.get())) {
                bullet = static_cast<PlayerBullet*>(objectA.get());
                asteroid = static_cast<AsteroidGameObject*>(objectB.get());
            }
            else if (dynamic_cast<AsteroidGameObject*>(objectA.get()) && dynamic_cast<PlayerBullet*>(objectB.get())) {
                asteroid = static_cast<AsteroidGameObject*>(objectA.get());
                bullet = static_cast<PlayerBullet*>(objectB.get());
            }

            if (bullet == nullptr || asteroid == nullptr) {
                continue;
            }
            
            if (!bullet->getIsAlive() || !asteroid->getIsAlive() || !asteroid->canBeHit()) {
                continue;
            }

            if (collisionDetection.checkCollision(bullet->position, asteroid->position)){
                
                if (asteroid->getAsteroidType() == SMALL){
                    asteroid->setIsAlive(false);
                }
                else {
                    gameObjectsInScene.push_back(asteroidSpawner->SpawnAsteroid(SMALL, asteroid->position.x, asteroid->position.y));
                    asteroid->setIsAlive(false);
                }
                
                points += 60;
                pointsLabel->setValue(points);
                bullet->setIsAlive(false);
                
                break;
            }
        }
    }
}

//TODO: Desacoplar taxa de quadros com velocidade do jogo
void update(float deltaTime){
    asteroidsDelayTimer += deltaTime;
    if (asteroidsDelayTimer > delayBetweenAsteroids){
        asteroidsDelayTimer = 0;
        if (asteroidSpawner != nullptr) gameObjectsInScene.push_back(asteroidSpawner->SpawnAsteroid());
    }
    
    checkAsteroidBulletCollision();
    
    for (auto& gameObject : gameObjectsInScene){
        if (!gameObject->getIsAlive()) {
            if(dynamic_cast<PlayerGameObject*>(gameObject.get()) != nullptr) {
                lives -= 1;
                livesLabel->setValue(lives);
                SDL_AddTimer(playerSpawnTime * 1000,respawnPlayer,NULL);
            }
            
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
    
    SDL_RenderCopy(renderer, pointsLabel->textTexture, NULL, &pointsLabel->rect);
    SDL_RenderCopy(renderer, livesLabel->textTexture, NULL, &livesLabel->rect);
    
    SDL_RenderPresent(renderer);
}

void handlePlayerMovement(){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    const Uint32 mousestate = SDL_GetMouseState(NULL, NULL);
        
    if (playerShip == nullptr || !playerShip->getIsAlive()) return;
    
    if (mousestate & SDL_BUTTON(SDL_BUTTON_LEFT)){
        if (playerShip == nullptr || !playerShip->getIsAlive()) return;
        currentTimeBetweenShots = getCurrentTime();
        if (currentTimeBetweenShots - lastTimeBulletShot > delayBetweenShots){
            lastTimeBulletShot = currentTimeBetweenShots;
            gameObjectsInScene.push_back(std::make_unique<PlayerBullet>(playerShip->position.x,
                playerShip->position.y,30, 30, "playerBullet.png",3,playerShip->currentXSpeed,
                playerShip->currentYSpeed,playerShip->rotation));
        }
    }
        
    if (keystate[SDL_SCANCODE_W]) {
        playerShip->setIsMoving(true);
    }
    else {
        playerShip->setIsMoving(false);
    }
    
    if (keystate[SDL_SCANCODE_A]){
        playerShip->setIsRotating(true, false);
    }
    else if (keystate[SDL_SCANCODE_D]){
        playerShip->setIsRotating(false, true);
    }
    else{
        playerShip->setIsRotating(false, false);
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
    
    gameObjectsInScene.push_back(asteroidSpawner->SpawnAsteroid());
    
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
            }
            
        }
        
        handlePlayerMovement();
        
        //Usando o Game Programming Pattern Update pra manter uma taxa de frames fixa, com um time step fixo e uma renderização variável (como não passamos lag residual pra renderização, em máquinas mais lentas a renderização pode ocorrer menos frequentemente que o update, causando artefatos visuais. Como essa máquina é meio goat 🐐 (bode 🐐) a renderização sempre roda mais rápido (uns 1000fps enquanto o update roda a uma taxa fixa))
        while (lag >= MS_PER_UPDATE){
            frames++;
            update(MS_PER_UPDATE);
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
