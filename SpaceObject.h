#pragma once
#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H
#include <string>
#include <vector>

class SpaceObject
{
public:
    std::string name;
    std::vector <double> eciposition;
    //std::vector <double> velocity;
    //std::vector <double> acceleration;
    double orbVel;
    double mass = 2500;
    double altitude;
    double period;
    double thetaPerSec;
    double currentAngle;

    SpaceObject(std::string name, double alt);
};

#endif //SPACE_OBJECT_H