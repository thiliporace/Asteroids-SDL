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
    std::vector<std::string> meteorAssets = {"meteor1.png","meteor2.png","meteor3.png","meteor4.png","meteor5.png","meteor6.png","meteor7.png","meteor8.png"};
public:
    std::unique_ptr<AsteroidGameObject> SpawnAsteroid();
};

#endif /* AsteroidSpawner_hpp */
