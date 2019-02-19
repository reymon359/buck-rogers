// Buck Rogers
// Author Ramon Morcillo @reymon359

#include <SFML/Graphics.hpp>

#include <game.h>

using namespace sf;

int main(int argc, char * args[])
{
    game * match1;

    match1 = new game({800,600}, "buck rogers");

    return 0;
}
