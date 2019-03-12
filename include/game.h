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
    void process_events();
    void move_rocks();
    void draw();

private:
    // Window
    RenderWindow * window1;
    Event * event1;

    // Time
    Clock * clock1;
    Time * time1;
    float gameSpeed;
    float  time_water;

    // Background
    Texture * txt_background;
    Sprite * spr_water;

    // Player
    Texture * txt_player;
    Sprite * spr_player;
    int vel_player;

    Texture * txt_rock;
    RectangleShape * rock1;
    RectangleShape * rockspace;
    RectangleShape * rock2;
    int rockSize;

        Vector2i rock_pos;

//    Vector2i sprite_division;
//    Vector2i actual_frame;
//    int sprite_flip;



    bool game_over = false;
    int fps;
};

#endif // GAME_H
