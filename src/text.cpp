#include "text.hpp"
#include <iostream>
SDL_Surface* TextObject::Alphabet = nullptr;

TextObject::TextObject(const char* text)
{
  //first time initialize
  if(Alphabet == nullptr)
  {
    Alphabet = SDL_LoadBMP(alphabetpath);
    if(Alphabet == nullptr)
      std::cerr << "Coulnd't Load Alphabet\n";
  }
}
