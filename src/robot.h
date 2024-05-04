/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file
 * @brief Robot class representing the robot
*/

#include <vector>
#include "obstacle.h"

#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    double x;  // x-coordinate
    double y;  // y-coordinate
    double r;  // angle in degrees
    bool is_controlled;

    Robot(double initial_x, double initial_y, double initial_r);

    /* updates the position no matter the obstacles */
    void updatePosition();

    /* one-tick update of a position or angle */
    void update(std::vector<Robot> &others, std::vector<Obstacle> &obstacles);
    void updateAutonomous(std::vector<Robot> &others, std::vector<Obstacle> &obstacles);
    void updateControlled(std::vector<Robot> &others, std::vector<Obstacle> &obstacles);

    bool collidesWith(Robot &other);
    bool collidesWithWindow();
    bool collidesWithAnyone(std::vector<Robot> &others);
    bool collidesWithAnyObstacle(std::vector<Obstacle> &obstacles);
    bool collidesWithObstacle(Obstacle &obs);

    /* set randomized rotation direction for autonomous robot */
    void updateRotDir();

    /* stuff for controlled_robot below */

    /* mark the robot as controlled (default is autonomous) */
    void setControlled();

    /* start/stop moving the controlled robot */
    void moveForward(bool do_move);

    /**
     * start/stop rotating the controlled robot
     * @param dir -1 CW, 0 don't, 1 CCW
    */
    void rotate(int dir);

    /**
     * rotate the robot by 180 degrees, also change the rotation direction
    */
   void flip();

   bool isControlled();

    /* is the controlled robot moving? */
    bool moving_forward;

    /* rotation direction of the controlled robot, set by `rotate` */
    int cr_rotdir;

    /* rotation direction, 1 (CCW) or -1 (CW) */
    int rotdir;

    /* is the controlled robot flipped? */
    bool flipped;

};

#endif // ROBOT_H
