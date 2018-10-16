#include "grid.hpp"
#include "timing.hpp"
#include "blocks.hpp"
#include "coloreffects.hpp"

#include <cmath>

/*Color effects to be used on the whole grid for the
 *sake of looking cool*/
 double pi = 3.1415926535897;

void Color_DiagonalCosScaleTopLeft()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int red = (0x9F - floor(80*sin(mscount/(400)+i*cos(mscount/1000))));
    int green = (0x9F - floor(80*sin(mscount/(400)+i*cos(mscount/1000))));
    int blue = (0x9F - floor(80*sin(mscount/(400)+i*cos(mscount/1000))));

    red -= abs(red*sin(mscount/1000));
    green -= abs(green*sin((mscount+1000)/1000));
    blue -= abs(blue*sin((mscount+2000)/1000));

    int color = (red<<16) | (green<<8) | blue;
    DiagonalFill(i, (BlockType)color, true);
  }
}

void Color_Checkerboard()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int c = (0x9F - floor(80*sin(mscount/400+i*3)));
    int red = c;
    int green = c;
    int blue = c;

    red -= abs(red*sin(mscount/1000));
    green -= abs(green*sin((mscount+1000)/1000));
    blue -= abs(blue*sin((mscount+2000)/1000));

    int color = (red<<16) | (green<<8) | blue;
    DiagonalFill(i, (BlockType)color, true);
  }
}

void Color_BigDiagonalScroll()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int c = (0x9F - floor(80*sin(mscount/400+i*6)));
    int red = c;
    int green = c;
    int blue = c;

    red -= abs(red*sin(mscount/1000));
    green -= abs(green*sin((mscount+1000)/1000));
    blue -= abs(blue*sin((mscount+2000)/1000));

    int color = (red<<16) | (green<<8) | blue;
    DiagonalFill(i, (BlockType)color, true);
  }
}

void Color_DoubleCheckerBoard()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int c = (0x9F - floor(80*sin(mscount/400+i*9)));
    int red = c;
    int green = c;
    int blue = c;

    red -= abs(red*sin(mscount/1000));
    green -= abs(green*sin((mscount+1000)/1000));
    blue -= abs(blue*sin((mscount+2000)/1000));

    int color = (red<<16) | (green<<8) | blue;
    DiagonalFill(i, (BlockType)color, true);
  }
}

void Color_()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int c = (0xFF);// - floor(80*sin(mscount/400)));
    int red = c;
    int green = c;
    int blue = c;

    red *= 0.5*abs(sin(mscount/500));
    green *= 0.5*abs(sin(mscount/500 + 2*2.0943));
    blue *= 0.5*abs(sin(mscount/500 + 2.0943));

    if(red < 0 || red > 255)
      red = 0;
    if(green < 0 || green > 255)
      green = 0;
    if(blue < 0 || blue > 255)
      blue = 0;

    int color = (red<<16) | (green<<8) | blue;
    DiagonalFill(i, (BlockType)color, true);
  }
}
void Color_HorizontalScrollDown()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int red = (0x9F - floor(80*sin(mscount/(400)-i)));
    int green = (0x9F - floor(80*sin(mscount/(400)-i)));
    int blue = (0x9F - floor(80*sin(mscount/(400)-i)));

    red -= abs(red*sin(mscount/1000));
    green -= abs(green*sin((mscount+1000)/1000));
    blue -= abs(blue*sin((mscount+2000)/1000));

    int color = (red<<16);
    RowFill(i, (BlockType)color, true);
  }
}

void Color_HorizontalRedScrollUp()
{
  for(int i = 0; i < gridheight+gridwidth; ++i)
  {
    int red = (0x9F - floor(100*sin(mscount/(400)+i)));

    red *= abs(1.1*sin(mscount/1000));

    if(red < 10) red = 10;
    if(red > 255) red = 255;
    int color = (red<<16);
    RowFill(i, (BlockType)color, true);
  }
}
