#include "player.h"
#include <stdlib.h>
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

player::player()
{
    //ctor
    txt_ship.loadFromFile("imgs/ship.png");
    spr_ship1.setTexture(txt_ship);
//    spr_ship1.setScale(100.f/spr_ship1.getTexture()->getSize().x, 50.f/spr_ship1.getTexture()->getSize().y);



}

Sprite player::get_sprite()
{

    return spr_ship1;
}


