
/**
 * @Author               : Tausif Ali
 * @Date                 : 07-Jan-2017
 * @Email                : anodecode@gmail.com
 * @Filename             : Canvas.cpp
 * @Last modified by     : Tausif Ali
 * @Last modified time   : 13-Jan-2017
 * @Copyright            : feel free to use, adding reference appreciated :)
**/

#include "Canvas.h"

std::ostream& operator<<(std::ostream& o,_CANVAS &can)
{
  for (size_t i = 0; i < 80*25; i++) {
    o.write(reinterpret_cast<char *>(&can.cnvsBuffer[i]),sizeof(can.cnvsBuffer[i]));
  }
  return o;
}

std::istream& operator>>(std::istream& o,_CANVAS &can)
{
  for (size_t i = 0; i < 80*25; i++) {
    o.read(reinterpret_cast<char *>(&can.cnvsBuffer[i]),sizeof(can.cnvsBuffer[i]));
  }
  return o;
}

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

const char* _CANVAS::getName()
{
  if(szName == NULL) return "";
  return szName;
}
void _CANVAS::setName(const char* str)
{
  szName = new char[strlen(str)+1];
  strcpy(szName,str);
}

void _CANVAS::DrawCnvs(HANDLE hOut)
{
  WriteConsoleOutput(hOut,cnvsBuffer,{80,25},{0,0},&outBuffRect);
}

void _CANVAS::StoreCnvs(HANDLE hOut)
{
  ReadConsoleOutput(hOut,cnvsBuffer,{80,25},{0,0},&outBuffRect);
}

void _CANVAS::saved(bool t)
{
  modified = !t;
}
bool _CANVAS::saved()
{
  return !modified;
}
