#ifndef BLOCKS_HPP
#define BLOCKS_HPP

enum BlockType {
    EMPTY,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    PURPLE,
    BLOCKTYPE_MAX
};

extern BlockType* BlockArray;

extern void DrawBlocks();
extern void PlaceBlockWithMouse(int x, int y);
extern int CheckLines();

#endif
