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
    float bulletSpeed = 260;
public:
    void update(float deltaTime) override;
    
    void init(int x, int y, float xSpeed, float ySpeed, float rotation);
    
    PlayerBullet(int x, int y, int w, int h, const std::string& assetName, float bulletLifetime, float xSpeed,
                 float ySpeed, float rotation);
};

#endif /* PlayerBullet_hpp */
