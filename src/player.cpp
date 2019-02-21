#include "player.h"

player::player()
{
    //ctor
    txt_ship->loadFromFile("imgs/ship.png");
    spr_ship1-> setTexture(*txt_ship);
    spr_ship1->setScale(100.f/spr_ship1->getTexture()->getSize().x, 50.f/spr_ship1->getTexture()->getSize().y);
}

