#ifndef OBSTACLE_GENERATOR_H
#define OBSTACLE_GENERATOR_H

#include <string>
#include "obstacle.h"

class Obstacle_Generator
{
private:
    std::string asteroid;
    std::string asteroid_cls;
    int counter;
public:
    Obstacle_Generator();

    Obstacle get_next_obstacle();
};

#endif
