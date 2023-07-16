#include "OrbitalMechanics.h"
#include "SpaceObject.h"
#include <iostream>
#include <cmath>

std::vector<double> OrbitalMechanics::computeAcceleration(SpaceObject* spaceboi)
{

    SpaceObject spacey = *spaceboi;

    std::vector<double> pos = spacey.eciposition;
    double x = pos[0];
    double y = pos[1];
    double z = pos[2];
    double theta;

    double gravforce = G * ((spacey.mass * EARTHM) / (pow(spacey.altitude * 1000.0, 2.0)));
    double accelconst = gravforce / spacey.mass;

    if (x >= 0 && z <= 0)
    {
        std::cout << "Quadrant I\n";

        double ratio = abs(z) / x;
        std::cout << "Ratio: " << ratio << "\n";

        theta = atan(ratio) * (180.0 / 3.14);
        if (theta > 90.0)
        {
            theta = 90.0;
        }

        std::cout << "delta theta: " << theta << " degrees\n";

        double modacc = (1.0 / 90.0) * theta;
        std::cout << modacc << "\n";

        double ax = (fabs(1.0 - modacc)) * -1.0;
        std::cout << ax << " ax\n";

        double az = (fabs(0.0 + modacc)) * -1.0;
        std::cout << az << " az\n";

        double finax = ax * accelconst;
        double finaz = az * accelconst;
        std::vector<double> retrn = { finax, 0, finaz };

        return retrn;
    }
    else
    {
        std::cout << "Fail\n";
        return { 0 };
    }
}

void OrbitalMechanics::updatePositionVelocity(SpaceObject* space, double timestep)
{
    /* We need to first update the velocity vector at each time step, as the velocity vector of a satellite constantly changes based on the
    gravitational force component applied. It will ALAWYS face towards the center of the earth so based on the satellites position the
    acceleration vector looks different, which effects the velocity vector.
    */
    SpaceObject spaceboi = *space;
    std::vector<double> acceleration = computeAcceleration(space);

    std::vector<double> vel = spaceboi.velocity;

    // compute velocity

    for (unsigned i = 0; i < 3; i++)
    {
        vel[i] = vel[i] + (acceleration[i] * timestep);
    }

    std::vector<double> pos = spaceboi.eciposition;

    for (unsigned i = 0; i < 3; i++)
    {
        pos[i] = pos[i] + (vel[i] * timestep);
    }

    space->eciposition = pos;
    space->velocity = vel;
}
