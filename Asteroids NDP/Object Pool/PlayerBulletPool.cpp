//
//  PlayerBulletPool.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 05/06/25.
//

#include "PlayerBulletPool.hpp"

PlayerBulletPool::PlayerBulletPool(const int POOL_SIZE): POOL_SIZE(POOL_SIZE){
    for (int i = 0; i < POOL_SIZE; i++) {
        playerBullets.push_back(std::make_unique<PlayerBullet>(0,0,30, 30, "playerBullet.png",4,0,0,0));
    }
}

std::shared_ptr<PlayerBullet> PlayerBulletPool::SpawnFromPool(int x, int y, float xSpeed, float ySpeed, float newRotation){
    for (std::shared_ptr<PlayerBullet> bullet : playerBullets){
        if(!bullet->inUse){
            bullet->init(x, y, xSpeed, ySpeed, newRotation);
            return bullet;
        }
    }
    std::cout << "bullet pool limite maximo" << std::endl;
    return nullptr;
}
