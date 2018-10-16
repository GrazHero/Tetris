#ifndef TEXT_HPP
#define TEXT_HPP
#include <SDL2/SDL.h>

class TextObject
{
public:
  TextObject(const char* text);
  static SDL_Surface* Alphabet;
private:
  const char* alphabetpath = "./res/alphabet.bmp";
};
#endif // TEXT_HPP
