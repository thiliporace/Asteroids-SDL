//
//  CollisionDetection.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 13/05/25.
//

#include "CollisionDetection.hpp"

bool CollisionDetection::checkCollision(SDL_FRect rectA, SDL_FRect rectB){
    if ((rectA.x + rectA.w) <= rectB.x || rectA.x >= (rectB.x + rectB.w)) {
        return false;
    }
    
    if ((rectA.y + rectA.h) <= rectB.y || rectA.y >= (rectB.y + rectB.h)) {
        return false;
    }
    
    return true;
}
