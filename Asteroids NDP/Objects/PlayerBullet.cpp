//
//  PlayerBullet.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 09/05/25.
//

#include "PlayerBullet.hpp"
#include <SDL.h>
#include <iostream>

PlayerBullet::PlayerBullet(int x, int y, int w, int h, const std::string& assetName, float bulletLifetime, float xSpeed, float ySpeed, float rotation)
    : GameObject(x, y, w, h, assetName, xSpeed, ySpeed, rotation, bulletLifetime) {}

void PlayerBullet::init(int x, int y, float xSpeed, float ySpeed, float newRotation){
    inUse = true;
    position.x = x;
    position.y = y;
    currentXSpeed = xSpeed;
    currentYSpeed = ySpeed;
    rotation = newRotation;
}

void PlayerBullet::update(float deltaTime){
    GameObject::update(deltaTime);
    
    position.x += (std::cos(degreesToRadians(90 - rotation)) * bulletSpeed + (currentXSpeed/2)) * deltaTime;
    position.y -= (std::sin(degreesToRadians(90 - rotation)) * bulletSpeed + (currentYSpeed/2)) * deltaTime;
}
