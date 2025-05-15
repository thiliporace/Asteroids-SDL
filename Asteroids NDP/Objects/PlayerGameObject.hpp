//
//  PlayerGO.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef PlayerGameObject_hpp
#define PlayerGameObject_hpp

#include <stdio.h>

#include "GameObject.hpp"

class PlayerGameObject: public GameObject{
private:
    bool isMoving, isRotatingLeft, isRotatingRight;
    
    bool isInvincible = true;
    const float invincibilityCooldown = 0.6f;
    float invincibilityTimer = 0;
    
    const float playerShipMoveSpeed = 0.4;
    const float playerShipRotateSpeed = 11.0;
public:
    void update(float deltaTime) override;
    
    void setIsMoving(bool b);
    
    void setIsRotating(bool isRotatingLeft, bool isRotatingRight);
    
    bool canBeHit();
    
    void calculateRotation(float deltaTime);
    
    void calculateSpeed();
    
    PlayerGameObject(int x, int y, int w, int h, const std::string& assetName);
};

#endif /* PlayerGO_hpp */
