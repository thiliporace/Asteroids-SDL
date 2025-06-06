//
//  SdlServiceLocator.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#include "SdlServiceLocator.hpp"

std::shared_ptr<SdlServiceInterface> SdlServiceLocator::service = std::make_shared<NullSdlService>();

std::shared_ptr<SdlServiceInterface> SdlServiceLocator::getSdlService(){
    if (service == nullptr) {
        std::cout << "serviço nulo" << std::endl;
    }
    return service;
}

void SdlServiceLocator::provide(std::shared_ptr<SdlServiceInterface> sdlService){
    if (sdlService == nullptr) {
        std::cout << "pegou servico nulo" << std::endl;
        service = std::make_shared<NullSdlService>();
    }
    else {
        std::cout << "pegou servico" << std::endl;
        service = sdlService;
    }
}
