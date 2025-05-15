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

void AsteroidGameObject::update(){ 
    timeAlive += 0.016f;
    
    if (isInvincible) {
        invincibilityTimer -= 0.016f;
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
    
    position.x += currentXSpeed;    
    position.y -= currentYSpeed;
    
    rotation += rotateAmount;
}

AsteroidType AsteroidGameObject::getAsteroidType(){
    return asteroidType;
}

bool AsteroidGameObject::canBeHit(){
    return !isInvincible;
}
