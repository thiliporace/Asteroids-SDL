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
    
    const float playerShipMoveSpeed = 800;
    const float playerShipRotateSpeed = 440;
public:
    void update(float deltaTime) override;
    
    void setIsMoving(bool b);
    
    void setIsRotating(bool isRotatingLeft, bool isRotatingRight);
    
    bool canBeHit();
    
    void calculateRotation(float deltaTime);
    
    void calculateSpeed(float deltaTime);
    
    PlayerGameObject(int x, int y, int w, int h, const std::string& assetName);
};

#endif /* PlayerGO_hpp */
