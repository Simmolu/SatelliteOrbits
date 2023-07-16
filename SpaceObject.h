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
    std::vector <double> velocity;
    double mass = 2500;
    double altitude;

    SpaceObject(std::string name, double alt);
};

#endif //SPACE_OBJECT_H