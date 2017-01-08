
/**
 * @Author               : Tausif Ali
 * @Date                 : 07-Jan-2017
 * @Email                : anodecode@gmail.com
 * @Filename             : Canvas.h
 * @Last modified by     : Tausif Ali
 * @Last modified time   : 08-Jan-2017
 * @Copyright            : feel free to use, adding reference appreciated :)
**/

#ifndef _CANVAS_H
#define _CANVAS_H

#include <windows.h>

class _CANVAS
{
  public:
    _CANVAS();
    ~_CANVAS();

    void GetcnvsBuffer(HANDLE handle_out);
    void SetCnvsBuffer(HANDLE handle_out);

    void saved(bool isSaved);

  protected:

  private:
    CHAR_INFO *cnvsBuffer;

    char *szName;
    SMALL_RECT outBuffRect;
    bool modified;
};

#endif // CANVAS_H
