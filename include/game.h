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
    game(Vector2i dimension, std::string title);

        void gameLoop();
        void draw();
        void process_events();
        void load_graphics();

    private:

        RenderWindow * window1;

        int fps;

        player * player1;

        Texture * txt_title;
        Sprite * spr_title_1;

        Event * event1;

};

#endif // GAME_H
