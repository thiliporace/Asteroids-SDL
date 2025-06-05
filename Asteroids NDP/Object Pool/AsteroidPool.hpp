//
//  AsteroidPool.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 05/06/25.
//

#ifndef AsteroidPool_hpp
#define AsteroidPool_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <list>

#include "AsteroidGameObject.hpp"

class AsteroidPool {
public:
    const int SMALL_ASTEROID_POOL_SIZE;
    const int MEDIUM_ASTEROID_POOL_SIZE;
    
    std::list<std::shared_ptr<AsteroidGameObject>> smallAsteroids;
    std::list<std::shared_ptr<AsteroidGameObject>> mediumAsteroids;
    
    std::vector<std::string> smallMeteorAssets = {"meteor2.png","meteor4.png","meteor6.png","meteor8.png"};
    std::vector<std::string> mediumMeteorAssets = {"meteor1.png","meteor3.png","meteor5.png","meteor7.png"};
    
    AsteroidPool(const int SMALL_ASTEROID_POOL_SIZE, const int MEDIUM_ASTEROID_POOL_SIZE);
    
    std::shared_ptr<AsteroidGameObject> SpawnFromPool(AsteroidType asteroidType, int x, int y, float xSpeed, float ySpeed, float newRotation, std::shared_ptr<PlayerGameObject> playerGO);
};

#endif /* AsteroidPool_hpp */
