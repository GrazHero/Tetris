#include "game.hpp"
#include "piece.hpp"
#include "timing.hpp"
#include <cstdlib>
#include <cstdio>

Piece* CurrentPiece;
Piece* NextPiece;
int GameSpeed = 4;//change this to not be hard coded
int OldGameSpeed;
bool Speeding;
float RealSpeed = 1000.0/(0.5*GameSpeed);//the threshhold of milliseconds before moving the block down
float lastms = 0;

void TestPiece()
{
    BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
    PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX-1) +1); // random piece
    CurrentPiece = new Piece(piece, color);
    CurrentPiece->Spawn();
    printf("Piece Spawned\n");
}

void InitGame()
{
  BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
  PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX-1) ); // random piece
  NextPiece = new Piece(piece, color);
  color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
  piece = (PieceType)(rand()%(PIECETYPE_MAX-1) ); // random piece
  CurrentPiece = new Piece(piece, color);
  CurrentPiece->Spawn();
}

void Update()
{
  if(mscount - lastms >= RealSpeed)
  {
    lastms = mscount;
    if(!CurrentPiece->Move(0, 1))
    {
      BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
      PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX-1)); // random piece

      delete CurrentPiece;

      CheckLines();

      CurrentPiece = NextPiece;
      NextPiece = new Piece(piece, color);
      CurrentPiece->Spawn();
    }
  }
}

void SpeedUp(bool speed, int amount)
{
  if(!Speeding && speed)
  {
    OldGameSpeed = GameSpeed;
    GameSpeed = amount;
    RealSpeed = 1000.0/(0.5*GameSpeed);
    Speeding = true;
  }
  if(Speeding && !speed)
  {
    GameSpeed = OldGameSpeed;
    RealSpeed = 1000.0/(0.5*GameSpeed);

    Speeding = false;
  }
}
