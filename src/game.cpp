#include "game.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;

// Constructor
game::game(Vector2f dimension, std::string title)
{
    // Setting window
    fps = 60;
    window1 = new RenderWindow(VideoMode(dimension.x, dimension.y), title);
    window1->setFramerateLimit(fps);

    event1 = new Event;

    load_resources();

    gameLoop();
}

// Here we load the game textures and sprites
void game::load_resources()
{
    // We are going to load the background texture and  water sprites
    txt_background = new Texture();
    txt_background -> loadFromFile("imgs/texture_background.png");

    spr_water1 = new Sprite(*txt_background);
    spr_water1 -> setTextureRect(sf::IntRect(2, 107, 255, 48));


    spr_water2 = new Sprite(*txt_background);
    spr_water2 -> setTextureRect(sf::IntRect(262, 107, 255, 48));
    spr_water2 -> setPosition(260,0);

    spr_water3 = new Sprite(*txt_background);
    spr_water3 -> setTextureRect(sf::IntRect(523, 107, 255, 48));
    spr_water3 -> setPosition(520,0);

    spr_water4 = new Sprite(*txt_background);
    spr_water4 -> setTextureRect(sf::IntRect(784, 107, 255, 48));
    spr_water4 -> setPosition(780,0);


    txt_ship.loadFromFile("imgs/ship.png");
    spr_ship1.setTexture(txt_ship);
//    spr_title_1.setScale(((float)window1->getSize().x/(float)txt_title.getSize().x), ((float)window1->getSize().y/(float)txt_title.getSize().y));

//    spr_title_1.setScale(((float)window1->getSize().x/(float)spr_title_1->getTexture()->getSize().x), ((float)window1->getSize().y/(float)spr_title_1->getTexture()->getSize().y));
}

void game::gameLoop()
{
    while(!game_over)
    {
        // We clean the window and then show it
        window1->clear();
//        process_events();
        window1->draw(*spr_water1);
        window1->draw(*spr_water2);
        window1->draw(*spr_water3);
        window1->draw(*spr_water4);
//         window1->draw(spr_ship1);
//        window1->draw((Sprite)player1->get_sprite());
        window1->display();
    }
}


//void game::process_events()
//{
//    while(window1->pollEvent(*event1))
//    {
//        // We are going to listen the different events
//        switch(event1->type)
//        {
//        // window closed
//        case Event::Closed:
//            window1->close();
//            exit(1);
//            break;
//        // Key pressed
//        case Event::KeyPressed:
//            if(Keyboard::isKeyPressed(Keyboard::Up))
//            {
//                player1->get_sprite()->setPosition(player1->get_sprite()->getPosition().x,player1->get_sprite()->getPosition().y - 6);
//            }
//            else if(Keyboard::isKeyPressed(Keyboard::Down))
//            {
//                player1->get_sprite()->setPosition(player1->get_sprite()->getPosition().x,player1->get_sprite()->getPosition().y + 6);
//            }
//            else if(Keyboard::isKeyPressed(Keyboard::Left))
//            {
//                player1->get_sprite()->setPosition(player1.get_sprite()->getPosition().x - 6,player1.get_sprite()->getPosition().y);
//            }
//            else if(Keyboard::isKeyPressed(Keyboard::Right))
//            {
//                player1.get_sprite()->setPosition(player1.get_sprite()->getPosition().x + 6,player1.get_sprite()->getPosition().y);
//            }
//
//            break;
//        }
//    }

//}

//game::~game()
//{
//    //dtor
//}
