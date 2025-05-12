//
//  AsteroidGameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 12/05/25.
//

#ifndef AsteroidGameObject_hpp
#define AsteroidGameObject_hpp

#include <stdio.h>

#include "GameObject.hpp"

class AsteroidGameObject: public GameObject{
private:
    float rotateAmount,lifeTime,timeAlive;
public:
    AsteroidGameObject(int x, int y, int w, int h, const std::string& assetName, float xSpeed, float ySpeed, float rotateAmount,float lifeTime);
    
    void update() override;
};

#endif /* AsteroidGameObject_hpp */
