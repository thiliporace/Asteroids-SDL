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

GameObject::GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, char* assetName){
    SdlManager* sdlManager = SdlManager::getInstance();
    
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
    SDL_DestroyTexture(spriteTexture);
}

SDL_Texture* GameObject::getTexture(){
    return spriteTexture;
}
