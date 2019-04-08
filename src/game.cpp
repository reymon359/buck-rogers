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
    gameLoop();
}

void game::initialize_stuff()
{
    gameSpeed = 4;
    vel_player = 5;
    player_points = 0;
    player_objectives = 2;
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

    spr_player -> setTexture(*txt_player);
    spr_player -> setTextureRect(sf::IntRect(0, 0, 224, 224));
    spr_player -> setPosition(350,470);

    text_score -> setPosition(10,40);

    player_time = new RectangleShape({450,30});
    player_time -> setFillColor(Color::White);
    player_time-> setPosition(120,10);

    spawn_rocks();
    if(game_level==2)
    {
        spawn_ufo1();
        spawn_ufo2();
    }
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
    spr_player -> setScale(300.f/spr_player->getTexture()->getSize().y, 300.f/spr_player->getTexture()->getSize().y);

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



    // Bullets
    for (int i = 0; i < sizeof(slots_bullets); i++ )
    {
        slots_bullets[i] = false; // all bullets to false, none is fired yet
        bullets[i] = new RectangleShape({5,30}); // creating them
        bullets[i] -> setFillColor(Color::Magenta); // Magenta bullets ftw
    }

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
                pass_time();
                move_water();
                move_rocks();
                process_collisions();
                calculate_objectives();
                if(game_level==2)
                {
                    move_enemies();
                    if (ufo1_state==2)
                    {
                        if(time_respawn_ufo1 <= time1->asSeconds()) spawn_ufo1();
                    }
                    if (ufo2_state==2)
                    {
                        if(time_respawn_ufo2 <= time1->asSeconds()) spawn_ufo2();
                    }
                }
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
            shooting_bullets();
            draw();
        }

        if(player_objectives == 0)  // If the player accomplishes all objectives
        {
            if(game_status == 1)  // And it is in the first stage
            {
                game_status = 2; // He passes to the second stage
                game_level = 2;
                player_objectives = 2;
                spawn_ufo1();
                spawn_ufo2();

            }

        }
    }
}

void game::pass_time(){
//    player_time = new RectangleShape({450,30});
    player_time -> setSize({player_time ->getSize().x - (float)(gameSpeed/32),player_time ->getSize().y });
//    player_time-> setPosition(120,10);
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
                /// Shoot a bullet
                if(Keyboard::isKeyPressed(Keyboard::Space))
                {
                    for (int i = 0; i < sizeof(slots_bullets); i++ ) // go through bullets array
                    {
                        if(slots_bullets[i] == false) // When it finds a bullet not fired
                        {
                            slots_bullets[i] = true; // Changed to fired
                            // Now i spawn the bullet a bit upper the player position
                            bullets[i]-> setPosition(spr_player -> getPosition().x+15, spr_player -> getPosition().y -40 );
                            break; // We exit the for
                        }
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
            // Quit game pressing Q
            if(Keyboard::isKeyPressed(Keyboard::Q))
            {
                window1->close();
                exit(1);
                break;
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
        player_crashed(1);
    }
    // If the player hits the ufos
    if (game_level == 2) // Here was the biggest problem of the fucking game
    {
        if(spr_player -> getGlobalBounds().intersects(ufo1 -> getGlobalBounds()) || spr_player -> getGlobalBounds().intersects(ufo2 -> getGlobalBounds()))
        {
            player_crashed(2);
        }
    }

}


void game::calculate_objectives()
{
    /// The objectives are acomplished if the player stays alive some X time or passing between rocks or killing ufos
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
void game::player_crashed(int a)
{
    // First I change the sprite for the explosion one
    spr_player ->setTexture(*txt_player_explosion);
    spr_player -> setTextureRect(sf::IntRect(97, 65, 393, 420));

    // I put the explosion between the rocks or the ufo and the player sprite for more realism
    if(a==1)spr_player -> setPosition(spr_player -> getPosition().x, (spr_player -> getPosition().y + rock1 -> getPosition().y)/2);

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
        window1->draw(*player_time);
        window1->draw(*text_score);
        window1->draw(*text_objectives);
        // Drawing bullets
        for (int i = 0; i < sizeof(slots_bullets); i++ )
        {
            if(slots_bullets[i] == true) window1->draw(*bullets[i]);
        }

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
        // Drawing ufos
        if (game_level == 2)
        {
            window1->draw(*ufo1);
            window1->draw(*ufo2);
        }
    }
    window1->display();
}
void game::spawn_ufo1()
{
    ufo1_state=1; // Ufo is alive
    int ufo1_size; // Ufosize
    srand (time(NULL)+1);
    int ran1 =  rand() % 100; // Random number

    if (ran1 > 50 )
    {
        ufo1_pos.y = 150; // Spawns Up
        ufo1_size = 10; // So it is small
        ufo1_direction.y=1; // Goes down
    }
    else
    {
        ufo1_pos.y = 570; // Spawns Down
        ufo1_size =30; // So it is big
        ufo1_direction.y=0; // Goes Up
    }
    ufo1_pos.x = rand() % (800-ufo1_size ) + 1; // Random x position betweeen 0 and 800
    ufo1 = new RectangleShape({ufo1_size,ufo1_size}); // We create the ufo
    ufo1 -> setTexture(txt_ufo); // Texture added
    ufo1 -> setTextureRect(sf::IntRect(5, 89, 44, 38)); // Texture part desired
    ufo1 -> setPosition(ufo1_pos.x,ufo1_pos.y); // We put the position with the random numbers from before

    int ran2 =  rand() % 100; // Another random number to determine if it goes left or right
    ufo1_direction.x = 0;
    if (ran2 > 50 ) ufo1_direction.x= 1;
}
void game::spawn_ufo2() // Same as the spawnufo1 but for the ufo2
{
    ufo2_state=1;
    int  ufo2_size;
    srand (time(NULL));
    int ran3 =  rand() % 100;

    if (ran3 > 50 )
    {
        ufo2_pos.y = 150;
        ufo2_size = 10;
        ufo2_direction.y=1;
    }
    else
    {
        ufo2_pos.y = 570;
        ufo2_size =30;
        ufo2_direction.y=0;
    }
    ufo2_pos.x = rand() % (800-ufo2_size ) + 1;
    ufo2 = new RectangleShape({ufo2_size,ufo2_size});
    ufo2 -> setTexture(txt_ufo);
    ufo2 -> setTextureRect(sf::IntRect(5, 89, 44, 38));
    ufo2 -> setPosition(ufo2_pos.x,ufo2_pos.y);

    int ran4 =  rand() % 100;
    ufo2_direction.x= 0;
    if (ran4 > 50 )  ufo2_direction.x= 1;
}

void game::move_enemies()
{
    // First I am going to check if it is
    if(ufo1_direction.y == 0) // If it goes up
    {
        if(ufo1_direction.x == 0) // If it goes left
        {
            ufo1 -> setPosition(ufo1 -> getPosition().x - (gameSpeed/4), ufo1 -> getPosition().y - (gameSpeed/4));
            if(ufo1 -> getPosition().x <= 0) ufo1_direction.x = 1;// If it hits the left wall I change the direction to right
        }
        else if(ufo1_direction.x == 1)// If it goes right
        {
            ufo1 -> setPosition(ufo1 -> getPosition().x + (gameSpeed/4), ufo1 -> getPosition().y - (gameSpeed/4));
            if(ufo1 -> getPosition().x >= 800)  ufo1_direction.x = 0; // If it hits the right wall I change the direction to left
        }
        if(ufo1 -> getPosition().y <= 140)
        {
            ufo1_direction.y =1; // Hits top, direction bottom
        }

    }
    if(ufo1_direction.y == 1) // If it goes down
    {
        if(ufo1_direction.x == 0) // If it goes left
        {
            ufo1 -> setPosition(ufo1 -> getPosition().x - (gameSpeed/4), ufo1 -> getPosition().y + (gameSpeed/4));
            if(ufo1 -> getPosition().x <= 0) ufo1_direction.x = 1;// If it hits the left wall I change the direction to right
        }
        else if(ufo1_direction.x == 1)// If it goes right
        {
            ufo1 -> setPosition(ufo1 -> getPosition().x + (gameSpeed/4), ufo1 -> getPosition().y + (gameSpeed/4));
            if(ufo1 -> getPosition().x >= 800)  ufo1_direction.x = 0; // If it hits the right wall I change the direction to left
        }
        if(ufo1 -> getPosition().y >= 580)
        {
            ufo1_direction.y =0;  // Hits bottom, direction top
        }
    }
    // UFO size
    if(ufo1 -> getPosition().y <= 280) ufo1->setSize({20,20}); // Size to small
    if(ufo1 -> getPosition().y > 280 && ufo1 -> getPosition().y <= 420 ) ufo1->setSize({30,30});// Size to medium}
    if(ufo1 -> getPosition().y > 420)  ufo1->setSize({40,40}); // Size to big

    // NOW UFO 2
    // First I am going to check if it is
    if(ufo2_direction.y == 0) // If it goes up
    {
        if(ufo2_direction.x == 0) // If it goes left
        {
            ufo2 -> setPosition(ufo2 -> getPosition().x - (gameSpeed/3), ufo2 -> getPosition().y - (gameSpeed/3));
            if(ufo2 -> getPosition().x  <= 0) ufo2_direction.x = 1;// If it hits the left wall I change the direction to right
        }
        else if(ufo2_direction.x == 1)// If it goes right
        {
            ufo2 -> setPosition(ufo2 -> getPosition().x + (gameSpeed/3), ufo2 -> getPosition().y - (gameSpeed/3));
            if(ufo2 -> getPosition().x  >=  800)  ufo2_direction.x = 0; // If it hits the right wall I change the direction to left
        }
        if(ufo2 -> getPosition().y <= 140)
        {
            ufo2_direction.y =1; // Hits top, direction bottom
        }
    }
    if(ufo2_direction.y == 1) // If it goes down
    {
        if(ufo2_direction.x == 0) // If it goes left
        {
            ufo2 -> setPosition(ufo2 -> getPosition().x - (gameSpeed/3), ufo2 -> getPosition().y + (gameSpeed/3));
            if(ufo2 -> getPosition().x <= 0) ufo2_direction.x = 1;// If it hits the left wall I change the direction to right
        }
        else if(ufo2_direction.x == 1)// If it goes right
        {
            ufo2 -> setPosition(ufo2 -> getPosition().x + (gameSpeed/3), ufo2 -> getPosition().y + (gameSpeed/3));
            if(ufo2 -> getPosition().x >= 800)  ufo2_direction.x = 0; // If it hits the right wall I change the direction to left
        }
        if(ufo2 -> getPosition().y >= 580)
        {
            ufo2_direction.y =0;  // Hits bottom, direction top
        }
    }
    // UFO size
    if(ufo2 -> getPosition().y <= 280) ufo2->setSize({20,20}); // Size to small
    if(ufo2 -> getPosition().y > 280 && ufo2 -> getPosition().y <= 420 ) ufo2->setSize({30,30});// Size to medium}
    if(ufo2 -> getPosition().y > 420)  ufo2->setSize({40,40}); // Size to big

    if(ufo1_direction.y == -1)  ufo1 -> setPosition( ufo1 -> getPosition().x, ufo1 -> getPosition().y );
    if(ufo2_direction.y == -1)  ufo2 -> setPosition( ufo2 -> getPosition().x, ufo2 -> getPosition().y );
}


void game::shooting_bullets()
{
    for (int i = 0; i < sizeof(slots_bullets); i++ ) // go through bullets array
    {
        /// Move the bullets
        if(slots_bullets[i] == true)  //  when it finds a bullet that is fired
        {
            // Now I move the bullet a bit upper
            bullets[i]-> setPosition(bullets[i] -> getPosition().x, bullets[i] -> getPosition().y -4 );
        }
        /// Delete the bullets
        if(bullets[i]-> getPosition().y < 130)
        {
            slots_bullets[i] = false;
        }
        if(game_level == 2) /// Status problem hehe
        {
            /// Hits ufo1
            if(bullets[i] -> getGlobalBounds().intersects(ufo1 -> getGlobalBounds()) && ufo1_state==1)
            {
                slots_bullets[i] = false; // I put the bullet to false
                ufo1_exploded();
            }
            /// Hits ufo2
            if(bullets[i] -> getGlobalBounds().intersects(ufo2 -> getGlobalBounds()) && ufo2_state==1)
            {
                slots_bullets[i] = false; // I put the bullet to false
                ufo2_exploded();
            }
        }
    }
}

void game::ufo1_exploded()
{
    ufo1_state=2; // Ufo1 exploded
    player_objectives--; // Objective acomplished
    player_points += 200; // 200 score points
    // Change ufo sprite with the explosion one
    ufo1 -> setTexture(txt_player_explosion);
    ufo1 -> setTextureRect(sf::IntRect(97, 65, 393, 420));
    time_respawn_ufo1 = time1->asSeconds() + 2; // 2 seconds as an explosion
    ufo1_direction.y = -1; // With this it does not move
}
void game::ufo2_exploded()
{
    ufo2_state=2; // Ufo2 exploded
    player_objectives--; // Objective acomplished
    player_points += 200; // 200 score points
    // Change ufo sprite with the explosion one
    ufo2 -> setTexture(txt_player_explosion);
    ufo2 -> setTextureRect(sf::IntRect(97, 65, 393, 420));
    time_respawn_ufo2 = time1->asSeconds() + 2; // 2 seconds as an explosion
    ufo2_direction.y = -1; // With this it does not move
}


