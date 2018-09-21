#ifndef PIECE_HPP
#define PIECE_HPP

#include "blocks.hpp"

extern void SpawnPiece();

enum PieceType {
    PIECE_T,
    PIECE_B,
    PIECE_S,
    PIECE_RS,
    PIECE_L,
    PIECE_RL,
    PIECE_I,
    PIECETYPE_MAX
};

extern unsigned char piece_t[];
extern unsigned char piece_b[];
extern unsigned char piece_s[];
extern unsigned char piece_rs[];
extern unsigned char piece_l[];
extern unsigned char piece_rl[];
extern unsigned char piece_i[];

#endif
