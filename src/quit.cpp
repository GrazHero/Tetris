#include "quit.hpp"
#include "main.hpp"
#include "window.hpp"
#include <cstdlib>
#include <windows.h>

void QuitGame()
{

}

void Killswitch(const char* errmsg)
{
  MessageBox(MainWindowHandle,errmsg,NULL,NULL);
  exit(-1);
}
