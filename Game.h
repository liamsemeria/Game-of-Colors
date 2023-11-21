//
//  Game.h
//  GameEngine
//
//  Created by Liam on 5/16/20.
//  Copyright © 2020 Liam Semeria. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <SDL.h>
#include "brush.hpp"
#include <iostream>
#include <vector>
#include <cmath>

class Sim
{
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Brush brushes[300];
    int brushCount = 300;
    SDL_Color cols[6];
    int min;
    Brush closest;
    SDL_Point distdata;
    int sizex,sizey;
    int spawnsize = 800;
    Uint32 *pixels = nullptr;
    int pitch = 0;
public:
    Sim();
    ~Sim();
    // basic functions to run and uodate using the SDL framework
    void initialize(char* name, int xPos, int yPos, int xSize, int ySize, bool fullscreen);
    void handleEvents();
    void render();
    void run();
    void start();
    void end();
private:
    SDL_Point dist(SDL_Point a, SDL_Point b);
};

#endif /* Game_h */
