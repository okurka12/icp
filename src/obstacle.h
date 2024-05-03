/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file Obstacle class representing the obstacles
*/

#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle
{
public:
    Obstacle(unsigned int x, unsigned int y);

    /* upper left corner */
    unsigned int x;
    unsigned int y;
};

#endif // OBSTACLE_H
