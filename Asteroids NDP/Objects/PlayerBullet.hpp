//
//  PlayerBullet.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 09/05/25.
//

#ifndef PlayerBullet_hpp
#define PlayerBullet_hpp

#include <stdio.h>
#include <SDL.h>

#include "GameObject.hpp"

class PlayerBullet: public GameObject{
private:
    SDL_TimerID timer;
    float lifetime, timeAlive;
    
    float bulletSpeed = 4;
public:
    void update() override;
    
    static Uint32 deleteBulletCallback(Uint32 interval, void* param);
    
    PlayerBullet(int x, int y, int w, int h, std::string assetName, float bulletLifetime, float xSpeed,
                 float ySpeed, float rotation);
};

#endif /* PlayerBullet_hpp */
