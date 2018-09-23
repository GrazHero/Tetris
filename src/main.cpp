#include <cstdio>
#include <SDL2/SDL.h>

#include "window.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "grid.hpp"
#include "blocks.hpp"
#include "piece.hpp"
#include "timing.hpp"
#include <ctime>
#include <cmath>
#include <cstdlib>

///These get defined in their respective source files. no reason to do it here.
//SDL_Window* MainWindow;
//SDL_Event* MainEvent;
//SDL_Renderer* MainRenderer;

int main(int argc, char** argv)
{
    //srand(time(NULL));
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      printf("Error\n");
    MainWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowwidth, windowheight, SDL_WINDOW_SHOWN);
    MainEvent = new SDL_Event;
    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_SOFTWARE);

    InitGrid();

//    SpawnPiece();

    bool loop = true;
    while(loop)
    {
        Draw();
        if(HandleEvents() == 1)
            loop = false;
        CalculateDeltaTime();
    }


    delete[] BlockArray;
    SDL_DestroyRenderer(MainRenderer);
    SDL_DestroyWindow(MainWindow);
    SDL_Quit();
    return 0;
}
