#ifndef GAME_HPP
#define GAME_HPP

#include "piece.hpp"
extern void TestPiece();
extern void InitGame();
extern void Update();
extern void SpeedUp(bool speed, int amount = 0);

extern Piece* CurrentPiece;
extern Piece* NextPiece;

extern int GameSpeed;
extern float RealSpeed;


#endif // GAME_HPP
