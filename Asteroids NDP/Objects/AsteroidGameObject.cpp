//
//  AsteroidGameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#include "AsteroidGameObject.hpp"

#include <iostream>

AsteroidGameObject::AsteroidGameObject(AsteroidType asteroidType, int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount, float lifeTime, PlayerGameObject& playerGO): GameObject(x, y, w, h, assetName, xSpeed, ySpeed), asteroidType(asteroidType), rotateAmount(rotateAmount), lifeTime(lifeTime), playerGO(playerGO), playerRect(playerGO.position) {
    collisionDetection = CollisionDetection();
}

void AsteroidGameObject::update(float deltaTime){ 
    timeAlive += deltaTime;
    
    if (isInvincible) {
        invincibilityTimer -= deltaTime;
        if (invincibilityTimer <= 0) {
            isInvincible = false;
        }
    }
    
    if (timeAlive >= lifeTime){
        isAlive = false;
        return;
    }
    
    if(collisionDetection.checkCollision(position, playerRect)){
        if(playerGO.canBeHit()) playerGO.setIsAlive(false);
    }
    
    position.x += currentXSpeed * deltaTime;
    position.y -= currentYSpeed * deltaTime;
    
    rotation += rotateAmount * deltaTime;
}

AsteroidType AsteroidGameObject::getAsteroidType(){
    return asteroidType;
}

bool AsteroidGameObject::canBeHit(){
    return !isInvincible;
}
