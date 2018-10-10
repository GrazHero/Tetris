#include "game.hpp"
#include "piece.hpp"
#include "timing.hpp"
#include <cstdlib>
#include <cstdio>
#include <iostream>

Piece* CurrentPiece;
Piece* NextPiece;
#define DEFAULT_GAMESPEED 4
int GameSpeed = 4;//change this to not be hard coded
bool GamePaused = false;
int OldGameSpeed;
bool Speeding;
float RealSpeed = 1000.0/(0.5*GameSpeed);//the threshhold of milliseconds before moving the block down
float lastms = 0;

void TestPiece()
{
    BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
    PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX-1) ); // random piece
    CurrentPiece = new Piece(piece, color);
    CurrentPiece->Spawn();
    printf("Piece Spawned\n");
}

void InitGame()
{
  BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
  PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX) ); // random piece
  NextPiece = new Piece(piece, color);
  color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
  piece = (PieceType)(rand()%(PIECETYPE_MAX) ); // random piece
  CurrentPiece = new Piece(piece, color);
  CurrentPiece->Spawn();
}

void Update()
{
  if(!GamePaused) // this is bad practice. I should be using a state machine or something.
  {               // but i'm not sticking to one style for this game, I want to try everything
    if(mscount - lastms >= RealSpeed)
    {
      lastms = mscount;
      if(!CurrentPiece->Move(0, 1))
      {
        BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
        PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX)); // random piece

        delete CurrentPiece;

        //CheckLines();

        CurrentPiece = NextPiece;
        NextPiece = new Piece(piece, color);
        CurrentPiece->Spawn();
      }
    }
  }
}

void SpeedUp(bool speed, int amount)
{
if(!GamePaused)
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
}

void TogglePause()
{
  GamePaused = !GamePaused;
  if(GamePaused)
  {
    std::cout << "paused\n";
  }
  else
  {
    std::cout << "unpaused\n";
  }
}
