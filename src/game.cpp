#include "game.hpp"
#include "blocks.hpp"
#include "piece.hpp"
#include <cstdlib>
#include <cstdio>

void TestPiece()
{
    BlockType color = (BlockType)(rand()%(BLOCKTYPE_MAX-1) +1); // random color
    PieceType piece = (PieceType)(rand()%(PIECETYPE_MAX-1) +1); // random piece
    SpawnPiece(piece, color);
    printf("Piece Spawned\n");
}
