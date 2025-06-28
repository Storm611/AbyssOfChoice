#include <iostream>
#include <limits> 
#include "Shop.h"
#include "Player.h"
#include "levelManager.h"
#include "Game.h"
#include <cstdlib> 

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else

#endif

int main() {
    Game game;
    game.Play();
    return 0;
}