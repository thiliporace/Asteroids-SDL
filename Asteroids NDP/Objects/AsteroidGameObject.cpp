//
//  AsteroidGameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#include "Grid.hpp"
#include "AsteroidGameObject.hpp"

#include <iostream>

AsteroidGameObject::AsteroidGameObject(AsteroidType asteroidType, int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount, float lifeTime, PlayerGameObject& playerGO, std::shared_ptr<Grid> grid): GameObject(x, y, w, h, assetName, xSpeed, ySpeed, 0, grid), asteroidType(asteroidType), rotateAmount(rotateAmount), lifeTime(lifeTime), playerGO(playerGO), playerRect(playerGO.position) {}

std::shared_ptr<AsteroidGameObject> AsteroidGameObject::Create(AsteroidType asteroidType, int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount, float lifeTime, PlayerGameObject& playerGO, std::shared_ptr<Grid> grid)
{
    auto newAsteroid = std::make_shared<AsteroidGameObject>(asteroidType, x, y, w, h, assetName, xSpeed, ySpeed, rotateAmount, lifeTime, playerGO, grid);

    if (grid) {
        grid->add(newAsteroid);
    }

    return newAsteroid;
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
    
    float newX = position.x + currentXSpeed * deltaTime;
    float newY = position.y - currentYSpeed * deltaTime;
    
    move(newX, newY);
    
    rotation += rotateAmount * deltaTime;
    
    if(collisionDetection.checkCollision(position, playerRect)){
        if(playerGO.canBeHit()) playerGO.setIsAlive(false);
    }
}

AsteroidType AsteroidGameObject::getAsteroidType(){
    return asteroidType;
}

bool AsteroidGameObject::canBeHit(){
    return !isInvincible;
}
