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
    bool isMoving;
    
    const float playerShipMoveSpeed = 1.5;
public:
    void update() override;
    void setIsMoving(bool b);
    
    void calculateMovementDirection();
    
    PlayerGameObject(int x, int y, int w, int h, const std::string& assetName);
};

#endif /* PlayerGO_hpp */
