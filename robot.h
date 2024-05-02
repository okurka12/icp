#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    double x;  // x-coordinate
    double y;  // y-coordinate
    double r;  // angle in degrees

    Robot(unsigned int initial_x, unsigned int initial_y, unsigned int initial_r);

    /* one-tick update of a position */
    void update();
    bool collidesWith(Robot &other);
    bool collidesWithWindow();
};

#endif // ROBOT_H
