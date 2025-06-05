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
    
    float rotateAmount;
    float invincibilityTimer = 0.1f;
    
    bool isInvincible = true;
    
    std::shared_ptr<PlayerGameObject> playerGO;
    
    CollisionDetection collisionDetection;
public:
    AsteroidGameObject(AsteroidType asteroidType, int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount, float lifeTime, std::shared_ptr<PlayerGameObject> playerGO);
    
    void init(AsteroidType asteroidType, int x, int y, float xSpeed, float ySpeed, float newRotation, std::shared_ptr<PlayerGameObject> playerGO);
    
    void update(float deltaTime) override;
    
    AsteroidType getAsteroidType();
    
    bool canBeHit();
};

#endif /* AsteroidGameObject_hpp */
