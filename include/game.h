#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

using namespace sf;

class game
{
    public:
        // Constructor
        game(int width, int height, std::string title);

        void gameLoop();

        void draw();


    private:

        RenderWindow * window1;

        int fps;

        Texture * txt_title;
        Sprite * spr_title_1;

};

#endif // GAME_H
