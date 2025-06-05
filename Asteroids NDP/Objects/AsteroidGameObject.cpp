//
//  AsteroidGameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#include "AsteroidGameObject.hpp"

#include <iostream>

AsteroidGameObject::AsteroidGameObject(AsteroidType asteroidType, int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount, float lifeTime, std::shared_ptr<PlayerGameObject> playerGO): GameObject(x, y, w, h, assetName, xSpeed, ySpeed, rotateAmount, lifeTime), asteroidType(asteroidType), rotateAmount(rotateAmount), playerGO(playerGO) {
    collisionDetection = CollisionDetection();
}

void AsteroidGameObject::update(float deltaTime){ 
    GameObject::update(deltaTime);
    
    if (isInvincible) {
        invincibilityTimer -= deltaTime;
        if (invincibilityTimer <= 0) {
            isInvincible = false;
        }
    }
    
    if(collisionDetection.checkCollision(position, playerGO->position)){
        if(playerGO->canBeHit()) playerGO->inUse = false;
    }
    
    position.x += currentXSpeed * deltaTime;
    position.y -= currentYSpeed * deltaTime;
    
    rotation += rotateAmount * deltaTime;
}

void AsteroidGameObject::init(AsteroidType newAsteroidType, int x, int y, float xSpeed, float ySpeed, float newRotation, std::shared_ptr<PlayerGameObject> newPlayerGO) {
    inUse = true;
    asteroidType = newAsteroidType;
    position.x = x;
    position.y = y;
    currentXSpeed = xSpeed;
    currentYSpeed = ySpeed;
    rotation = newRotation;
    playerGO = newPlayerGO;
}

AsteroidType AsteroidGameObject::getAsteroidType(){
    return asteroidType;
}

bool AsteroidGameObject::canBeHit(){
    return !isInvincible;
}
