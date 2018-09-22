#include "event.hpp"
#include "grid.hpp"
#include "game.hpp"

SDL_Event* MainEvent;

int HandleEvents()
{
    while(SDL_PollEvent(MainEvent))
    {
        if(MainEvent->type == SDL_QUIT)
            return 1;
        if(MainEvent->type == SDL_KEYUP)
        {
            switch(MainEvent->key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                return 1; //this will break us from the main loop since returning 1 will set the loop var to false
                break;
            case SDL_SCANCODE_SPACE:
                //TestPiece(); //just for testing. Get ready for the segfaults
                break;
            }
        }

        if(MainEvent->type == SDL_MOUSEBUTTONUP)
        {
            printf("Click!\n");
            Click(MainEvent->button);
        }
        else return 0;
    }
}
