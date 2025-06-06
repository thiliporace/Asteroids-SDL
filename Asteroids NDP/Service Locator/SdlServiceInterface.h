//
//  SdlServiceInterface.h
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#ifndef SdlServiceInterface_h
#define SdlServiceInterface_h

#include <SDL.h>

class SdlServiceInterface {
public:
    virtual ~SdlServiceInterface() {}
    
    const virtual void initializeSDL() = 0;
    const virtual void initializeSDLWindow() = 0;
    const virtual void initializeSDLRenderer() = 0;
    
    virtual SDL_Renderer* getRenderer() = 0;
    virtual SDL_Window* getWindow() = 0;
};


#endif /* SdlServiceInterface_h */
