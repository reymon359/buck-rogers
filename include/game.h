#pragma once

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class game
{
public:
    // Constructor
    game(Vector2f dimension, std::string title);

    void load_resources(); /// Loads the resources, sprites, textures, etc.
    void gameLoop(); /// Main game loop that controls the game states and other important functions.
    void start_game(); /// Starts the game or restarts it if the player has crashed and still has lifes.
    void end_game(); /// Called when the player has no more lifes after crashing.

    void process_events();
    void process_collisions();
    void player_crashed();
    void move_water();
    void spawn_rocks();
    void move_rocks();
    void draw();

private:
    // Game
    RenderWindow * window1;
    Event * event1;
    int game_status;
    Texture * txt_title;
    Sprite * spr_title;

    // Time
    Clock * clock1;
    Time * time1;
    float  time2;
    float gameSpeed;
    float  time_water;

    // Background
    Texture * txt_background;
    Sprite * spr_water;
    Sprite * spr_islands;
    Sprite * spr_islands2;
    Sprite * spr_sky;

    // Player
    Texture * txt_player;
    Texture * txt_player_explosion;
    Sprite * spr_player;
    int vel_player;
    int player_points;
    int player_objectives; /// The game objectives. Accomplished passing trough rocks and reaching x distance.
    Font * font_objectives;
    Text * text_objectives;
    int player_lifes;
    Texture * txt_life;
    Sprite * spr_life1, * spr_life2, * spr_life3;

    // Rocks
    Texture * txt_rock;
    RectangleShape * rock1;
    RectangleShape * rockspace;
    RectangleShape * rock2;
    int rockSize;
    int randomSize;
    int randomSpawn;
    int pass_between;
    Vector2i rock_pos;

    // Font
    Font * font1;
    Text * text_score;
    Text * text_time;
//    Vector2i sprite_division;
//    Vector2i actual_frame;
//    int sprite_flip;



    bool game_over = false;
    int fps;
};

#endif // GAME_H
