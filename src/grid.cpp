#include "grid.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "blocks.hpp"
#include <cstdio>
#include <cmath>

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
  BlockType i = BlockArray[x+y*gridwidth];
  if(i > BLOCKTYPE_MAX)
    return EMPTY;

  return i;
}

void GridFill(BlockType type, bool Cosmetic)
{
  for(int i = 0; i < gridheight*gridwidth; ++i)
  {
    BlockType* b = &(BlockArray[i]);
    if(Cosmetic)
    {
      if(*b == EMPTY || *b >= BLOCKTYPE_MAX) *b = type;
    }
    else *b = type;
  }
}

void RowFill(int row, BlockType type, bool Cosmetic)
{
  for(int i = 0; i < gridwidth; ++i)
  {
    BlockType b = BlockArray[i+row*gridwidth];
    if(Cosmetic)
    {
      if(b == EMPTY || b >= BLOCKTYPE_MAX) SetCell(i, row, type);
    }
    else SetCell(i, row, type);
  }
}
void DiagonalFill(int row, BlockType type, bool Cosmetic)
{
  ///row is a number between 0 and gridwidth+gridheight-1
  ///starting in the top left corner, going all the way down
  ///then going all the way right
  int distance;
  int x;
  if(row >= 0 && row < gridwidth-1)
    distance = row;
  else if(row >= gridwidth-1 && row < gridheight)
    distance = gridwidth-1;
  else
    distance = gridwidth-2-(row-gridheight);

 if(row<gridheight)
    x = 0;
  else
  {
    x = row-(gridheight-1);
    row = gridheight-1;
    /* clamping the row value to gridheight-1
     * we don't need it for any more calculations except
     * for SetCell, which will look for a y value on the grid,
     * not something within this weird width+height indexing thing
     * we have going on. Setting it like this is fine since we don't
     * need its real value again for the rest of the function
     * and it saves us needing to make and another variable for y */
  }

  for(int i = 0; i <= distance; ++i)
  {
    BlockType b = BlockArray[x+(row-i)*gridwidth];
    if(Cosmetic)
    {
      if(b == EMPTY || b >= BLOCKTYPE_MAX) SetCell(x,row-i, type);
    }
    else SetCell(x, row-i, type);

    ++x;
  }
}

