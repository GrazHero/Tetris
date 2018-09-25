#include "timing.hpp"
#include "quit.hpp"
#include <cmath>
#include <SDL2/SDL.h>
#include <cstdio>
#include <vector>

Uint64 now;
Uint64 last = 0;
Uint64 freq;
float frametime; // in milliseconds
float lastframetime;
unsigned framecount = 0;
unsigned secondcount = 0;

float mscount = 0;
float lastmscount = 0;
float framerate;
float avgframerate;
double DeltaTime;

std::vector<float> framevector(30, 0.0);

void CalculateTime()
{
  //while loop here. it doesn't do anything special right now, but I might use it to keep the game from running faster than a certain framerate\
    Gotta save on battery life, right?
  while(true)
  {

    now = (SDL_GetPerformanceCounter());
    try
    {
      freq = SDL_GetPerformanceFrequency();
      if(freq == 0)
        throw -1;
    }
    catch(int except)
    {
      Killswitch("Your computer lacks the high frequency clock required "
                 "for calculating frame rate and delta time. Dare I ask how old it is?");
    }

    frametime = 1000.0*(((float)now)/(float)freq - ((float)last)/float(freq));
      last = now;

   // printf("ms: %f\n", mscount);
//    if(frametime >= )) //aim for 60fps
//    {

    //printf("%f\n", frametime);
      DeltaTime = (double)(frametime)/1000.0;

    mscount += frametime;
      lastframetime = frametime;

      if(mscount - lastmscount >= 1000)//if one second has passed
      {
        secondcount += floor((mscount - lastmscount)/1000);
        lastmscount = mscount;
        //printf("%u seconds\n", secondcount);
      }

      if(framecount%2 == 0)//only calculate the framerate every other frame. I assume vector functions are expensive
      {
        framerate = 1000.0f/((frametime));
        framevector.insert(framevector.begin(), framerate);
        framevector.pop_back();
      }

/*      if(secondcount%2==0) //we evaluate the average frame rate every 2 seconds
//      {
        auto begin = framevector.begin();
        auto end = framevector.end();
        float temp = 0;
        for(auto it = begin; it != end; ++it)
        {
          temp += *it;
          //printf("%d\n", std::distance(begin, it));
        }
        avgframerate = temp/framevector.size();
//      }*/


      ++framecount;
        avgframerate = 1000.0/frametime;
        printf("FPS: %f\n", frametime);
      //printf("begin:%d\ncapacity:%d\n", framevector.begin(), framevector.capacity());
      break;
//    }
  }
}
