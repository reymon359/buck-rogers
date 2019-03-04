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

    void gameLoop();
    void process_events();
    void load_resources();
    void draw();

private:

    RenderWindow * window1;

    Event * event1;

    Sprite * spr_character1;
    Texture * txt_character1;


    Vector2i sprite_division;
    Vector2i actual_frame;
    int sprite_flip;

    Texture * txt_background;
    Sprite * spr_water1, * spr_water2,* spr_water3, * spr_water4;


    Texture txt_ship;
    Sprite spr_ship1;




//    player * player1;


    bool game_over = false;
    int fps;
};

#endif // GAME_H
