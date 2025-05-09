//
//  GameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "GameObject.hpp"
#include "SdlManager.hpp"

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

GameObject::GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const char* assetName,
                       float xSpeed, float ySpeed, float rotation) : currentXSpeed(xSpeed), currentYSpeed(ySpeed), isAlive(true), rotation(rotation) {
    SdlManager* sdlManager = SdlManager::getInstance();
    
    spriteTexture = nullptr;
    
    sprite = IMG_Load(assetName);
    
    if (!sprite){
        cout << "Error Surface: " << SDL_GetError() << endl;
        return;
    }
    
    spriteTexture = SDL_CreateTextureFromSurface(sdlManager->getRenderer(), sprite);
    
    if (!spriteTexture){
        cout << "Error Texture: " << SDL_GetError() << endl;
        return;
    }
    
    SDL_FreeSurface(sprite);
    
    SDL_QueryTexture(spriteTexture, NULL, NULL, &position.w, &position.h); //Conecta textura com posicao
    
    position.x = initialXPos;
    position.y = initialYPos;
    
    width = objectWidth;
    height = objectHeight;
    
    position.w = width;
    position.h = height;
}

GameObject::~GameObject(){
    if (spriteTexture) {
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = nullptr;
    }
}

SDL_Texture* GameObject::getTexture(){
    return spriteTexture;
}

bool GameObject::getIsAlive(){
    return isAlive;
}

double GameObject::degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}
