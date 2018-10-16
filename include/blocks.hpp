#ifndef BLOCKS_HPP
#define BLOCKS_HPP
#include <SDL2/SDL.h>
enum BlockType {
    EMPTY,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    PURPLE,
    BLOCKTYPE_MAX,
    CUSTOM
};

extern BlockType* BlockArray;
extern SDL_Color blockcolor;

extern void DrawBlocks();
extern void PlaceBlockWithMouse(int x, int y);
extern int CheckLines();
extern void SetColor(int newr, int newg, int newb, int newa = 255, SDL_Color* color = &blockcolor);
#endif
