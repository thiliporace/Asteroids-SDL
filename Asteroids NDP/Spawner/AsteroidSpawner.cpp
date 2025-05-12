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

std::unique_ptr<AsteroidGameObject> AsteroidSpawner::SpawnAsteroid(){
    int assetIndex = rand() % meteorAssets.size();
    std::string randomName = meteorAssets[assetIndex];
    
    int randomSpawnPosition = rand() % 3; // 0, 1 e 2
    int xPosition,yPosition;
    
    switch (randomSpawnPosition){
        case 0:
            xPosition = -60 + (rand() % 60);
            break;
        case 1:
            xPosition = rand() % 800;
            break;
        case 2:
            xPosition = 800 + (rand() % 120);
            break;
        default:
            std::cout << "Não deveria cair aqui" << std::endl;
            break;
    }
    
    float xSpeed, ySpeed;
    
    if (xPosition <= -20 || xPosition >= 800){
        yPosition = rand() % 600;
    }
    else{
        yPosition = (rand() % 2) == 0 ? -20 + rand() % 20 : 600 + rand() % 20;
    }
    
    if (xPosition <= 400){
        xSpeed = randFloat(0.7f, 1.2f);
    }
    else{
        xSpeed = randFloat(-1.2f, -0.7f);
    }
    
    if (yPosition <= 300){
        
        ySpeed = randFloat(-1.2f, -0.7f);
    }
    else{
        ySpeed = randFloat(0.7f, 1.2f);
    }
    
    float rotateAmount = (rand() % 2) == 0 ? randFloat(-1.0f, -0.4f) : randFloat(0.4f, 1.0f);
    
    return std::make_unique<AsteroidGameObject>(xPosition, yPosition, 60, 60, randomName, xSpeed, ySpeed, rotateAmount, 12);
}
