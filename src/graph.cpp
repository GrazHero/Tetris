#include <cmath>
#include <vector>
#include <SDL2/SDL.h>
#include "window.hpp"
#include "renderer.hpp"
#include <iostream>

struct GraphPoint
{
  int x;
  int y;
  char color;
  /*0 = red
   *1 = green
   *2 = blue
   */
};
std::vector<GraphPoint> vec;
int scalefactor;

///Graph must have three variables right now. For debugging
void InitGraph()
{
  vec.reserve((windowheight/20)*windowwidth);
  scalefactor = floor(windowheight/10);
}

void UpdateGraph(float x, float y, float z)
{
  //move everything left by one
  int numtopop = 0;
  for(auto it = vec.begin(); it != vec.end(); ++it)
  {
    (*it).x--;
    if((*it).x < 300/1.3) ++numtopop;//pop anything that goes off screen
  }
  if(numtopop != 0)
  {
    for(int i=0; i <numtopop; ++i)
    vec.pop_back();//Doing this out of the other loop so we don't ruin the iterators
  }
  GraphPoint p = {windowwidth, windowheight/2+ floor(x*scalefactor), (char)0};
  vec.insert(vec.begin(), p);

  p = {windowwidth, windowheight/2+floor(y*scalefactor), (char)1};
  vec.insert(vec.begin(), p);

  p = {windowwidth, windowheight/2+floor(z*scalefactor), (char)2};
  vec.insert(vec.begin(), p);
}

void DrawGraph()
{
  for(auto it = vec.begin(); it != vec.end(); ++it)
  {
      char c = (*it).color;
      if(c == (char)0)SDL_SetRenderDrawColor(MainRenderer, 255, 0, 0, 255);

      if(c == (char)1)SDL_SetRenderDrawColor(MainRenderer, 0, 255, 0, 255);

      if(c == (char)2)SDL_SetRenderDrawColor(MainRenderer, 0, 0, 255, 255);

    SDL_RenderDrawPoint(MainRenderer, (*it).x, (*it).y);
    std::cout << (*it).y << std::endl;
  }
}
