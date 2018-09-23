#include "timing.hpp"
#include <cmath>
#include <SDL2/SDL.h>
#include <cstdio>
#include <vector>

int now;
int last = 0;
unsigned long framecount = 0;
double framerate;
double DeltaTime;
//std::vector
void CalculateDeltaTime()
{
  while(true)
  {
    now = SDL_GetTicks();
    double temprate;
    //if(now - last > floor((1/60)*1000))
    //{
      DeltaTime = (double)(now - last)/1000.0;
      framerate = 1000.0/((double)now - (double)last);
      //if(DeltaTime == 0.0)printf("ZERO");
      //printf("%d, %d, %f\n", now, last, (now-last)/1000.0);
      last = now;
      if(120%framecount == 0)
      {

      }
      ++framecount;
      printf("%lf\n", framerate);
      return;
    //}
  }
}
