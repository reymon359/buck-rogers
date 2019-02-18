#include <game.h>

#include "SFML/Graphics.hpp"

using namespace sf;

// Constructor
game::game(int width, int height, std::string title)
{
    fps = 60;

    window1 = new RenderWindow(VideoMode(width, height), title);

    window1->setFramerateLimit(fps);

    texture1 =  new  Texture;

    sprite1 = new Sprite;

    texture1->loadFromFile("Buckrogers_Title.png");

    sprite1-> setTexture(*texture1);

    gameLoop();
}


void game::gameLoop(){

    while(window1->isOpen()){

        draw();
    }
}

void game::draw(){

        // We clean the window and then show it
        window1->clear();

        window1->draw(*sprite1);




        window1->display();


}
//game::~game()
//{
//    //dtor
//}
