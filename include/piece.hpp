#ifndef PIECE_HPP
#define PIECE_HPP

#include "blocks.hpp"
#include <vector>
#include <SDL2/SDL.h>

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

class Piece
{
public:
  Piece(PieceType type, BlockType color) : m_type(type), m_color(color), m_rotation(0) {};
  int Move(int xdir, int ydir);
  void Spawn();
  void PrintClaimed();
  int CheckClaimed(int x, int y);
private:
  PieceType m_type;
  BlockType m_color;
  int m_xpos;
  int m_ypos;
  int m_rotation;

  void SetOrigin(unsigned char& orig, int x);
  void ClaimCell(int x, int y);

  std::vector<SDL_Point> ClaimedCells;
};

extern void SpawnPiece(PieceType, BlockType);
#endif
