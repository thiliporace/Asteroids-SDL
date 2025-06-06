//
//  SdlServiceLocator.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#ifndef SdlServiceLocator_hpp
#define SdlServiceLocator_hpp

#include <stdio.h>
#include <iostream>

#include "SdlServiceInterface.h"
#include "NullSdlService.h"

class SdlServiceLocator {
private:
    static std::shared_ptr<SdlServiceInterface> service;
public:
    static std::shared_ptr<SdlServiceInterface> getSdlService();
    
    static void provide(std::shared_ptr<SdlServiceInterface> sdlService);
};

#endif /* SdlServiceLocator_hpp */
