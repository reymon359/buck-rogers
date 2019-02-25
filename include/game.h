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
    void load_graphics();
//    void process_events();

private:

    Texture * txt_background;
    Sprite * spr_water1, * spr_water2,* spr_water3, * spr_water4;


    Texture txt_ship;
    Sprite spr_ship1;


    RenderWindow * window1;

    Texture  txt_title;
    Sprite  spr_title_1;

    player * player1;

    Event * event1;

    bool game_over;
    int fps;
};

#endif // GAME_H
