//
//  brush.hpp
//  GameEngine
//
//  Created by Liam on 5/9/21.
//  Copyright © 2021 Liam Semeria. All rights reserved.
//

#ifndef brush_hpp
#define brush_hpp
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <math.h>

class Brush
{
public:
    long size = 400;
    bool full = false;
    int front = 0;
    SDL_Point windowsize;
    std::vector<SDL_Point> points;
    SDL_Point pos;
    SDL_Point targpos = {960,540};
    SDL_Point chances = {50,50};
    SDL_Color col;
    int flag = 0;
    
    Brush();
    Brush(SDL_Color color, int x, int y, int xsize, int ysize);
    void update(SDL_Renderer *renderer, Uint32 *pixels);
private:
    bool isfree();
    void getchances();
};

#endif /* brush_hpp */
