#pragma once

#ifndef GAME_H
#define GAME_H

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

    private:

        RenderWindow * window1;

        int fps;

        Texture * txt_title, * txt_ship;
        Sprite * spr_title_1, *spr_ship1;

        Event * event1;

};

#endif // GAME_H
