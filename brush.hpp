//
//  brush.hpp
//  GameEngine
//
//  Created by Liam on 5/9/21.
//  Copyright © 2021 Liam Semeria. All rights reserved.
//

#ifndef brush_hpp
#define brush_hpp
#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <math.h>

class Brush
{
public:
    long size = 300;
    bool full = false;
    int front = 0;
    SDL_Point windowsize;
    std::vector<SDL_Point> points;
    SDL_Point pos;
    SDL_Point targpos = {960,540};
    SDL_Point chances = {50,50};
    Uint32 colhex;
    int flag = 0;
    
    Brush();
    Brush(SDL_Color color,int x, int y, int xsize, int ysize);
    void update(SDL_Renderer *renderer, Uint32 *pixels);
private:
    bool isfree();
    void getchances();
    Uint32 neighborcolor(Uint32 *pixels, int x, int y);
};

#endif /* brush_hpp */
