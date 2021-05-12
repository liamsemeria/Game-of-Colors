//
//  main.cpp
//  GameEngine
//
//  Created by Liam on 5/16/20.
//  Copyright © 2020 Liam Semeria. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
/*
 Cube Artists
 
    cubes start and find a mate, using A* pathfinding to the first cube it sees
    when they go next to each other they combine colors, and create a child
    the parents stay in place
    the new cube searches for a new mate, if there are none, it looks at parents not its own
    
    
 
 */
Sim *g = nullptr;

int main(int argc, const char * argv[]) {
    // insert code here...
    g = new Sim();
    char* t = "Color Evolution";
    g->initialize(t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 750, true);
    g->run();
    return 0;
}
