#include "quit.hpp"
#include "main.hpp"
#include "window.hpp"
#include "game.hpp"
#include "grid.hpp"
#include <cstdlib>

#ifdef WINDOWS_COMPILE

#include <windows.h>

#endif // defined

#include "text.hpp"

void QuitGame()
{

}

void Killswitch(const char* errmsg)
{
  #ifdef WINDOWS_COMPILE
  MessageBox(MainWindowHandle,errmsg,NULL,NULL);
  #endif
  exit(-1);
}

void LoseGame()
{
    Lose = true;
    GridFill((BlockType)0xFF0000, false);

    CurrentPiece = nullptr;
}
