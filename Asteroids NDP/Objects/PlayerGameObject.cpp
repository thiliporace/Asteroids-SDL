//
//  PlayerGO.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "PlayerGameObject.hpp"
#include <stdio.h>
#include <iostream>

PlayerGameObject::PlayerGameObject(int x, int y, int w, int h, const std::string& assetName)
    : GameObject(x, y, w, h, assetName), isMoving(false), isRotatingLeft(false), isRotatingRight(false) {}

void PlayerGameObject::update(float deltaTime){
    
    calculateRotation(deltaTime);
    
    if(isInvincible){
        invincibilityTimer += deltaTime;
        if (invincibilityTimer > invincibilityCooldown){
            isInvincible = false;
        }
    }
    
    if(isMoving){
        calculateSpeed(deltaTime);
        position.x += currentXSpeed * deltaTime;
        position.y -= currentYSpeed * deltaTime;
    }
    else{
        currentXSpeed *= 0.97;
        currentYSpeed *= 0.97;
        
        if (std::fabs(currentXSpeed) < 0.1) currentXSpeed = 0;
        if (std::fabs(currentYSpeed) < 0.1) currentYSpeed = 0;
        
        position.x += currentXSpeed * deltaTime;
        position.y -= currentYSpeed * deltaTime;
    }
}

void PlayerGameObject::setIsMoving(bool b){
    isMoving = b;
}

void PlayerGameObject::calculateSpeed(float deltaTime){
    currentXSpeed += std::cos(degreesToRadians(90 - rotation)) * playerShipMoveSpeed * deltaTime;
    currentYSpeed += std::sin(degreesToRadians(90 - rotation)) * playerShipMoveSpeed * deltaTime;
}

void PlayerGameObject::calculateRotation(float deltaTime){
    if (isRotatingLeft){
        rotation -= playerShipRotateSpeed * deltaTime;
    }
    else if (isRotatingRight){
        rotation += playerShipRotateSpeed * deltaTime;
    }
}

void PlayerGameObject::setIsRotating(bool left, bool right){
    isRotatingLeft = left;
    isRotatingRight = right;
}

bool PlayerGameObject::canBeHit(){
    return !isInvincible;
}

