#include "piece.hpp"
#include "grid.hpp"
#include <cstdio>
#include <cmath>
#include <cstdlib>

//Let's try making the pieces only use one bit per block
//Only works with C++14 because of binary literals
unsigned char piece_t[] = {
0b00010000,
0b00111000
};

unsigned char piece_b[] = {
0b00011000,
0b00011000
};

unsigned char piece_s[] = {
0b00011000,
0b00110000
};

unsigned char piece_rs[] = {
0b00110000,
0b00011000
};

unsigned char piece_l[] = {
0b00001000,
0b00111000
};

unsigned char piece_rl[] = {
0b00100000,
0b00111000
};

unsigned char piece_i[] = {
0b00111100,
0b00000000
};

void Piece::SetOrigin(unsigned char& orig, int x)
{
    printf("original origin: %d\n", orig);
    orig = (0b10000000 >> x);
    //printf("new origin: %d\n", orig);
}

void Piece::Spawn()
{
    unsigned char origin = 0b00000000; // for offsetting the piece on the grid

    unsigned char* actualpiece; // will point to one of the global hard coded pieces

    unsigned char result; //for bitwise AND

    const short piecesize = sizeof(unsigned char)*2*8; //16

    switch(m_type)
    {
    case PIECE_T:
        SetOrigin(origin, 3);
        actualpiece = piece_t;

        break;
    case PIECE_B:
        SetOrigin(origin, 4);
        actualpiece = piece_b;
        break;
    case PIECE_S:
        SetOrigin(origin, 3);
        actualpiece = piece_s;
        break;
    case PIECE_RS:
        SetOrigin(origin, 3);
        actualpiece = piece_rs;
        break;
    case PIECE_L:
        SetOrigin(origin, 3);
        actualpiece = piece_l;
        break;
    case PIECE_RL:
        SetOrigin(origin, 3);
        actualpiece = piece_rl;
        break;
    case PIECE_I:
        SetOrigin(origin, 4);
        actualpiece = piece_i;
        break;
    }

    //put the origin into a form I can use
    int neworigin;
    bool loop = true;
    int counter = 1;
    while(loop)
    {
      if(origin << counter >255)
      {
        neworigin = counter-1;
        loop = false;
        //printf("origin: %d\n", origin);
      }else ++counter;
      //printf("====Testing====\n%d\n%d\n%d\n%d\n%d\n%d", origin << 1, origin << 2, origin << 3, origin << 4, origin << 5, origin << 6);
      //loop = false;
    }

    for(int i = 0; i < 2; ++i)
    {
      for(int j = 0; j < piecesize/2; ++j)
      {
        //i/piecesize/2
        //i/8 = 0 when i < 8

        result = actualpiece[i] & (0b10000000 >> j);
        if(result != 0) //if the current bit is 1
        {
          int x = (gridwidth/2)-neworigin+j;
          SetCell(x, i, m_color);
          ClaimCell(x, i);
          //printf("%d, %d, %d\n", gridwidth/2, neworigin, j);
        }
      }
    }
    //m_xpos = (gridwidth/2)-neworigin;
}

void Piece::ClaimCell(int x, int y)
{
  SDL_Point point;
  point.x = x;
  point.y = y;
  ClaimedCells.push_back(point);
  //printf("point x: %d\n", (ClaimedCells.begin())->x);
}

///Returns 1 if the piece is moved successfully, 0 if there's something in the way
int Piece::Move(int xdir, int ydir)
{
  //check if we're gonna hit something
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    int nextx = (*it).x+xdir;
    int nexty = (*it).y+ydir;
    if(nextx >= gridwidth || nextx < 0 || nexty >= gridheight || nexty < 0)
      return 0;
    else if(CheckCell(nextx, nexty) != EMPTY && !CheckClaimed(nextx, nexty))
      return 0;
  }
  //clear the cells we currently occupy
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    SetCell((*it).x, (*it).y, EMPTY);
  }

  //claim cells in the direction we're moving
  //ClaimedCells.clear();
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    SetCell(((*it).x)+xdir, (*it).y+ydir, m_color);
    (*it).x += xdir;
    (*it).y += ydir;
  }
  return 1;
  /*TODO
   *add checks for hitting walls, floor, other blocks*/
}

int Piece::CheckClaimed(int x, int y)
{
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    //printf("Checking %d against %d\n", (*it).x, x);
    //printf("Checking %d against %d\n", (*it).y, y);
    if(((*it).x) == x && ((*it).y) == y)
    {
      //printf("\n\nclaimed\n\n");
      return 1;
    }
  }
   return 0;
}

void Piece::PrintClaimed()
{
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    //printf("\n\n\nx = %d, y = %d", (*it).x, (*it).y);
  }
}
