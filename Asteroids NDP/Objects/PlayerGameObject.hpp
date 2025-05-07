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
public:
    bool isMoving;
    
    using GameObject::GameObject; //Herda o Construtor do GameObject pai
};

#endif /* PlayerGO_hpp */
