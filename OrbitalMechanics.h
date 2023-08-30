#pragma once
#ifndef ORBITAL_MECHANICS_H
#define ORBITAL_MECHANICS_H
#include <vector>

class SpaceObject;

class OrbitalMechanics
{
public:

    int numSpaceCraft;
    const double EARTHR = 6371000.00;
    const double G = 6.6743e-11;
    const double EARTHM = 5.724e24;

    std::vector <SpaceObject*> satelliteList;





    void updatePositionVelocity(SpaceObject* spaceboi, double timestep);

    int computeAcceleration(SpaceObject* spaceboi);

    void addSatellite(SpaceObject* spacey);


};


#endif // ORBITAL_MECHANICS_H