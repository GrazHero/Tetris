#include "window.hpp"

SDL_Window* MainWindow;
SDL_SysWMinfo* MainWindowInfo;
#ifdef WINDOWS_COMPILE
HWND MainWindowHandle;
#endif
const int windowwidth = 300;
const int windowheight = 600;
