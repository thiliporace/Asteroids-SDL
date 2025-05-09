//
//  PlayerBullet.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 09/05/25.
//

#include "PlayerBullet.hpp"
#include <SDL.h>
#include <iostream>

PlayerBullet::PlayerBullet(int x, int y, int w, int h, const char* assetName, float bulletLifetime, float xSpeed, float ySpeed, float rotation)
    : GameObject(x, y, w, h, assetName, xSpeed, ySpeed, rotation), lifetime(bulletLifetime) {}

void PlayerBullet::update(){
    timeAlive += 0.016f;
    
    if (timeAlive >= lifetime){
        std::cout << "a" << std::endl;
        isAlive = false;
        return;
    }
    
    position.x += std::cos(degreesToRadians(90 - rotation)) * bulletSpeed + currentXSpeed;
    position.y -= std::sin(degreesToRadians(90 - rotation)) * bulletSpeed + currentYSpeed;
}
