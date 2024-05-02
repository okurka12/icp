#include <vector>

#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    double x;  // x-coordinate
    double y;  // y-coordinate
    double r;  // angle in degrees

    Robot(double initial_x, double initial_y, double initial_r);

    /* one-tick update of a position */
    void update(std::vector<Robot> &others);
    bool collidesWith(Robot &other);
    bool collidesWithWindow();
    bool collidesWithAnyone(std::vector<Robot> &others);
private:

    /* rotation direction, 1 or -1 */
    int rotdir;
    void updateRotDir();
};

#endif // ROBOT_H
