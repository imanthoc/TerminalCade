#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string_view>

class Drawable_Obj
{
public:
    virtual std::string_view get_sprite() const = 0;
    virtual std::string_view get_cls() const = 0;

    virtual int get_x() const = 0;
    virtual int get_y() const = 0;
    virtual int get_old_x() const = 0;
    virtual int get_old_y() const = 0;
};

#endif
