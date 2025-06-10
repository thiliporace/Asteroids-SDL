//
//  PlayerBullet.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 09/05/25.
//

#include "Grid.hpp"
#include "PlayerBullet.hpp"
#include <SDL.h>
#include <iostream>

PlayerBullet::PlayerBullet(int x, int y, int w, int h, const std::string& assetName, float bulletLifetime, float xSpeed, float ySpeed, float rotation, std::shared_ptr<Grid> grid)
    : GameObject(x, y, w, h, assetName, xSpeed, ySpeed, rotation, grid), lifetime(bulletLifetime) {}

std::shared_ptr<PlayerBullet> PlayerBullet::Create(int x, int y, int w, int h, const std::string& assetName, float bulletLifetime, float xSpeed, float ySpeed, float rotation, std::shared_ptr<Grid> grid)
{
    auto newBullet = std::make_shared<PlayerBullet>(x, y, w, h, assetName, bulletLifetime, xSpeed, ySpeed, rotation, grid);

    if (grid) {
        grid->add(newBullet);
    }

    return newBullet;
}

void PlayerBullet::update(float deltaTime){
    timeAlive += deltaTime;
    
    if (timeAlive >= lifetime){
        isAlive = false;
        return;
    }
    
    float newX = position.x + (std::cos(degreesToRadians(90 - rotation)) * bulletSpeed + (currentXSpeed/2)) * deltaTime;
    float newY = position.y - (std::sin(degreesToRadians(90 - rotation)) * bulletSpeed + (currentYSpeed/2)) * deltaTime;
    
    move(newX, newY);
}
