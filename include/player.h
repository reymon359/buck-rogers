#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>


using namespace sf;

class player
{
public:
    player();
    Sprite get_sprite();


private:

    Texture txt_ship;
    Sprite spr_ship1;

};

#endif // PLAYER_H

