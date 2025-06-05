//
//  AsteroidSpawner.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#ifndef AsteroidSpawner_hpp
#define AsteroidSpawner_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "AsteroidGameObject.hpp"
#include "AsteroidPool.hpp"

class AsteroidSpawner{
private:
    std::shared_ptr<PlayerGameObject> playerGO;
    AsteroidPool& asteroidPool;
    
public:
    AsteroidSpawner(std::shared_ptr<PlayerGameObject> playerRect, AsteroidPool& asteroidPool);
    
    std::shared_ptr<AsteroidGameObject> SpawnAsteroid(std::optional<AsteroidType> initialAsteroidType = std::nullopt, std::optional<int> initialXPosition = std::nullopt, std::optional<int> initialYPosition = std::nullopt);
};

#endif /* AsteroidSpawner_hpp */
