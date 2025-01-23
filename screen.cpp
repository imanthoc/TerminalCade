
#include "screen.h"

TScreen::TScreen()
{
    initscr();

    game_window = newwin(game_window_h, game_window_w, 0, 0);
    hud_window  = newwin(hud_window_h, hud_window_w, game_window_h, 0);
    refresh();
    
    curs_set(0);    
    noecho();


    box(game_window, 0, 0);
    box(hud_window, 0, 0);

    wrefresh(game_window);
    wrefresh(hud_window);
}

TScreen::~TScreen()
{
    delwin(game_window);
    delwin(hud_window);
    endwin();
}

void TScreen::draw_game_scr(std::string str, int x, int y)
{
    mvwprintw(game_window, y, x, str.c_str());
    box(game_window, 0, 0);
    wrefresh(game_window);
}

void TScreen::draw_hud(std::string str, int x, int y)
{
    mvwprintw(hud_window, y, x, str.c_str());
    box(hud_window, 0, 0);
    wrefresh(hud_window);
}

void TScreen::draw_sprite_game_scr(std::string_view str, int w, int h)
{
    int original_w = w;
    for (auto& c: str)
    {
        if (c == '\n')
        {
            h++;
            w = original_w;
        }
        else 
        {
            mvwaddch(game_window, h, w, c);
            w++;
        }
    }

    box(game_window, 0, 0);
    wrefresh(game_window);
}

void TScreen::draw_object(const Drawable_Obj& object)
{
    draw_sprite_game_scr(object.get_cls(), object.get_old_x(), object.get_old_y() - 1);
    draw_sprite_game_scr(object.get_sprite(), object.get_x(), object.get_y());
}
