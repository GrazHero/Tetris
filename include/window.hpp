#ifndef WINDOW_HPP
#define WINDOW_HPP

#if defined (_WIN32) || defined (_WIN64)

#define WINDOWS_COMPILE
#include <windows.h>

#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

extern const int windowwidth;
extern const int windowheight;

extern SDL_Window* MainWindow;
extern SDL_SysWMinfo* MainWindowInfo;
#ifdef WINDOWS_COMPILE
extern HWND MainWindowHandle;
#endif // WINDOWS

#endif // WINDOW_HPP
