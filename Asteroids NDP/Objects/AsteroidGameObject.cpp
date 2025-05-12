//
//  AsteroidGameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#include "AsteroidGameObject.hpp"
#include "GameObject.hpp"

#include <iostream>

AsteroidGameObject::AsteroidGameObject(int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount, float lifeTime): GameObject(x, y, w, h, assetName, xSpeed, ySpeed), rotateAmount(rotateAmount), lifeTime(lifeTime) {}

void AsteroidGameObject::update(){ 
    timeAlive += 0.016f;
    
    if (timeAlive >= lifeTime){
        isAlive = false;
        return;
    }
    
    position.x += currentXSpeed;    
    position.y -= currentYSpeed;
    
    rotation += rotateAmount;
}
