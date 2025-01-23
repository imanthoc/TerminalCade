#include <cmath>
#include "obstacle_generator.h"

Obstacle_Generator::Obstacle_Generator()
{
    asteroid =  " **** \n"
                "******\n"
                "******\n"
                "******\n"
                " ****\n";
    
    asteroid_cls =  "       \n"
                    "       \n"
                    "       \n"
                    "       \n"
                    "       \n"
                    "       \n";
    counter = 0;
}

Obstacle Obstacle_Generator::get_next_obstacle()
{
    if (counter < 10)
    {
        counter++;
        return { "", "", 0, 0 };
    }
    else 
    {
        counter = 0;
        return { asteroid, asteroid_cls, rand() % 69, -10 };
    }
}
