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
#include "AsteroidGameObject.hpp"

class PlayerGameObject: public GameObject{
private:
    bool isMoving, isRotatingLeft, isRotatingRight;
    
    const float playerShipMoveSpeed = 0.3;
    const float playerShipRotateSpeed = 5.0;
public:
    void update() override;
    void setIsMoving(bool b);
    
    void setIsRotating(bool isRotatingLeft, bool isRotatingRight);
    
    void calculateRotation();
    
    void calculateSpeed();
    
    PlayerGameObject(int x, int y, int w, int h, const std::string& assetName);
};

#endif /* PlayerGO_hpp */
