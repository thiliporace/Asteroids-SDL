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
    : GameObject(x, y, w, h, assetName, xSpeed, ySpeed, rotation), lifetime(bulletLifetime) {}

void PlayerBullet::update(float deltaTime){
    timeAlive += deltaTime;
    
    if (timeAlive >= lifetime){
        isAlive = false;
        return;
    }
    
    position.x += (std::cos(degreesToRadians(90 - rotation)) * bulletSpeed + (currentXSpeed/2)) * deltaTime;
    position.y -= (std::sin(degreesToRadians(90 - rotation)) * bulletSpeed + (currentYSpeed/2)) * deltaTime;
}
