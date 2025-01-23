#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "drawable.h"

class Player : public Drawable_Obj
{
private:
    int hp;
    int old_x;
    int x, y;
    std::string sprite;
    std::string cls;
    float speed;
private:
    bool is_key_pressed(int k);
public:
    Player(int x, int y);

    void dec_hp() { hp -= 10; }
    int  get_hp() const { return hp; }

    std::string_view get_sprite() const override { return sprite; };
    std::string_view get_cls() const override { return cls; }

    void reset_hp() { hp = 100; }
    int get_x() const override { return x; }
    int get_y() const override { return y; }
    int get_old_x() const override { return old_x; }    
    int get_old_y() const override { return y; }

    bool move(int l_lim, int r_lim);
};

#endif
