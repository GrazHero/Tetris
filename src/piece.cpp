#include "piece.hpp"
#include "grid.hpp"
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>

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
    //printf("original origin: %d\n", orig);
    orig = (0b10000000 >> x);
    //printf("new origin: %d\n", orig);
}

//fun, time to try/catch every vector function
int Piece::Spawn()
{
    ClaimedCells.reserve(9);


    unsigned char origin = 0b00000000; // for offsetting the piece on the grid

    m_centerIndex = 0;

    unsigned char* actualpiece; // will point to one of the global hard coded pieces

    unsigned char result; //for bitwise AND

    const short piecesize = sizeof(unsigned char)*2*8; //16

    switch(m_type)
    {
    case PIECE_T:
        SetOrigin(origin, 3);
        actualpiece = piece_t;
        m_centerOffset = {3, 1};
        break;
    case PIECE_B:
        SetOrigin(origin, 4);
        actualpiece = piece_b;
        m_centerOffset = {0, 0};
        break;
    case PIECE_S:
        SetOrigin(origin, 3);
        actualpiece = piece_s;
        m_centerOffset = {3, 0};
        break;
    case PIECE_RS:
        SetOrigin(origin, 3);
        actualpiece = piece_rs;
        m_centerOffset = {3, 0};
        break;
    case PIECE_L:
        SetOrigin(origin, 3);
        actualpiece = piece_l;
        m_centerOffset = {3, 1};
        break;
    case PIECE_RL:
        SetOrigin(origin, 3);
        actualpiece = piece_rl;
        m_centerOffset = {3, 1};
        break;
    case PIECE_I:
        SetOrigin(origin, 4);
        actualpiece = piece_i;
        m_centerOffset = {3, 0};
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
          if(!CheckCell(x, i))
             SetCell(x, i, m_color);
          else return 0;

          ClaimCell(x, i);

          if(j == m_centerOffset.x && i == m_centerOffset.y)
          {
            m_centerIndex = ClaimedCells.size() -1;//the distance from the back of the vectorwhere the "center piece" is
          }
          //printf("%d, %d, %d\n", gridwidth/2, neworigin, j);
        }
      }
    }
    try
    {
    m_centerCell = &ClaimedCells.at(ClaimedCells.size()-1-m_centerIndex);
    }
    catch(...)
    {
      /* Found the error. Turns out I was neglecting to define the m_centerOffset variable for the 4x4 pieces.
       * I thought it was unnecessary because I don't need to rotate them. Turns out I was later using that
       * variable irresponsibly as an argument to ClaimedCells.at(). I never initialize it for 4x4 blocks,
       * so it was essentially using a garbage number as an index for the vector. Then it would throw an
       * out of range exception basically every time a 4x4 block spawned. Weird how it only crashes the program
       * selectively. GDB seems to catch this exception all the time, and then unhelpfully terminates the program.
       * Glad I got that sorted out. Never EVER leave variables uninitialized. */
      std::cerr << "last m_centercell\n";
      std::cerr << "index is " << m_centerIndex << "\n";
      std::cerr << "size is " << ClaimedCells.size() << "\n";
    }

    return 1;
}

void Piece::ClaimCell(int x, int y)
{
  SDL_Point point;
  point.x = x;
  point.y = y;

  ClaimedCells.insert(ClaimedCells.begin(), point);

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
    if(CheckCell(nextx, nexty) != EMPTY && !CheckClaimed(nextx, nexty))
      return 0;
  }

  ClearCells();

  //claim cells in the direction we're moving
  //ClaimedCells.clear();
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    SetCell(((*it).x)+xdir, (*it).y+ydir, m_color);
    (*it).x += xdir;
    (*it).y += ydir;
  }
  return 1;
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
    //printf("\nx = %d, y = %d", (*it).x, (*it).y);
  }
  printf("\n");
}

int Piece::Rotate(int dir) //dir = 1 for counterclockwise, -1 for clockwise. returns 1 if rotation is successful, otherwise 0
{
    //x = y
    //y = -x
    /*
    ..X..3
    ..X..4
    ..X..5
    ..X..6
    34567
    */
  if(m_type == PIECE_B)
    return 1; //no need to rotate this piece

  int originalSize = ClaimedCells.size();
  int inserts = 0;
  for(int i = 0; i < originalSize; ++i) //using iterators would just make this harder
  {
    /* In hindsight, I could have done this like I did the Piece::Move() function.*/

    //Reading back to front so the rotated blocks get loaded in the original order
    int cellx, celly;

    cellx = ClaimedCells.at(ClaimedCells.size()-1-i).x;
    celly = ClaimedCells.at(ClaimedCells.size()-1-i).y;

    int xdifference, ydifference, nextx, nexty;
    xdifference = cellx - m_centerCell->x;
    ydifference = celly - m_centerCell->y;
    nextx = m_centerCell->x + dir*ydifference;
    nexty = m_centerCell->y - dir*xdifference;


    //There's a problem with this
    if(nextx >= gridwidth || nextx < 0 || nexty >= gridheight || nexty < 0)
      goto _RESTORE; // goto :^)
    if(CheckCell(nextx, nexty) != EMPTY && !CheckClaimed(nextx, nexty))
      goto _RESTORE;




    SDL_Point p = {nextx, nexty};
    //std::cout << "before: " << m_centerCell->x <<std::endl;
    ClaimedCells.insert(ClaimedCells.begin(), p);
    ++inserts;
    m_centerCell = &ClaimedCells.at(ClaimedCells.size()-1-m_centerIndex);//Set this again since vector::insert will invalidate it
    //std::cout << "after: " << m_centerCell->x <<std::endl;
  }
  //if we rotated without error, resize the array to truncate the old values, then clean them off of the global grid array
  ClearCells();
  ClaimedCells.resize(4);
  SetAllCells();
  m_centerCell = &ClaimedCells.at(ClaimedCells.size()-1-m_centerIndex);
  //std::cout << m_centerIndex << std::endl;
  return 1;
_RESTORE:
  //if we ran into a problem, we need to undo what we did to the vector
  if(inserts > 0) ClaimedCells.erase(ClaimedCells.begin(), ClaimedCells.begin()+inserts);
  m_centerCell = &ClaimedCells.at(ClaimedCells.size()-1-m_centerIndex);
  //std::cout << "_RESTORE\n";
  return 0;
}

void Piece::ClearCells()
{
  //clear the cells we currently occupy
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    SetCell((*it).x, (*it).y, EMPTY);
  }
}

void Piece::SetAllCells()
{
  int i = 0;
  for(auto it = ClaimedCells.begin(); it != ClaimedCells.end(); ++it)
  {
    SetCell((*it).x, (*it).y, m_color);
    //printf("%d, %d!\n", (*it).x, (*it).y);
  }
}

bool Piece::CheckCenterCell(int x, int y)
{
  if(m_centerCell->x == x && m_centerCell->y == y)
    return true;
  else return false;
}
