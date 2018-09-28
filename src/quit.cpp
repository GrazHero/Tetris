#include "quit.hpp"
#include "main.hpp"
#include "window.hpp"
#include <cstdlib>

#ifdef WINDOWS_COMPILE

#include <windows.h>

#endif // defined

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
