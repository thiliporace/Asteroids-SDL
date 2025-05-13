//
//  AsteroidSpawner.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#include "AsteroidSpawner.hpp"

float randFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

AsteroidSpawner::AsteroidSpawner(GameObject& playerGO): playerGO(playerGO) {}

std::unique_ptr<AsteroidGameObject> AsteroidSpawner::SpawnAsteroid(std::optional<AsteroidType> initialAsteroidType, std::optional<int> initialXPosition, std::optional<int> initialYPosition){
    
    AsteroidType asteroidType = initialAsteroidType.value_or(rand() % 2 == 0 ? MEDIUM : SMALL);
    
    std::vector<std::string> assets = (asteroidType == SMALL) ? smallMeteorAssets : mediumMeteorAssets;
    std::string randomName = assets[rand() % assets.size()];
    
    int randomSpawnPosition = rand() % 3; // 0, 1 e 2
    
    int xPosition,yPosition;
    
    float xSpeed, ySpeed;
    
    if (initialXPosition.has_value()) {
        xPosition = (initialXPosition.value() -30) + rand() % 60;
    }
    else {
        switch (randomSpawnPosition){
            case 0: xPosition = -60 + (rand() % 60); break;
            case 1: xPosition = rand() % 800; break;
            case 2: xPosition = 800 + (rand() % 120); break;
            default: xPosition = 0; std::cout << "Não é pra cair aqui" << std::endl; break;
        }
    }
    
    if (initialYPosition.has_value()) {
        yPosition = (initialYPosition.value() -30) + rand() % 60;
    } else {
        if (xPosition <= -20 || xPosition >= 800){
            yPosition = rand() % 600;
        } else {
            yPosition = (rand() % 2 == 0) ? -20 + rand() % 20 : 600 + rand() % 20;
        }
    }
    
    xSpeed = randFloat(-1.2f, 1.2f);

    ySpeed = randFloat(-1.2f, -0.7f);
    
    float rotateAmount = (rand() % 2) == 0 ? randFloat(-1.0f, -0.4f) : randFloat(0.4f, 1.0f);
    
    return std::make_unique<AsteroidGameObject>(asteroidType, xPosition, yPosition, 60, 60, randomName, xSpeed, ySpeed, rotateAmount, 12, playerGO);
}
