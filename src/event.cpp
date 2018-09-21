#include "event.hpp"
#include "grid.hpp"

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
                return 1;
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
