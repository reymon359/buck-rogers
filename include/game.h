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

    // Textures and Sprites
    Texture * txt_background;
    Sprite * spr_water;

    Texture * txt_player;
    Sprite * spr_player;

    Texture * txt_rock;
    RectangleShape * rock1;
    RectangleShape * rockspace;
    RectangleShape * rock2;
    float rockSize;


//    Vector2i sprite_division;
//    Vector2i actual_frame;
//    int sprite_flip;



    bool game_over = false;
    int fps;
};

#endif // GAME_H
