#include "SpaceObject.h"
#include <cmath>


SpaceObject::SpaceObject(std::string namey, double alt)
{
    this->altitude = alt;
    double EARTHR = 6371000.00; // meters
    double G = 6.6743e-11; // m^3 kg^-1 s^-2
    double EARTHM = 5.724e24; // kg
    double altitudem = 1000.0 * alt;
    this->eciposition = { EARTHR + altitudem, 0 };
    this->name = namey;
    double vz = sqrt((G * EARTHM) / (EARTHR + altitudem));
    this->orbVel = vz;
    this->period = (2 * 3.14 * (EARTHR+altitudem) / orbVel);
    this->thetaPerSec = 360.0 / this->period;
    //this->velocity = { 0, 0, -vz };
    //this->acceleration = { 0, 0, 0 };
}

