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

void SetOrigin(unsigned char& orig, int x)
{
    printf("original origin: %d\n", orig);
    orig = (0b10000000 >> x);
    printf("new origin: %d\n", orig);
}

void SpawnPiece(PieceType type, BlockType color)
{
    unsigned char origin = 0b00000000; // for offsetting the piece on the grid

    unsigned char* actualpiece; // will point to one of the global hard coded pieces

    unsigned char result; //for bitwise AND

    const short piecesize = sizeof(unsigned char)*2*8; //16

    switch(type)
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
        printf("origin: %d\n", origin);
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
          SetCell(x, i, color);
          printf("%d, %d, %d\n", gridwidth/2, neworigin, j);
        }
      }
    }
}
