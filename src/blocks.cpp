#include "blocks.hpp"
#include "grid.hpp"
#include "renderer.hpp"
#include "cmath"
#include "window.hpp"
#include <cstdlib>
#include <cstdio>
#include "piece.hpp"
#include "game.hpp"
#include <iostream>

BlockType* BlockArray;


SDL_Rect blockrect;

SDL_Color blockcolor;

void SetColor(int newr, int newg, int newb, int newa, SDL_Color* color)
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
        default:
          /*I kinda screwed myself over with this system.
           *The way it is now, every color must be hard coded.
           *I thought of a workaround that should be good enough for
           *at least making some neat color effects.
           *Since the only data contained in each cell is an int (enum for my hard coded colors),
           *I'll just have every value for the enum OTHER than the few hard coded ones be interpreted
           *as carying a 24-bit rgb value. Basically every color except for from zero to 0x000006 should
           *work for this. I'll be using the lower 24 bits of the (hopefully) 32 bit enumerator.
           *I guess I'm now making assumptions about the size of an int (enum) on any given
           *system, but good enough I guess*/
           int bitmaskR, bitmaskG, bitmaskB;
           bitmaskR = (0xFF0000 & BlockArray[i]) >> 16;
           bitmaskG = (0x00FF00 & BlockArray[i]) >> 8;
           bitmaskB = (0x0000FF & BlockArray[i]);
           SetColor(bitmaskR, bitmaskG, bitmaskB);
           break;
        }
        //debug
        //if(CurrentPiece->CheckCenterCell(x, y)) SetColor(255, 255, 255);
        SDL_SetRenderDrawColor(MainRenderer, blockcolor.r, blockcolor.g, blockcolor.b, blockcolor.a);
        SDL_Rect testrect = {50, 50, 50, 50};
        if(i==50)
        {
            //printf("testrect: %d, %d, %d, %d\n", testrect.x, testrect.y, testrect.w, testrect.h);
            //printf("blockrect: %d, %d, %d, %d\n", blockrect.x, blockrect.y, blockrect.w, blockrect.h);
        }
        if(BlockArray[i] != EMPTY)SDL_RenderFillRect(MainRenderer, &blockrect);
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
    BlockType cell = CheckCell(gridx, gridy);
    printf("%d\n", cell);
}

void ClearRow(int y)
{
  for(int i = 0; i < gridwidth; ++i)
  {
    SetCell(i, y, EMPTY);
  }
}

void MoveRow(int row, int distance)
{
  ///*Use carefully - Will not check boundaries or intersection with other blocks :^)*///
  for(int i = 0; i < gridwidth; ++i)
  {
    if(CheckCell(i, row))//Make sure we're not moving empty blocks. I know I just said I wasn't being careful
    {
      if(!(row + distance >= gridheight) || !(row + distance < 0))
        SetCell(i, row + distance, CheckCell(i, row));
    }
  }
  ClearRow(row);
}

int CheckLines()
{
  int numcleared = 0;
  int clearedrows[gridheight] = {-1};//array for holding the y value of every row we clear.  It should never be larger than gridheight
  //First, clear any rows we can
  for(int i = gridheight-1; i>=0; --i)
  {
    unsigned char sum = (char)0;
    for(int j = 0; j <gridwidth; ++j)
    {
      if(CheckCell(j, i)) ++sum;
    }
    if(sum==(unsigned char)gridwidth)//if every every cell of the row is occupied
    {
      ClearRow(i);
      clearedrows[numcleared] = i;

      ++numcleared;
    }
  }//end clearing rows

  //Moving down
  int n = 1;
  for(int i = clearedrows[0]-1; i >=0; --i)
  {
    /*numcleared[0] should always be the lowest row we cleared, so there's no need to deal with anything below it
     *That's why i starts there and counts down
     *Probably a bit of a lost cause to worry about optimization at this point, but whatever*/
    /* n will be the number of rows to move down.
     * in other words, the number of CLEARED rows BELOW the current one */
    MoveRow(i, n);
    if(i==clearedrows[n]) ++n;
    /*God I hope this works*/
  }

  RowsCleared += numcleared;//Update gloabal number of cleared rows
  TotalScore += numcleared*100+floor((numcleared*100)*0.5f);
}
