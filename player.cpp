#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "player.h"

Player::Player(int x_, int y_)
{
    speed = 0;
    hp    = 100;
    x = x_;
    y = y_;
    
    sprite = "    ^\n"
             "   | |\n"
             "  ||0||\n"
             " /  .  \\\n"
             "|--| |--|\n"
             "  /|||\\\n"; 
    
    cls =   "            \n"
            "            \n"
            "            \n"
            "            \n"
            "            \n"
            "            \n"
            "            \n";
}

// generously copied from stackoverflow
bool Player::is_key_pressed(int ks)
{
    Display *dpy = XOpenDisplay(":0");
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    XCloseDisplay(dpy);

    return isPressed;
}

bool Player::move(int l_lim, int r_lim)
{
    const float delta = 0.01;
    bool moved = true;
    const float speed_step = 0.2;
    const float speed_lim  = 3;
    old_x = x;    

    if ((is_key_pressed(XK_a) || is_key_pressed(XK_A))) 
    {   
        if (speed > -1) speed = -1;
        else if (speed > -speed_lim) speed -= speed_step;
    }
    else if ((is_key_pressed(XK_d) || is_key_pressed(XK_D)))
    {
        // player does not move when speed < 1, so set speed to 1
        // to make the player move instantly
        if (speed < 1) speed = 1;
        else if (speed < speed_lim) speed += speed_step;
    }
    else 
    {
        if (speed > 0 && speed > delta) speed -= speed_step;
        else if (speed < 0 && speed < -delta) speed += speed_step;
        else moved = false;
    }

    x += static_cast<int>(speed);

    if (x < l_lim)
    {
        x = l_lim;
        moved = false;
        speed = 0;
    }
    if (x > r_lim)
    {
        x = r_lim;
        moved = false;
        speed = 0;
    }

    return moved;
}
