//
//  GameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <string.h>
#include <stdio.h>
#include <list>
#include <SDL.h>

class GameObject {
private:
    SDL_Surface* sprite;
    
    SDL_Texture* spriteTexture;
    
    float width,height,timeAlive;

public:
    SDL_FRect position;
    
    double rotation;
    
    float currentXSpeed, currentYSpeed, lifeTime;
    
    bool inUse;
    
    GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const std::string& assetName,
               float xSpeed = 0, float ySpeed = 0, float rotation = 0, float lifeTime = 0.1);
    
    GameObject();
    
    virtual void update(float deltaTime);
    
    double degreesToRadians(double degrees);
    
    SDL_Texture* getTexture();
    
    virtual ~GameObject();
};

#endif /* GameObject_hpp */
