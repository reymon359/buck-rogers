#include "game.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>

#include <time.h>       /* time */


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

    initialize_stuff();
    load_resources();
//    start_game();
    gameLoop();
}

void game::initialize_stuff()
{
    gameSpeed = 4;
    vel_player = 5;
    player_points = 0;
    player_objectives = 0;
    player_lifes = 3;
    time_water = 0;
    time_objectives = 0;
    pass_between = 0;
    rockSize = 30;
    game_status = -1;// For before starting the game
}

void game::start_game()
{
    game_status = 1;

    spr_islands -> setPosition(-10,130);
    spr_islands2 -> setPosition(790,130);

    spr_player ->setTexture(*txt_player);
    spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
    spr_player -> setPosition(350,470);

    text_score -> setPosition(10,40);

    spawn_rocks();
}

void game::end_game()
{
    game_status =-1;
    window1->draw(*spr_title);
    text_score -> setString("       GAME OVER.\n    TOTAL SCORE: " + std::to_string(player_points)
                            + "\n\n\n\n\n\nPRESS A TO PLAY AGAIN");
    text_score -> setPosition(240,80);
}

// Here we load the game textures and sprites
void game::load_resources()
{
    // Title Screen for end game
    txt_title = new Texture();
    txt_title -> loadFromFile("imgs/title_screen_raw.png");
    spr_title = new Sprite(*txt_title);
    spr_title -> setScale(800.f/256, 600.f/224);

    // We are going to load the background texture and  water sprites
    txt_background = new Texture();
    txt_background -> loadFromFile("imgs/texture_background.png");

    // Text and fonts
    font1 = new Font();
    font1->loadFromFile("fonts/256bytes.ttf");

    text_time = new Text();
    text_time -> setFont(*font1);
    text_time -> setString("TIME");
    text_time -> setPosition(10,5);
    text_time -> setCharacterSize(40);

    text_score = new Text();
    text_score -> setFont(*font1);
    text_score -> setString("Ramon Morcillo\n    Presents: \n\n\n\n\n\nPRESS A TO PLAY");
    text_score -> setPosition(260,80);
    text_score -> setCharacterSize(40);

    font_objectives = new Font();
    font_objectives ->loadFromFile("fonts/AfricOrnOne.ttf");
    text_objectives = new Text();
    text_objectives -> setFont(*font_objectives);
    text_objectives -> setCharacterSize(15);
    text_objectives -> setPosition(600,60);

    // Water and islands
    spr_water = new Sprite(*txt_background);
    spr_water -> setPosition(0,230);
    spr_water -> setScale(800.f, 2200.f/spr_water->getTexture()->getSize().y); // desired size / actual size

    spr_islands = new Sprite(*txt_background);
    spr_islands -> setTextureRect(sf::IntRect(1, 70, 512, 32));
    spr_islands -> setScale(800.f/512, 100.f/32);

    spr_islands2 = new Sprite(*txt_background);
    spr_islands2 -> setTextureRect(sf::IntRect(1, 70, 512, 32));
    spr_islands2 -> setScale(800.f/512, 100.f/32);

    spr_sky = new Sprite(*txt_background);
    spr_sky -> setTextureRect(sf::IntRect(2, 70, 10, 10));
    spr_sky -> setScale(800.f/10, 130.f/10);


    // Now the player texture and sprites
    txt_player = new Texture();
    txt_player -> loadFromFile("imgs/player.png");
    spr_player = new Sprite(*txt_player);
    spr_player -> setScale(500.f/spr_player->getTexture()->getSize().y, 500.f/spr_player->getTexture()->getSize().y);

    txt_player_explosion = new Texture();
    txt_player_explosion -> loadFromFile("imgs/explosion.png");

    // Player lifes
    txt_life = new Texture();
    txt_life -> loadFromFile("imgs/heart.png");
    spr_life1 = new Sprite(*txt_life);
    spr_life1 -> setScale(50.f/190, 50.f/200);
    spr_life1 -> setPosition(600,10);
    spr_life2 = new Sprite(*txt_life);
    spr_life2 -> setScale(50.f/190, 50.f/200);
    spr_life2 -> setPosition(650,10);
    spr_life3 = new Sprite(*txt_life);
    spr_life3 -> setScale(50.f/190, 50.f/200);
    spr_life3 -> setPosition(700,10);

    // Rocks
    txt_rock = new Texture();
    txt_rock -> loadFromFile("imgs/sea_rock.png");

    // Enemies
    txt_ufo = new Texture();
    txt_ufo -> loadFromFile("imgs/ufo.png");
}

void game::spawn_rocks()
{
    srand (time(NULL));
    int randomSize = rand() % rockSize + 1;// Random size between rocks

    rock_pos.x =  rand() % (800-(rockSize*2 + randomSize) ) + 1;// Random spawn point
    rock_pos.y = 210;
    rock1 = new RectangleShape({rockSize,rockSize});
    rockspace = new RectangleShape({rockSize + randomSize,rockSize});
    rock2 = new RectangleShape({rockSize,rockSize});

    rock1 -> setTexture(txt_rock);
    rockspace -> setFillColor(Color::Transparent);
    rock2 -> setTexture(txt_rock);

    rock1-> setPosition(rock_pos.x,rock_pos.y);
    rockspace-> setPosition(rock_pos.x + rockSize,rock_pos.y);
    rock2-> setPosition(rock_pos.x + randomSize +(rockSize*2),rock_pos.y);
}


void game::gameLoop()
{
    while(!game_over)
    {
        *time1 = clock1->getElapsedTime();
        // To control manually the fps
        // The number you are dividing is the number of the fps, if you put a 3 the
        // game will "move" each 3 seconds cause the clock will restart every 3 seconds

        if(time1->asSeconds()>5/fps)
        {
            if(game_status >= 1 )
            {
                move_water();
                move_rocks();
                process_collisions();
                calculate_objectives();
            }
            else if(game_status == 0)
            {
                // When the game has stopped
                if(time1->asSeconds() >= time2) // if time reaches the 4 secs
                {
                    time2 = 0;
                    if(player_lifes>=0)
                    {
                        start_game();
                    }
                    else
                    {
                        end_game(); // Game Over
                    }
                }
            }
            process_events();
            draw();
        }

        if(player_objectives== 0)  // If the player accomplishes all objectives
        {
            if(game_status == 1)  // And it is in the first stage
            {
                game_status = 2; // He passes to the second stage
                  player_objectives = 15;
                spawn_enemies();

            }

        }
    }
}

void game::move_water()
{
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
}


void game::move_rocks()
{
    // Change the size
    rock1->setSize({rock1 ->getSize().x + (float)(gameSpeed/8),rock1 ->getSize().y + (float)(gameSpeed/8)});
    rockspace->setSize({rockspace ->getSize().x + (float)(gameSpeed/4),rockspace ->getSize().y + (float)(gameSpeed/8)});
    rock2->setSize({rock2 ->getSize().x + (float)(gameSpeed/8),rock2 ->getSize().y + (float)(gameSpeed/8)});

    // Change the position
    rock1-> setPosition(rock1 -> getPosition().x - (float)(gameSpeed/8),rock1 -> getPosition().y + (gameSpeed/3));
    rockspace-> setPosition(rockspace -> getPosition().x,rockspace -> getPosition().y + (gameSpeed/3));
    rock2-> setPosition(rock2 -> getPosition().x + (float)(gameSpeed/4),rock2 -> getPosition().y + (gameSpeed/3));

    if(rock1 -> getPosition().y >= 650)
    {
        spawn_rocks();
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
            if(game_status>= 1)
            {
                if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    // If the player sprite is not above the limit it will go up
                    if (spr_player -> getPosition().y > 390)
                    {
                        spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
                        spr_player -> setPosition(spr_player -> getPosition().x, spr_player -> getPosition().y - vel_player );
                    }
                }
                else if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if (spr_player -> getPosition().y < 538)
                    {
                        spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
                        spr_player -> setPosition(spr_player -> getPosition().x, spr_player -> getPosition().y + vel_player );
                    }
                }
                else if(Keyboard::isKeyPressed(Keyboard::Left))
                {
                    // Move the rocks and islands
                    rock1-> setPosition(rock1 -> getPosition().x + (float)(vel_player/1.5),rock1 -> getPosition().y );
                    rockspace-> setPosition(rockspace -> getPosition().x + (float)(vel_player/1.5),rockspace -> getPosition().y);
                    rock2-> setPosition(rock2 -> getPosition().x + (float)(vel_player/1.5),rock2 -> getPosition().y);
                    // And the islands background
                    spr_islands -> setPosition(spr_islands -> getPosition().x + (float)(vel_player/2.3),spr_islands -> getPosition().y );
                    spr_islands2 -> setPosition(spr_islands2 -> getPosition().x + (float)(vel_player/2.3),spr_islands2 -> getPosition().y );

                    if (spr_player -> getPosition().x > 2)
                    {
                        spr_player -> setTextureRect(sf::IntRect(896, 1120, 224, 224));
                        spr_player -> setPosition(spr_player -> getPosition().x - vel_player, spr_player -> getPosition().y);

                    }
                }
                else if(Keyboard::isKeyPressed(Keyboard::Right))
                {
                    // Move the rocks and islands
                    rock1-> setPosition(rock1 -> getPosition().x - (float)(vel_player/1.5),rock1 -> getPosition().y );
                    rockspace-> setPosition(rockspace -> getPosition().x - (float)(vel_player/1.5),rockspace -> getPosition().y);
                    rock2-> setPosition(rock2 -> getPosition().x - (float)(vel_player/1.5),rock2 -> getPosition().y);

                    spr_islands -> setPosition(spr_islands -> getPosition().x - (float)(vel_player/2.3),spr_islands -> getPosition().y );
                    spr_islands2 -> setPosition(spr_islands2 -> getPosition().x - (float)(vel_player/2.3),spr_islands2 -> getPosition().y );

                    if (spr_player -> getPosition().x < 722)
                    {
                        spr_player -> setTextureRect(sf::IntRect(672, 0, 224, 224));
                        spr_player -> setPosition(spr_player -> getPosition().x + vel_player, spr_player -> getPosition().y );

                    }
                }

            }
            if(game_status == -1)
            {
                if(Keyboard::isKeyPressed(Keyboard::A))
                {
                    // Restart game
                    initialize_stuff();
                    start_game();
                }
            }
            break;
        case Event::KeyReleased:
            if(game_status>= 1)
            {

                if(!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
                {
                    spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
                }
            }
            break;
        }

        // Move islands background.When the islands1 passes through 0 patatero
        if(spr_islands -> getPosition().x <= -0.5 && spr_islands -> getPosition().x > -2)
        {
            // islands at begining
//            cout << "0 patatero" <<endl;
            // Now we look which one has an x greater to see where are they
            if(spr_islands -> getPosition().x > spr_islands2 -> getPosition().x )
            {
                // If islands2 is at left I put islands2 at right
                spr_islands2 -> setPosition(790,spr_islands2 -> getPosition().y );
            }
            else if(spr_islands -> getPosition().x < spr_islands2 -> getPosition().x )
            {
                // If islands2 is at right I put islands2 at left
                spr_islands2 -> setPosition(-790,spr_islands2 -> getPosition().y );
            }
        }
        // When the islands2 passes through 0 patatero
        if(spr_islands2 -> getPosition().x <= -0.5 && spr_islands2 -> getPosition().x > -2)
        {
            // Now we look which one has an x greater to see where are they
            if(spr_islands2 -> getPosition().x > spr_islands -> getPosition().x )
            {
                // If islands is at left I put islands at right
                spr_islands -> setPosition(790,spr_islands -> getPosition().y );
            }
            else if(spr_islands2 -> getPosition().x < spr_islands -> getPosition().x )
            {
                // If islands is at right I put islands at left
                spr_islands -> setPosition(-790,spr_islands -> getPosition().y );
            }
        }
    }
}

void game::process_collisions()
{
    // If the player pass between the rocks
    if(spr_player -> getGlobalBounds().intersects(rockspace -> getGlobalBounds()) && pass_between == 0)
    {
        pass_between ++;
        player_objectives--;
        player_points += 500;
    }
    else if(!spr_player -> getGlobalBounds().intersects(rockspace -> getGlobalBounds()))
    {
        pass_between = 0;
    }
    text_score -> setString("SCORE " + std::to_string(player_points));

    // If the player hits the rocks
    if(spr_player -> getGlobalBounds().intersects(rock1 -> getGlobalBounds()) || spr_player -> getGlobalBounds().intersects(rock2 -> getGlobalBounds()))
    {
        player_crashed();
    }
}


void game::calculate_objectives()
{
    // The objectives are acomplished if the player stays alive some X time or passing between rocks
    if(time1->asSeconds()>= time_objectives+(gameSpeed*1.2))
    {
        time_objectives = time1->asSeconds() + (gameSpeed*1.2);
        player_objectives--;
    }
    string strAux;
    for (int i = 0; i<player_objectives; i++ )
    {
        strAux.append("h");
        if(i == 9)
        {
            strAux.append("\n");
        }
    }
    text_objectives -> setString(strAux);
}

// When the player crashes and explodes
void game::player_crashed()
{
    // First I change the sprite for the explosion one
    spr_player ->setTexture(*txt_player_explosion);
    spr_player -> setTextureRect(sf::IntRect(97, 65, 393, 420));
    // I put the explosion between the rocks and the player sprite for more realism
    spr_player -> setPosition(spr_player -> getPosition().x, (spr_player -> getPosition().y + rock1 -> getPosition().y)/2);

    // Then I change the status of the game to 0 (stopped)
    game_status = 0; // stop game
    player_lifes -- ; // minus 1 life
    time2 = time1->asSeconds() + 3; // For the game loopy loop
}

void game::draw()
{
    window1->clear();
    if (game_status == -1)
    {
        window1->draw(*spr_title);
        window1->draw(*text_score);
    }
    else
    {
        window1->draw(*spr_water);
        window1->draw(*spr_islands);
        window1->draw(*spr_islands2);
        window1->draw(*rock1);
        window1->draw(*rockspace);
        window1->draw(*rock2);
        window1->draw(*spr_player);
        window1->draw(*spr_sky);
        window1->draw(*text_time);
        window1->draw(*text_score);
        window1->draw(*text_objectives);


        // Drawing lifes
        if(player_lifes == 3 )
        {
            window1->draw(*spr_life1);
            window1->draw(*spr_life2);
            window1->draw(*spr_life3);
        }
        if(player_lifes ==2 )
        {
            window1->draw(*spr_life1);
            window1->draw(*spr_life2);
        }
        if(player_lifes ==1 )
        {
            window1->draw(*spr_life1);
        }

        if (game_status == 2)
        {
//           cout<<"drawing enemies"<<endl;
            window1->draw(*ufo1);
            window1->draw(*ufo2);
        }

    }
    window1->display();
}

void game::spawn_enemies()
{
    cout<<"spawn enemies"<<endl;
    int ufo1_size, ufo2_size;
    srand (time(NULL));


    int ran1 =  rand() % 1;
    cout<<"ran1: "<<ran1<<endl;
    if (ran1 > 50 )
    {
        ufo1_pos.y = 150;
        ufo1_size = 10;
    }
    else
    {
        ufo1_pos.y = 570;
        ufo1_size =30;
    }
    ufo1_pos.x = rand() % (800-ufo1_size ) + 1;

    int ran2 =  rand() % 100;
    cout<<"ran2: "<<ran2<<endl;
    if (ran2 > 50 )
    {
        ufo2_pos.y = 150;
        ufo2_size = 10;
    }
    else
    {
        ufo2_pos.y = 570;
        ufo2_size =30;
    }
    ufo2_pos.x = rand() % (800-ufo2_size ) + 1;

    ufo1 = new RectangleShape({ufo1_size,ufo1_size});
    ufo2 = new RectangleShape({ufo2_size,ufo2_size});

    ufo1 -> setFillColor(Color::Green);
    ufo2 -> setFillColor(Color::Red);
//    ufo1 -> setTexture(txt_ufo);
//    ufo2 -> setTexture(txt_ufo);

    ufo1 -> setPosition(ufo1_pos.x,ufo1_pos.y);
    ufo2 -> setPosition(ufo2_pos.x,ufo2_pos.y);
    cout<<"Ufo1 size: "<<ufo1_size<<endl;
    cout<<"Ufo1 position: x:"<<ufo1_pos.x << " y: "<<ufo1_pos.y <<endl;
    cout<<"Ufo2 size: "<<ufo2_size<<endl;
    cout<<"Ufo2 position: x:"<<ufo2_pos.x << " y: "<<ufo2_pos.y <<endl;
    cout<<"end spawn enemies"<<endl;
}

void game::move_enemies()
{





}









//game::~game()
//{
//    //dtor
//}
