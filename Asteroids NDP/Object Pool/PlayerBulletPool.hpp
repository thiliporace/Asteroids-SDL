//
//  PlayerBulletPool.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 05/06/25.
//

#ifndef PlayerBulletPool_hpp
#define PlayerBulletPool_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <list>

#include "PlayerBullet.hpp"

class PlayerBulletPool {
public:
    const int POOL_SIZE;
    
    std::list<std::shared_ptr<PlayerBullet>> playerBullets;
    
    PlayerBulletPool(const int POOL_SIZE);
    
    std::shared_ptr<PlayerBullet> SpawnFromPool(int x, int y, float xSpeed, float ySpeed, float newRotation);
};

#endif /* PlayerBulletPool_hpp */
