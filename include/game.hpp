#ifndef GAME_HPP
#define GAME_HPP

#include "piece.hpp"
extern void TestPiece();
extern void InitGame();
extern void Update();
extern void SpeedUp(bool speed, int amount = 0);
extern void TogglePause();

extern Piece* CurrentPiece;
extern Piece* NextPiece;

extern int GameSpeed;
extern bool GamePaused;
extern float RealSpeed;
extern int RowsCleared;
extern int TotalScore;
extern bool Lose;


#endif // GAME_HPP
