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
    float lifetime, timeAlive;
    
    float bulletSpeed = 260;
public:
    void update(float deltaTime) override;
    
    PlayerBullet(int x, int y, int w, int h, const std::string& assetName, float bulletLifetime, float xSpeed,
                 float ySpeed, float rotation, std::shared_ptr<Grid> grid);
    
    static std::shared_ptr<PlayerBullet> Create(int x, int y, int w, int h, const std::string& assetName, float bulletLifetime, float xSpeed, float ySpeed, float rotation, std::shared_ptr<Grid> grid);
};

#endif /* PlayerBullet_hpp */
