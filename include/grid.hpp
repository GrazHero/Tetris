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
extern void GridFill(BlockType type, bool Cosmetic = false);
extern void RowFill(int row, BlockType type, bool Cosmetic = false);
extern void DiagonalFill(int row, BlockType type, bool Cosmetic = false);

#endif
