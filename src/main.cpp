#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include "window.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "grid.hpp"
#include "blocks.hpp"
#include "piece.hpp"
#include "timing.hpp"
#include "main.hpp"
#include "game.hpp"
#include <ctime>
#include <cmath>
#include <cstdlib>

///These get defined in their respective source files. no reason to do it here.
//SDL_Window* MainWindow;
//SDL_Event* MainEvent;
//SDL_Renderer* MainRenderer;
bool MainLoop = true;

int main(int argc, char** argv)
{
    srand(time(NULL));
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      return -1;
    MainWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowwidth, windowheight, SDL_WINDOW_SHOWN);
    SDL_SysWMinfo* MainWindowInfo;

    SDL_VERSION(&(MainWindowInfo->version));
    SDL_GetWindowWMInfo(MainWindow, MainWindowInfo);
    #ifdef WINDOWS_COMPILE
    /*I hate to put a preprocessor #if right in the open like this. I wrote windows specific code without
     *thinking very much. I'll try to avoid making this a hassle. From now on I'll have functions obfuscate these
     *checks so they don't clutter stuff. WINDOWS_COMPILE is defined in window.hpp (no relation to the OS. Very
     *confusing and dumb, I know) because that's where it is first needed as of now, because I need to get the
     *HWND if we're on windows. That was rather shortsighted, OS checking should be it's own thing, not tethered
     *to one specific subset of why we might want to block out certain code depending on the OS we're compiling on/for
     */
    MainWindowHandle = MainWindowInfo->info.win.window;
    #endif // WINDOWS_COMPILE
    MainEvent = new SDL_Event;
    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_SOFTWARE);

    InitGrid();
    InitGame();

    while(MainLoop)
    {
        Update();
        Draw();
        if(HandleEvents() == 1)
            MainLoop = false;
        CalculateTime();
    }


    SDL_DestroyRenderer(MainRenderer);
    SDL_DestroyWindow(MainWindow);
    SDL_Quit();
EOP:
    delete[] BlockArray;
    return 0;
}
