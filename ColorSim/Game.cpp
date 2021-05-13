//
//  Game.cpp
//  GameEngine
//
//  Created by Liam on 5/16/20.
//  Copyright © 2020 Liam Semeria. All rights reserved.
//

#include <stdio.h>
#include "Game.h"


SDL_Point Sim::dist(SDL_Point a, SDL_Point b)
{
    // take min of sizex-a, 0-a, b-a
    // IM PRETTY SURE THIS SHIT IS WRONG
    // RETURN TUPLE, MIN, X DIR , Y DIR
    int flag = 0;
    SDL_Point normaldist = {abs(b.x-a.x),abs(b.y-a.y)};
    SDL_Point circulardist = {(int)fmin(abs(0-a.x)+abs(sizex-b.x), abs(0-b.x)+abs(sizey-a.x)),(int)fmin(abs(0-a.y)+abs(sizey-b.y), abs(0-b.y)+abs(sizey-a.y) )};
    int xd = fmin(normaldist.x,circulardist.x);
    int yd = fmin(normaldist.y,circulardist.y);
    if (xd == circulardist.x || yd == circulardist.y) flag = 1;
    return  {(int)sqrt(xd*xd + yd*yd),flag};
}

Sim::Sim()
{
    //start();
}

Sim::~Sim()
{
    end();
}
void Sim::initialize(char* name, int xPos, int yPos, int xSize, int ySize, bool fullscreen)
{
    running = true;
    // change flags based on wether ot not fullscreen is true
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    
    // initialize the SDL framework
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // enumerate displays
        int displays = SDL_GetNumVideoDisplays();
        assert( displays > 1 );  // assume we have secondary monitor

        // get display bounds for all displays
        std::vector< SDL_Rect > displayBounds;
        for( int i = 0; i < displays; i++ ) {
            displayBounds.push_back( SDL_Rect() );
            SDL_GetDisplayBounds( i, &displayBounds.back() );
        }

        // window of dimensions 500 * 500 on secondary monitor
        int x = displayBounds[1].x;
        int y = displayBounds[1].y;
        int w = displayBounds[1].w; //1920
        int h = displayBounds[1].h; // 1080
        sizex = w;
        sizey = h;
        printf("%d %d \n",sizex,sizey);
        // create a window
        window = SDL_CreateWindow(name, x, y, w, h, flags);
    }
    // create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    // create texture
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, sizex, sizey);
    pixels = new Uint32[sizex*sizey];
    memset(pixels, 0, sizex * sizey * sizeof(Uint32));
    //SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch);
}

void Sim::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
            else if (event.key.keysym.sym == SDLK_r)
            {
                memset(pixels, 0, sizex * sizey * sizeof(Uint32));
                start();
            }
                break;
    }
}

// render objects to screen
void Sim::render()
{
    //pixels[1] = 255;
    
    SDL_RenderClear(renderer);
    for (int i = 0; i < brushCount; i++)
    {
        min = INT_MAX;
        // find nearest brush for each brush
        for (int j = 0; j < brushCount; j++)
        {
            //printf("%d %d \n",brushes[j].pos.x,brushes[j].pos.y);
            if (brushes[j].colhex == brushes[i].colhex)
            {
                if (dist(brushes[j].pos, brushes[i].pos).x < min && i != j)
                {
                    distdata = dist(brushes[j].pos, brushes[i].pos);
                    min = distdata.x;
                    closest = brushes[j];
                }
            }
        }
        if (brushCount>1) {
            brushes[i].targpos = closest.pos;
            brushes[i].flag = distdata.y;
        }
        
        brushes[i].update(renderer,pixels);
    }
    SDL_UpdateTexture(texture, NULL, pixels, sizex * sizeof(Uint32));
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

// run the game
void Sim::run()
{
    start();
    while (running)
    {
        handleEvents();
        render();
    }
    end();
}

void Sim::end()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    delete [] pixels;
    SDL_Quit();
}

void Sim::start()
{
    SDL_Color c;
    cols[0] = {200,255,200};
    cols[1] = {255,200,200};
    cols[2] = {200,200,255};
    cols[3] = {255,255,200};
    cols[4] = {255,200,255};
    cols[5] = {200,255,255};
    srand(time(NULL));
    for (int i = 0; i < brushCount; i++)
    {
        c = cols[rand()%6];
        //brushes[0] = Brush(c,200,200);
        brushes[i] = Brush(c,(sizex/2 - spawnsize/2)+rand()%spawnsize,(sizey/2 - spawnsize/2)+rand()%spawnsize,sizex,sizey);
    }
    closest = Brush();
}

