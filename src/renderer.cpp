#include "renderer.hpp"
#include "window.hpp"
#include "grid.hpp"
#include "blocks.hpp"
#include "graph.hpp"
#include "coloreffects.hpp"
#include <cstdio>

SDL_Renderer* MainRenderer;

void Draw()
{
    ///Black Background
    SDL_SetRenderDrawColor(MainRenderer, 35, 0, 0, 0);
    SDL_RenderClear(MainRenderer);
    ///Grid
    DrawBlocks();
    GridDraw();
    SDL_RenderPresent(MainRenderer);
}
