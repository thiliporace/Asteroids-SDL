//
//  AsteroidGameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#ifndef AsteroidGameObject_hpp
#define AsteroidGameObject_hpp

#include <stdio.h>

#include "PlayerGameObject.hpp"
#include "CollisionDetection.hpp"
#include "AsteroidType.h"

class AsteroidGameObject: public GameObject{
private:
    AsteroidType asteroidType;
    
    float rotateAmount,lifeTime,timeAlive;
    float invincibilityTimer = 0.2f;
    
    bool isInvincible = true;
    
    PlayerGameObject& playerGO;
    SDL_FRect& playerRect;
    
    CollisionDetection collisionDetection;
public:
    AsteroidGameObject(AsteroidType asteroidType, int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount,float lifeTime, PlayerGameObject& playerGO);
    
    void update() override;
    
    AsteroidType getAsteroidType();
    
    bool canBeHit();
};

#endif /* AsteroidGameObject_hpp */
