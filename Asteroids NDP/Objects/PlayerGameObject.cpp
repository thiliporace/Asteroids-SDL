//
//  PlayerGO.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "PlayerGameObject.hpp"
#include <stdio.h>
#include <iostream>

PlayerGameObject::PlayerGameObject(int x, int y, int w, int h, const char* assetName)
    : GameObject(x, y, w, h, assetName), isMoving(false) {}

void PlayerGameObject::update(){
    
    if(isMoving){
        position.x += currentXSpeed;
        position.y -= currentYSpeed;
    }
    else{
        currentXSpeed *= 0.95;
        currentYSpeed *= 0.95;
        
        if (std::fabs(currentXSpeed) < 0.1) currentXSpeed = 0;
        if (std::fabs(currentYSpeed) < 0.1) currentYSpeed = 0;
        
        position.x += currentXSpeed;
        position.y -= currentYSpeed;
    }
}

void PlayerGameObject::setIsMoving(bool b){
    isMoving = b;
}

void PlayerGameObject::calculateMovementDirection(){
    currentXSpeed += std::cos(degreesToRadians(90 - rotation)) * playerShipMoveSpeed;
    currentYSpeed += std::sin(degreesToRadians(90 - rotation)) * playerShipMoveSpeed;
}
