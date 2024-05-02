#include <cmath>  // sin, cos, sqrt
#include <iostream>
#include <algorithm>  // min, max
#include <random>
#include "robot.h"
#include "icp24.h"
#include "obstacle.h"

static int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Robot::Robot(double initial_x, double initial_y, double initial_r)
    : x(initial_x), y(initial_y), r(initial_r)
{
    updateRotDir();
}

void Robot::updateRotDir() {

    /* every fourth time, the robot decides to rotate to the other side */
    rotdir = getRandomNumber(1, 4) == 1 ? 1 : -1;
}


void Robot::update(
    std::vector<Robot> &others,
    std::vector<Obstacle> &obstacles
) {

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
    if (
        collidesWithWindow() ||
        collidesWithAnyone(others) ||
        collidesWithAnyObstacle(obstacles))
    {
        x = oldx;
        y = oldy;
        r += rotdir * (double)ICP_ROBROT / ICP_TPS;
    } else {

        /* on each collision, start rotating to a random angle (CW/CCW) */
        /* note: maybe not as efficient to call this so often? (todo) */
        updateRotDir();
    }
}

bool Robot::collidesWithAnyObstacle(std::vector<Obstacle> &obstacles) {
    for (Obstacle &obs : obstacles) {
        if (collidesWithObstacle(obs)) return true;
    }
    return false;
}

bool Robot::collidesWithObstacle(Obstacle &obs) {
    double centerx = (double)obs.x * ICP_OBSIZE + (double)ICP_OBSIZE / 2;
    double centery = (double)obs.y * ICP_OBSIZE + (double)ICP_OBSIZE / 2;
    double xd = std::max(x, centerx) - std::min(x, centerx);
    double yd = std::max(y, centery) - std::min(y, centery);
    double distance = sqrt(xd * xd + yd * yd);
    if (distance < ICP_ROBSIZE + ICP_OBSIZE * sqrt(2) / 2) {
        return true;
    }
    return false;
}

bool Robot::collidesWithAnyone(std::vector<Robot> &others) {
    for (Robot &other : others) {
        bool are_same = (void *)this == (void *)(&other);
        if (!are_same && collidesWith(other)) {
            return true;
        }
    }
    return false;
}

bool Robot::collidesWith(Robot &other) {
    double xd = std::max(x, other.x) - std::min(x, other.x);
    double yd = std::max(y, other.y) - std::min(y, other.y);
    double distance = sqrt(xd * xd + yd * yd);
    return distance < 2 * ICP_ROBSIZE + ICP_MARGIN;
}

bool Robot::collidesWithWindow() {
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
