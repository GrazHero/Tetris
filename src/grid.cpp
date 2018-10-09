#include "grid.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "blocks.hpp"
#include <cstdio>

const int cellsize = 30;
const int gridwidth = windowwidth/cellsize;
const int gridheight = windowheight/cellsize;

void GridDraw()
{
    ///I realize only after writing this function that I kinda messed up. Now I have the grid drawing completely independent of the\
       actual array in code. Don't ever do anything like this. Make everything function based on the SAME data.
    SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 255);

    int i = 0;
    ///Horizontal lines
    for(i = 0; i <= gridheight; ++i)
    {
        //if(i!=windowheight/cellsize)
            SDL_RenderDrawLine(MainRenderer, 0, i*cellsize, windowwidth, i*cellsize);
        //else SDL_RenderDrawLine(MainRenderer, 0, i*cellsize-1, windowwidth, i*cellsize-1);
    }
    ///Vertical lines
    for(i = 0; i <= gridwidth; ++i)
    {
        //if(i!=windowwidth/cellsize)
            SDL_RenderDrawLine(MainRenderer, i*cellsize, 0, i*cellsize, windowheight);
        //else SDL_RenderDrawLine(MainRenderer, i*cellsize-1, 0, i*cellsize-1, windowheight);
    }
}

void InitGrid()
{
    BlockArray = new BlockType[gridwidth*gridheight];
    for(int i = 0; i < gridwidth*gridheight; ++i)
    {
        BlockArray[i] = EMPTY;
    }
}

void SetCell(int x, int y, BlockType type)
{
    BlockArray[x+y*gridwidth] = type;
}

void Click(const SDL_MouseButtonEvent event)
{
    printf("%d, %d, %d\n", event.x, event.y, event.button);

    if(event.button == 1)
    {
        PlaceBlockWithMouse(event.x, event.y);
    }
}

BlockType CheckCell(int x, int y)
{
  return BlockArray[x+y*gridwidth];
}
