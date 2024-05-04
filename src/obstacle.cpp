/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file implementation of class Obstacle
*/

#include <iostream>
#include "obstacle.h"

Obstacle::Obstacle(unsigned int x, unsigned int y)
         :x(x), y(y)
{
    std::cout << "initializing obstacle: " << x << ", " << y << std::endl;
}
