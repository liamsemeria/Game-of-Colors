//
//  brush.cpp
//  GameEngine
//
//  Created by Liam on 5/9/21.
//  Copyright © 2021 Liam Semeria. All rights reserved.
//
#include "brush.hpp"

// chance it is -1
int random_sign(int chance)
{
    return rand()%10>=chance ? 1 : -1;
}

void Brush::getchances()
{
    // calculate movement chances
    // calculate chances based on circular TODO
    if (flag == 0)
    {
        if (targpos.x == pos.x) chances.x =5;
        else if (targpos.x>pos.x) chances.x=6;
        else chances.x=4;
        
        if (targpos.y == pos.y) chances.y =5;
        else if (targpos.y>pos.y) chances.y=6;
        else chances.y=4;
    }
    else
    {
        if (targpos.x == pos.x) chances.x =5;
        else if (targpos.x>pos.x) chances.x=4;
        else chances.x=6;
        
        if (targpos.y == pos.y) chances.y =5;
        else if (targpos.y>pos.y) chances.y=4;
        else chances.y=6;
    }
}

bool Brush::isfree()
{
    for (int i = 0; i < points.size();i++)
    {
        if ((points[i].x == pos.x)&&(points[i].y == pos.y)) return false;
    }
    return true;
}

Brush::Brush()
{
    pos = {960,450};
    targpos = {960,540};
}

Brush::Brush(SDL_Color color,int x,int y, int xsize,int ysize)
{
    pos = {x,y};
    col = color;
    targpos = {xsize/2,ysize/2};
    windowsize = {xsize,ysize};
}

void Brush::update(SDL_Renderer *renderer, Uint32 *pixels)
{
    // calculate movement chances
    getchances();
    while (!isfree())
    {
        if (rand()%2) pos.x += random_sign(chances.x);
        else pos.y += random_sign(chances.y);
    }
    // circular display
    if (pos.x < 0) pos.x = windowsize.x-1;
    if (pos.x > windowsize.x) pos.x = 1;
    if (pos.y < 0) pos.y = windowsize.y-1;
    if (pos.y > windowsize.y) pos.y = 1;
    
    // detect if full
    if (size <= points.size())
        full = true;
    // add a new point
    if (full){
        if (front >= size) front = 0;
        points[front] = {pos.x,pos.y};
        front++;
    }
    else points.push_back({pos.x,pos.y});
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i].x == pos.x && points[i].y == pos.y)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        else SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 0);
        SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
    }

}

