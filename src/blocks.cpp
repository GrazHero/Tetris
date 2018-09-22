#include "blocks.hpp"
#include "grid.hpp"
#include "renderer.hpp"
#include "cmath"
#include "window.hpp"
#include <cstdlib>

BlockType* BlockArray;


SDL_Rect blockrect;

SDL_Color blockcolor;

void SetColor(int newr, int newg, int newb, int newa = 255, SDL_Color* color = &blockcolor)
{
    color->r = newr;
    color->g = newg;
    color->b = newb;
    color->a = newa;
}

void DrawBlocks()
{
    int r, g, b;
    int x=0, y=0;
    for(int i = 0; i < gridheight*gridwidth; ++i)
    {
        //i = x+w*y
        //x = i-w*y
        //y = (i-x)/w
        //x = (i-gridwidth*y);
        //y = ((i-x)/gridwidth);
        blockrect = {x*cellsize, y*cellsize, cellsize, cellsize};
        switch(BlockArray[i])
        {
        case EMPTY:
            SetColor(0, 0, 0, 0);
            break;
        case RED:
            SetColor(255, 0, 0);
            break;
        case ORANGE:
            SetColor(255, 69, 0);
            break;
        case YELLOW:
            SetColor(0xff, 0xff, 0);
            break;
        case GREEN:
            SetColor(0, 128, 0);
            break;
        case BLUE:
            SetColor(0, 128, 128);
            break;
        case PURPLE:
            SetColor(106, 90, 205);
            break;
        }

        SDL_SetRenderDrawColor(MainRenderer, blockcolor.r, blockcolor.g, blockcolor.b, blockcolor.a);
        SDL_Rect testrect = {50, 50, 50, 50};
        if(i==50)
        {
            //printf("testrect: %d, %d, %d, %d\n", testrect.x, testrect.y, testrect.w, testrect.h);
            //printf("blockrect: %d, %d, %d, %d\n", blockrect.x, blockrect.y, blockrect.w, blockrect.h);
        }
        SDL_RenderFillRect(MainRenderer, &blockrect);
        //Move X and Y
        ++x;
        if((i+1)%gridwidth==0)
        {
            //printf("MOD!\n");
            x=0;
            ++y;
        }
    }
}

void PlaceBlockWithMouse(int x, int y)
{
    if(x>windowwidth || y>windowheight)
        return;
    int gridx = floor(x/cellsize);
    int gridy = floor(y/cellsize);

    BlockType type = BlockType(rand() % (BLOCKTYPE_MAX-1)+1);
    SetCell(gridx, gridy, type);
}
