#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <string_view>
#include <ncurses.h>

#include "drawable.h"

class TScreen 
{
private:
    WINDOW* game_window;
    WINDOW* hud_window;
private:
    void draw_sprite_game_scr(std::string_view str, int w, int h);
public:
    const int game_window_w = 79;
    const int game_window_h = 36;
    const int hud_window_w = 79;
    const int hud_window_h = 4;
public:
    TScreen();
    ~TScreen();

    TScreen(const TScreen& t)   = delete;
    TScreen(TScreen&& t)        = delete;
    
    void draw_game_scr(std::string str, int x = 1, int y = 1);
    void draw_hud(std::string str, int x = 1, int y = 1);
    void draw_object(const Drawable_Obj &object); // can bind to any string like object
    void clear() { wclear(game_window); wclear(hud_window); }
};

#endif
