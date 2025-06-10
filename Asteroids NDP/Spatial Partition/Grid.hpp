//
//  Grid.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <iostream>
#include <stdio.h>
#include <list>

#include "CollisionDetection.hpp"
#include "AsteroidSpawner.hpp"
#include "PointsManager.h"
#include "GameObject.hpp"

class Grid {
public:
    static const int CELL_SIZE = 40;
    static const int NUM_CELLS = 20;
    
    void add(std::shared_ptr<GameObject> unit);
    
    void handleCollision();
    
    void handleCell(int x, int y);
    
    void handleAttack(std::shared_ptr<GameObject> unit, std::shared_ptr<GameObject> other);
    
    void handleUnit(std::shared_ptr<GameObject> unit, std::shared_ptr<GameObject> other);
    
    void checkCellChange(std::shared_ptr<GameObject> unit, float x, float y);
    
    Grid(std::list<std::shared_ptr<GameObject>>& gameObjectsInScene, PointsManager& pointsManager);
   
protected:
    std::shared_ptr<GameObject> cells[NUM_CELLS][NUM_CELLS];
    
    std::list<std::shared_ptr<GameObject>>& gameObjectsInScene;
    
//    AsteroidSpawner& asteroidSpawner;
    
    PointsManager& pointsManager;
    
    CollisionDetection collisionDetection;
};

#endif /* Grid_hpp */
