#pragma once

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class game
{
public:
    // Constructor
    game(Vector2f dimension, std::string title);

    void load_resources();
    void gameLoop();
    void start_game();
    void process_events();
    void process_collisions();
    void move_water();
    void spawn_rocks();
    void move_rocks();
    void draw();

private:
    // Game
    RenderWindow * window1;
    Event * event1;
    int game_status;

    // Time
    Clock * clock1;
    Time * time1;
    float gameSpeed;
    float  time_water;

    // Background
    Texture * txt_background;
    Sprite * spr_water;
    Sprite * spr_islands;
    Sprite * spr_islands2;

    // Player
    Texture * txt_player;
    Texture * txt_player_explosion;
    Sprite * spr_player;
    int vel_player;
    int player_points;
    int pass_between;

    // Rocks
    Texture * txt_rock;
    RectangleShape * rock1;
    RectangleShape * rockspace;
    RectangleShape * rock2;
    int rockSize;
    int randomSize;
    int randomSpawn;
    Vector2i rock_pos;

    // Font
    Font * font1;
    Text * text_score;
    Text * text_time;
//    Vector2i sprite_division;
//    Vector2i actual_frame;
//    int sprite_flip;



    bool game_over = false;
    int fps;
};

#endif // GAME_H
