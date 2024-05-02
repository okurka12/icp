#include <cmath>  // sin, cos, sqrt
#include <iostream>
#include <algorithm>  // min, max
#include "robot.h"
#include "icp24.h"

Robot::Robot(unsigned int initial_x, unsigned int initial_y, unsigned int initial_r)
    : x(initial_x), y(initial_y), r(initial_r)
{}


void Robot::update() {

    double oldx = x;
    double oldy = y;

    /* update position based on speed per second and TPS */
    double h = (double)ICP_ROBSPEED / (double)ICP_TPS;  // hypotenuse
    double rads = ICPdeg2rad(r);
    double xd = h * cos(rads);
    double yd = h * sin(rads);
    // std::cout << (void *)this <<": xd: " << xd << ", yd: " << yd << ", rads:" << rads << std::endl;
    double newx = x + xd;
    double newy = y - yd;

    /* check collision and eventually revert the position update */
    x = newx;
    y = newy;
    /* todo: check collision */
    if (collidesWithWall()) {
        x = oldx;
        y = oldy;
        r += (double)ICP_ROBROT / ICP_TPS;
    }
}

bool Robot::collidesWith(Robot &other) {
    double xd = std::max(x, other.x) - std::min(x, other.x);
    double yd = std::max(x, other.y) - std::min(x, other.y);
    double distance = sqrt(xd * xd + yd * yd);
    return distance < 2 * ICP_ROBSIZE + ICP_MARGIN;
}

bool Robot::collidesWithWall() {
    if (x < ICP_ROBSIZE + ICP_MARGIN || y < ICP_ROBSIZE + ICP_MARGIN) {
        return true;
    }
    if (
        x > ICP_WIDTH - ICP_ROBSIZE - ICP_MARGIN
        ||
        y > ICP_HEIGHT - ICP_ROBSIZE - ICP_MARGIN)
    {
        return true;
    }
    return false;
}
