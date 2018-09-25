#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

extern const int windowwidth;
extern const int windowheight;

extern SDL_Window* MainWindow;
extern SDL_SysWMinfo* MainWindowInfo;
extern HWND MainWindowHandle;

#endif // WINDOW_HPP
