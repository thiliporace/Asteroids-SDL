//
//  GameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <list>
#include <SDL.h>

class GameObject {
private:
    SDL_Surface* sprite;
    
    SDL_Texture* spriteTexture;
    
    float width,height;

public:
    SDL_Rect position;
    
    GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, char* assetName);
    
    SDL_Texture* getTexture();
    
    ~GameObject();
};

#endif /* GameObject_hpp */
