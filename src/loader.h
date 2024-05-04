/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

#include <vector>
#include "obstacle.h"

#ifndef LOADER_H
#define LOADER_H


class Loader
{
public:
    Loader();
    std::vector<Obstacle> load(const char *filename);
    void save(const char *filename, std::vector<Obstacle> &obstacles);
};

#endif // LOADER_H
