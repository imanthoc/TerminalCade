#include "obstacle.h"

Obstacle::Obstacle(std::string sprite_, std::string cls_, int x_, int y_)
{
    sprite = sprite_;
    cls = cls_;

    x = x_;
    y = y_;

    old_x = x;
    old_y = y; 
}

void Obstacle::move(DR direction, int speed)
{
    int speed_x = 0;
    int speed_y = 0;

    old_x = x;
    old_y = y;
    
    switch (direction)
    {
    case DR::UP:    speed_y = -speed; break;
    case DR::DOWN:  speed_y = speed;  break;
    case DR::LEFT:  speed_x = -speed; break;
    case DR::RIGHT: speed_x = speed;  break;
    }

    x += speed_x;
    y += speed_y;
}
