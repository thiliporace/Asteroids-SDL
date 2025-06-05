//
//  AsteroidPool.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 05/06/25.
//

#include "AsteroidPool.hpp"

AsteroidPool::AsteroidPool(const int SMALL_ASTEROID_POOL_SIZE, const int MEDIUM_ASTEROID_POOL_SIZE): SMALL_ASTEROID_POOL_SIZE(SMALL_ASTEROID_POOL_SIZE), MEDIUM_ASTEROID_POOL_SIZE(MEDIUM_ASTEROID_POOL_SIZE) {
    
    for(int i = 0; i < SMALL_ASTEROID_POOL_SIZE; i++){
        smallAsteroids.push_back(std::make_shared<AsteroidGameObject>(SMALL,0,0,60,60,smallMeteorAssets[rand() % smallMeteorAssets.size()],0,0,0, 12, nullptr));
    }
    
    for(int i = 0; i < MEDIUM_ASTEROID_POOL_SIZE; i++){
        mediumAsteroids.push_back(std::make_shared<AsteroidGameObject>(MEDIUM,0,0,60,60,mediumMeteorAssets[rand() % mediumMeteorAssets.size()],0,0,0, 12, nullptr));
    }
    
}

std::shared_ptr<AsteroidGameObject> AsteroidPool::SpawnFromPool(AsteroidType asteroidType, int x, int y, float xSpeed, float ySpeed, float newRotation, std::shared_ptr<PlayerGameObject> playerGO){
    switch (asteroidType) {
        case SMALL:
            for(std::shared_ptr<AsteroidGameObject> asteroid : smallAsteroids){
                if (!asteroid->inUse){
                    asteroid->init(asteroidType, x, y, xSpeed, ySpeed, newRotation, playerGO);
                    return asteroid;
                }
            }
            break;
        case MEDIUM:
            for(std::shared_ptr<AsteroidGameObject> asteroid : mediumAsteroids){
                if (!asteroid->inUse){
                    asteroid->init(asteroidType, x, y, xSpeed, ySpeed, newRotation, playerGO);
                    return asteroid;
                }
            }
        default:
            break;
    }
    std::cout << "asteroid pool limite maximo" << std::endl;
    return nullptr;
}
