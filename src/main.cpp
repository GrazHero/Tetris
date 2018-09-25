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
    //srand(time(NULL));
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      return -1;
    MainWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowwidth, windowheight, SDL_WINDOW_SHOWN);
    SDL_SysWMinfo* MainWindowInfo;

    SDL_VERSION(&(MainWindowInfo->version));
    SDL_GetWindowWMInfo(MainWindow, MainWindowInfo);
    MainWindowHandle = MainWindowInfo->info.win.window;

    MainEvent = new SDL_Event;
    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_SOFTWARE);

    InitGrid();

//    SpawnPiece();

    while(MainLoop)
    {
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
