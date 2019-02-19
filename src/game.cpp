#include <game.h>

#include "SFML/Graphics.hpp"

using namespace sf;

// Constructor
game::game(int width, int height, std::string title)
{
    fps = 60;
    window1 = new RenderWindow(VideoMode(width, height), title);
    window1->setFramerateLimit(fps);


    txt_title =  new  Texture;
    spr_title_1 = new Sprite;

    txt_title->loadFromFile("imgs/title_screen.png");


    spr_title_1-> setTexture(*txt_title);

    spr_title_1->setScale(((float)window1->getSize().x/(float)spr_title_1->getTexture()->getSize().x), ((float)window1->getSize().y/(float)spr_title_1->getTexture()->getSize().y));
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

        window1->draw(*spr_title_1);




        window1->display();


}
//game::~game()
//{
//    //dtor
//}
