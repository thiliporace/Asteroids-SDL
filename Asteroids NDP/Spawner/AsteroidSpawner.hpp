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

class AsteroidSpawner{
private:
    std::vector<std::string> smallMeteorAssets = {"meteor2.png","meteor4.png","meteor6.png","meteor8.png"};
    
    std::vector<std::string> mediumMeteorAssets = {"meteor1.png","meteor3.png","meteor5.png","meteor7.png"};
    
    PlayerGameObject& playerGO;
public:
    AsteroidSpawner(PlayerGameObject& playerRect);
    
    std::unique_ptr<AsteroidGameObject> SpawnAsteroid(std::optional<AsteroidType> initialAsteroidType = std::nullopt, std::optional<int> initialXPosition = std::nullopt, std::optional<int> initialYPosition = std::nullopt);
};

#endif /* AsteroidSpawner_hpp */
