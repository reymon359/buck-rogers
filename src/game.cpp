#include <game.h>
#include <player.h>
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

// Constructor
game::game(Vector2i dimension, std::string title)
{
    fps = 60;

    window1 = new RenderWindow(VideoMode(dimension.x, dimension.y), title);
    window1->setFramerateLimit(fps);


    load_graphics();
    event1= new Event,

    gameLoop();
}


void game::gameLoop()
{

    while(window1->isOpen())
    {
        player1.process_player_events();
        process_events();

        draw();
    }
}
void game::load_graphics()
{
    txt_title =  new  Texture;
    spr_title_1 = new Sprite;
    txt_title->loadFromFile("imgs/title_screen.png");
    spr_title_1-> setTexture(*txt_title);
    spr_title_1->setScale(((float)window1->getSize().x/(float)spr_title_1->getTexture()->getSize().x), ((float)window1->getSize().y/(float)spr_title_1->getTexture()->getSize().y));

//    txt_ship =  new  Texture;
//    spr_ship1 = new Sprite;
   //
//    spr_ship1->setScale(((float)window1->getSize().x/(float)spr_ship1->getTexture()->getSize().x), ((float)window1->getSize().y/(float)spr_ship1->getTexture()->getSize().y));




}
void game::draw()
{

    // We clean the window and then show it
    window1->clear();
    window1->draw( *spr_title_1);
     window1->draw(player1.get_sprite());
//    window1->draw(*spr_ship1);
    window1->display();


}

void game::process_events()
{
    while(window1->pollEvent(*event1))
    {
        // We are going to listen the different events
        switch(event1->type)
        {
        // window closed
        case Event::Closed:
            window1->close();
            exit(1);
            break;
        // Key pressed
//        case Event::KeyPressed:
//            if(Keyboard::isKeyPressed(Keyboard::Up))
//            {
//                spr_ship1->setPosition(spr_ship1->getPosition().x,spr_ship1->getPosition().y - 6);
//            }
//            else if(Keyboard::isKeyPressed(Keyboard::Down))
//            {
//
//                spr_ship1->setPosition(spr_ship1->getPosition().x,spr_ship1->getPosition().y + 6);
//            }
//            else if(Keyboard::isKeyPressed(Keyboard::Left))
//            {
//                spr_ship1->setPosition(spr_ship1->getPosition().x - 6,spr_ship1->getPosition().y);
//            }
//            else if(Keyboard::isKeyPressed(Keyboard::Right))
//            {
//                spr_ship1->setPosition(spr_ship1->getPosition().x + 6,spr_ship1->getPosition().y);
//            }
//
//            break;
        }
    }

}

//game::~game()
//{
//    //dtor
//}
