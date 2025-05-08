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
    bool isMoving;
public:
    void update() override;
    void setIsMoving(bool b);
    
    PlayerGameObject(int x, int y, int w, int h, char* assetName);
};

#endif /* PlayerGO_hpp */
