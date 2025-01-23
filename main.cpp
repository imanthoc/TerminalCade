#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "player.h"
#include "screen.h"
#include "obstacle_generator.h"

int score = 0;

struct Frame_Time_Pack
{
    int start;
    int end;
};

void start_frame(Frame_Time_Pack& frame_time)
{
    frame_time.start = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
}

void end_frame(Frame_Time_Pack& frame_time, int frame_target_ms)
{
    frame_time.end =  std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
    
    while (frame_time.end - frame_time.start < frame_target_ms)
    {
        frame_time.end = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
    }
}

std::string leading_zeroes(int n, int lim = 4)
{
    std::string zeroes = "";
    int digits = 0;
    
    while (n)
    {    
        n /= 10;
        digits++;
    }

    int leading_zeroes = lim - digits;
    for (int i = 0; i < leading_zeroes; ++i) zeroes.push_back('0');

    return zeroes;
}

double distance(int x1, int x2, int y1, int y2)
{
    return sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) );
}

bool check_collisions(TScreen& sc, Player& pl, std::vector<Obstacle>& obstacles)
{
    int pl_center_x = pl.get_x() + 5;
    int pl_center_y = pl.get_y() + 3;
    int pl_radius  = 4; 

    auto pos_to_delete = obstacles.end();

    for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        auto& obs = *it;

        int obs_center_x = obs.get_x() + 3;
        int obs_center_y = obs.get_y() + 3;
        int obs_radius = 3; 

        if (distance(pl_center_x, obs_center_x, pl_center_y, obs_center_y) < pl_radius + obs_radius) 
        {
            pl.dec_hp();
            
            std::string hp_str = "ENGINE STATE ";
            hp_str += std::to_string(pl.get_hp());
            hp_str += " ";
            sc.draw_hud(hp_str);

            pos_to_delete = it;
        }

        if (pl.get_hp() <= 0)
        {
            sc.draw_game_scr("GAME OVER!!!", (sc.game_window_w >> 1) - 6, sc.game_window_h >> 1);
            sc.draw_game_scr("INSERT COIN TO PLAY AGAIN", (sc.game_window_w >> 1) - 12, (sc.game_window_h >> 1) + 1);
            return true;
        }
    }
    if (pos_to_delete != obstacles.end()) 
    {
        pos_to_delete->move(DR::DOWN, 100);
        sc.draw_object(*pos_to_delete);
        obstacles.erase(pos_to_delete);
    }

    return false;
}

int main()
{
    srand(time(NULL));
    const int frame_target = 30;
    constexpr int frame_ms = static_cast<int>(
            (1.0f / static_cast<double>(frame_target)) * 1000
        );

    Frame_Time_Pack fr;

    TScreen sc{};
    Player pl{ (sc.game_window_w >> 1) - 5, sc.game_window_h - 7 };
    Obstacle_Generator gen{};
    std::vector<Obstacle> obstacles;
     
    sc.draw_object(pl);
    sc.draw_hud("ENGINE STATE 100");    
    sc.draw_hud("SCORE 0000", 1, 2);
    int r_lim = sc.game_window_w - 10;

    for (;;)
    {
        start_frame(fr);
        
        pl.move(1, r_lim); 
        sc.draw_object(pl);
        
        auto obstacle = gen.get_next_obstacle();
        if (!obstacle.get_sprite().empty())
        {
            obstacles.push_back(obstacle);
        }

        for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
        {
            it->move(DR::DOWN, 2);
            sc.draw_object(*it);
        
            if (it->get_y() > 100) obstacles.erase(it);
        }
        
        if (check_collisions(sc, pl, obstacles))
        {
            score = 0;
            pl.reset_hp();

            while (getch() != 'c');
            
            sc.clear();
            obstacles.clear();
            
            sc.draw_hud("ENGINE STATE 100"); 

            continue;
        }
        
        score += 1;

        std::string score_str = "SCORE ";
        score_str += leading_zeroes(score) + std::to_string(score);
        sc.draw_hud(score_str, 1, 2);

        end_frame(fr, frame_ms);
    }

    return 0;
}
