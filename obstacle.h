#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<string>

#include "drawable.h"

enum class DR
{
    UP, DOWN, LEFT, RIGHT
};

class Obstacle: public Drawable_Obj
{
private:
    int x, y;
    int old_x, old_y;
    std::string sprite;
    std::string cls;
public:
    // still not sure if strings should be passed by ref or by value
    Obstacle(std::string s, std::string cls, int x, int y);
        
    std::string_view get_sprite() const override { return sprite; };
    std::string_view get_cls()    const override { return cls; }
    int get_x() const override { return x; }
    int get_y() const override { return y; }
    int get_old_x() const override { return old_x; }
    int get_old_y() const override { return old_y; }

    void move(DR direction, int speed = 1);
};

#endif
