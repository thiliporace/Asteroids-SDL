//
//  PointsManager.h
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#ifndef PointsManager_h
#define PointsManager_h

#include "Label.hpp"

class PointsManager{
private:
    int points;
    Label& pointsLabel;
public:
    PointsManager(Label& pointsLabel): points(0), pointsLabel(pointsLabel) {}
    
    void addPoints(int pointsToAdd) {
        points += pointsToAdd;
        pointsLabel.setValue(points);
    }
};

#endif /* PointsManager_h */
