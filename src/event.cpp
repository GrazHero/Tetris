#include "event.hpp"
#include "grid.hpp"
#include "game.hpp"
#include "quit.hpp"

SDL_Event* MainEvent;

int HandleEvents()
{
    while(SDL_PollEvent(MainEvent))
    {
        if(MainEvent->type == SDL_QUIT)
            return 1;
        if(MainEvent->type == SDL_KEYDOWN)
        {
            switch(MainEvent->key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                return 1; //this will break us from the main loop since returning 1 will set the loop var to false
                break;
            case SDL_SCANCODE_SPACE:
                //Killswitch("Don't press space, idiot");
                //CurrentPiece->CheckClaimed(5, 10);
                break;
            case SDL_SCANCODE_UP:
                //CurrentPiece->Move(0, -1);
                break;
            case SDL_SCANCODE_DOWN:
                SpeedUp(true, 20);
                break;
            case SDL_SCANCODE_LEFT:
                if(CurrentPiece!=nullptr)CurrentPiece->Move(-1, 0);
                break;
            case SDL_SCANCODE_RIGHT:
                if(CurrentPiece!=nullptr)CurrentPiece->Move(1, 0);
                break;
            case SDL_SCANCODE_Z:
                if(CurrentPiece!=nullptr)CurrentPiece->Rotate(-1);
                break;
            case SDL_SCANCODE_X:
                if(CurrentPiece!=nullptr)CurrentPiece->Rotate(1);
                break;
            case SDL_SCANCODE_B:
                if(CurrentPiece!=nullptr)CurrentPiece->PrintClaimed();
                break;
            }
        }
        if(MainEvent->type == SDL_KEYUP)
        {
            switch(MainEvent->key.keysym.scancode)
            {
            case SDL_SCANCODE_DOWN:
                SpeedUp(false);
                break;
            case SDL_SCANCODE_P:
                TogglePause();
                break;
            case SDL_SCANCODE_L:
                Lose = true;
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
