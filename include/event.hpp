#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL2/SDL.h>
#include <cstdio>

extern SDL_Event* MainEvent;

int HandleEvents();
#endif
