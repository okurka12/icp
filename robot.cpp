#include <cmath>
#include <iostream>
#include "robot.h"
#include "icp24.h"

Robot::Robot(unsigned int initial_x, unsigned int initial_y, unsigned int initial_r)
    : x(initial_x), y(initial_y), r(initial_r)
{}


void Robot::update() {
    /* todo: check collision */

    /* update position based on speed per second and TPS */
    double h = (double)ICP_ROBSPEED / (double)ICP_TPS;  // hypotenuse
    double rads = ((double)r / 180.0) * ICP_PI;
    double xd = h * cos(rads);
    double yd = h * sin(rads);
    std::cout << (void *)this <<": xd: " << xd << ", yd: " << yd << ", rads:" << rads << std::endl;
    x += xd;
    y -= yd;
}
