#include "game.hpp"
#include "piece.hpp"
#include "timing.hpp"
#include "grid.hpp"
#include "blocks.hpp"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>

Piece* CurrentPiece;
Piece* NextPiece;
#define DEFAULT_GAMESPEED 4
int GameSpeed = 4;//change this to not be hard coded
bool GamePaused = false;
int OldGameSpeed;
bool Speeding;
int TotalScore = 0;
int RowsCleared = 0;
bool Lose = false;
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
    if(!Lose)
    {
      if(mscount - lastms >= RealSpeed)
      {
        lastms = mscount;
        if(!CurrentPiece->Move(0, 1))//it will return 0 if we hit something. meaning it's time to spawn the next
        {
          BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
          PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX)); // random piece

          delete CurrentPiece;

          CheckLines();

          CurrentPiece = NextPiece;
          NextPiece = new Piece(piece, color);
          if(!CurrentPiece->Spawn())//if it returns 0, that means it tried spawning on top of another piece.
          {                         //in other words, begin the lose state
            Lose = true;
            GridFill((BlockType)0xFF0000);
            CurrentPiece = nullptr;
          }//
        }//if(!CurrentPiece->Move(0, 1))
      }//if(mscount - lastms >= RealSpeed)
    }//if(!Lose)
    else
    {
      //Put Lose State stuff here
      //Maybe move it to a different file later if it gets too big
      for(int i = 0; i < gridheight+gridwidth; ++i)
      {
        int red = 0x7F - floor(50*sin(mscount/(500)-i));
        int green = 0x7f;//finish this. i want to make the color interpolate between red green and blue
        DiagonalFill(i, (BlockType)(red<<16));
      }
    }
  }//if(!GamePaused)
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
