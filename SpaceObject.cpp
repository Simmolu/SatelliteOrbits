#include "SpaceObject.h"
#include <cmath>


SpaceObject::SpaceObject(std::string name, double alt)
{
    this->altitude = alt;
    double EARTHR = 6371000.00; // meters
    double G = 6.6743e-11; // m^3 kg^-1 s^-2
    double EARTHM = 5.724e24; // kg
    double altitudem = 1000 * alt;
    this->eciposition = { EARTHR + altitudem, 0, 0 };
    this->name = name;
    double vz = sqrt((G * EARTHM) / (EARTHR + altitudem));
    this->velocity = { 0, 0, -vz };
}

