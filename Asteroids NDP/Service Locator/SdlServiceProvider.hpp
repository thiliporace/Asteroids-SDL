//
//  SdlServiceProvider.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#ifndef SdlServiceProvider_hpp
#define SdlServiceProvider_hpp

#include <stdio.h>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>

#include "SdlServiceInterface.h"

class SdlServiceProvider: public SdlServiceInterface{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    void const initializeSDL() override;
    void const initializeSDLWindow() override;
    void const initializeSDLRenderer() override;
    
    SDL_Renderer* getRenderer() override;
    SDL_Window* getWindow() override;
    
    SdlServiceProvider();
    ~SdlServiceProvider();
};

#endif /* SdlServiceProvider_hpp */
