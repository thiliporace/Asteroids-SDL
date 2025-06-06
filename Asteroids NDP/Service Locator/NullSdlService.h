//
//  NullSdlService.h
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#ifndef NullSdlService_h
#define NullSdlService_h

#include "SdlServiceInterface.h"

class NullSdlService: public SdlServiceInterface
{
public:
    void const initializeSDL() override { /* Faz nada */ }
    void const initializeSDLWindow() override { /* Faz nada */ }
    void const initializeSDLRenderer() override { /* Faz nada */ }
    
    SDL_Renderer* getRenderer() override { return nullptr; }
    SDL_Window* getWindow() override { return nullptr; }
};

#endif /* NullSdlService_h */
