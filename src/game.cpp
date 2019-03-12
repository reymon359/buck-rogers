#include "game.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>

#define velPlayer 4

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

    // 4th dimension
    clock1 = new Clock();
    time1 = new Time();

    gameSpeed = 2;
    time_water =0;


    load_resources();
    gameLoop();
}

// Here we load the game textures and sprites
void game::load_resources()
{
    // We are going to load the background texture and  water sprites
    txt_background = new Texture();
    txt_background -> loadFromFile("imgs/texture_background.png");

    spr_water = new Sprite(*txt_background);
    spr_water -> setPosition(0,230);
    spr_water -> setScale(800.f, 2200.f/spr_water->getTexture()->getSize().y); // desired size / actual size

    // Now the player texture and sprites

    txt_player = new Texture();
    txt_player -> loadFromFile("imgs/player.png");
    spr_player = new Sprite(*txt_player);
    spr_player -> setScale(500.f/spr_player->getTexture()->getSize().y, 500.f/spr_player->getTexture()->getSize().y);
    spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
    spr_player -> setPosition(350,470);

}

void game::gameLoop()
{
    while(!game_over)
    {

        *time1 = clock1->getElapsedTime();
         // To control manually the fps
        // The number you are dividing is the number of the fps, if you put a 3 the
        // game will "move" each 3 seconds cause the clock will restart every 3 seconds

        if(time1->asSeconds()>1/fps)
        {
            // Water animation
            time_water = (int)((time1->asSeconds())/(1/gameSpeed))%4;
            if ((int)time_water==0)
            {
                spr_water -> setTextureRect(sf::IntRect(2, 107, 255, 48));
            }
            else if ((int)time_water==1)
            {
                spr_water -> setTextureRect(sf::IntRect(262, 107, 255, 48));
            }
            else if ((int)time_water==2)
            {
                spr_water -> setTextureRect(sf::IntRect(523, 107, 255, 48));
            }
            else if ((int)time_water==3)
            {
                spr_water -> setTextureRect(sf::IntRect(784, 107, 255, 48));
            }
            else
            {
                time_water= 0;
            }





            process_events();
            draw();
        }
    }
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
        case Event::KeyPressed:

            if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                // If the player sprite is not above the limit it will go up
                if (spr_player -> getPosition().y > 390)
                {
                    spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
                    spr_player -> setPosition(spr_player -> getPosition().x, spr_player -> getPosition().y - velPlayer );
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (spr_player -> getPosition().y < 538)
                {
                    spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
                    spr_player -> setPosition(spr_player -> getPosition().x, spr_player -> getPosition().y + velPlayer );
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                if (spr_player -> getPosition().x > 2)
                {
                    spr_player -> setTextureRect(sf::IntRect(896, 1120, 224, 224));
                    spr_player -> setPosition(spr_player -> getPosition().x - velPlayer, spr_player -> getPosition().y );
                }
            }

            else if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                if (spr_player -> getPosition().x < 722)
                {
                    spr_player -> setTextureRect(sf::IntRect(672, 0, 224, 224));

                    spr_player -> setPosition(spr_player -> getPosition().x + velPlayer, spr_player -> getPosition().y );
                }
            }
            break;
        case Event::KeyReleased:
            if(!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
            {
//                cout<< "key left or right not pressed" <<endl;
                spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
            }
            break;
        }
    }

}

void game::draw()
{
    window1->clear();
    window1->draw(*spr_water);
    window1->draw(*spr_player);
    window1->display();
}

//game::~game()
//{
//    //dtor
//}
