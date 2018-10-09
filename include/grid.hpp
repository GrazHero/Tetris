#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>
#include "blocks.hpp"

extern void GridDraw();
extern void InitGrid();
extern void Click(const SDL_MouseButtonEvent); //Just for testing
extern void SetCell(int x, int y, BlockType type);
extern BlockType CheckCell(int x, int y);
extern const int cellsize;
extern const int gridwidth, gridheight;

#endif
