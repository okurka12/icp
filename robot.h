#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    double x;  // x-coordinate
    double y;  // y-coordinate
    unsigned int r;  // angle in degrees

    Robot(unsigned int initial_x, unsigned int initial_y, unsigned int initial_r);

    /* one-tick update of a position */
    void update();
};

#endif // ROBOT_H
