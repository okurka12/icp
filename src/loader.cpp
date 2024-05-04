/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file
 * @brief implementation of class loader
*/

#include <iostream>
#include <fstream>
#include <string>  // getline
#include "loader.h"

Loader::Loader()
{

}

std::vector<Obstacle> Loader::load(const char *filename) {
    std::vector<Obstacle> output;
    std::fstream f;
    f.open(filename, std::ios::in);

    if (!f.is_open()) {
        std::cerr << "Can't open file for load:" << filename << std::endl;
        return output;
    }

    std::string line;
    unsigned int x;
    unsigned int y;

    while (std::getline(f, line)) {
        int rc = sscanf(line.c_str(), "%u %u", &x, &y);
        if (rc != 2) {
            continue;
        }
        output.push_back(Obstacle(x, y));
    }

    return output;
}

void Loader::save(const char *filename, std::vector<Obstacle> &obstacles) {
    std::fstream f;
    f.open(filename, std::ios::out);
    if (!f.is_open()) {
        std::cerr << "Can't to open file for save: " << filename << std::endl;
        return;
    }
    for (Obstacle &o : obstacles) {
        f << o.x << " " << o.y << std::endl;
    }

}
