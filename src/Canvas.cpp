
/**
 * @Author               : Tausif Ali
 * @Date                 : 07-Jan-2017
 * @Email                : anodecode@gmail.com
 * @Filename             : Canvas.cpp
 * @Last modified by     : Tausif Ali
 * @Last modified time   : 08-Jan-2017
 * @Copyright            : feel free to use, adding reference appreciated :)
**/

#include "Canvas.h"

_CANVAS::_CANVAS()
{
  //ctor
  cnvsBuffer = new CHAR_INFO[80*25];
  szName     = NULL;
  modified   = true;

  outBuffRect.Left   = 0;
  outBuffRect.Top    = 0;
  outBuffRect.Right  = 80;
  outBuffRect.Bottom = 25;
}

_CANVAS::~_CANVAS()
{
  //dtor
  delete [] cnvsBuffer;
  if (szName) delete [] szName;
  modified = false;
}

void _CANVAS::GetcnvsBuffer(HANDLE hOut)
{
  WriteConsoleOutput(hOut,cnvsBuffer,{80,25},{0,0},&outBuffRect);
}

void _CANVAS::SetCnvsBuffer(HANDLE hOut)
{
  ReadConsoleOutput(hOut,cnvsBuffer,{80,25},{0,0},&outBuffRect);
}

void _CANVAS::saved(bool t)
{
  modified = !t;
}
