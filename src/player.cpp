#include "player.h"
#include "game.h"

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

player::player()
{
    //ctor
    txt_ship->loadFromFile("imgs/ship.png");
    spr_ship1-> setTexture(*txt_ship);
    spr_ship1->setScale(100.f/spr_ship1->getTexture()->getSize().x, 50.f/spr_ship1->getTexture()->getSize().y);



}

Sprite player::get_sprite()
{

    return *spr_ship1;
}

void player::process_player_events()
{
//    while(window1->pollEvent(*eventPlayer))
//    {
        // We are going to listen the different events
        switch(eventPlayer->type)
        {

        // Key pressed
        case Event::KeyPressed:
            if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                spr_ship1->setPosition(spr_ship1->getPosition().x,spr_ship1->getPosition().y - 6);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Down))
            {

                spr_ship1->setPosition(spr_ship1->getPosition().x,spr_ship1->getPosition().y + 6);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                spr_ship1->setPosition(spr_ship1->getPosition().x - 6,spr_ship1->getPosition().y);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                spr_ship1->setPosition(spr_ship1->getPosition().x + 6,spr_ship1->getPosition().y);
            }

            break;
        }
//    }

}
