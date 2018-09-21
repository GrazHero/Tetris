#include "piece.hpp"
#include <cstdio>

//Let's try making the pieces only use one bit per block
//Only works with C++14
unsigned char piece_t[] = {
0b00111000,
0b00010000
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
};

void SetOrigin(unsigned char* orig, int x, int y)
{
    orig[y] = 0b10000000 >> x;
}

void SpawnPiece(PieceType type)
{
    unsigned char origin[] = {
    0b00000000,
    0b00000000
    };
    unsigned char rotation;
    switch(type)
    {
    case PIECE_T:
        SetOrigin(origin, 2, 1);
        break;
    case PIECE_B:
        SetOrigin(origin, 3, 1);
        break;
    case PIECE_S:
        SetOrigin(origin, 2, 1);
        break;
    case PIECE_RS:
        SetOrigin(origin, 3, 1);
        break;
    case PIECE_L:
        SetOrigin(origin, 4, 0);
        break;
    case PIECE_RL:
        SetOrigin(origin, 2, 0);
        break;
    case PIECE_I:
        SetOrigin(origin, 2, 0);
        break;
    }
}
