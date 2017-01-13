
/**
 * @Author               : Tausif Ali
 * @Date                 : 07-Jan-2017
 * @Email                : anodecode@gmail.com
 * @Filename             : Canvas.h
 * @Last modified by     : Tausif Ali
 * @Last modified time   : 13-Jan-2017
 * @Copyright            : feel free to use, adding reference appreciated :)
**/

#ifndef _CANVAS_H
#define _CANVAS_H

#include <windows.h>
#include <iostream>

class _CANVAS
{
  public:
    _CANVAS();
    ~_CANVAS();

    void DrawCnvs(HANDLE handle_out);
    void StoreCnvs(HANDLE handle_out);

    const char* getName();
    void setName(const char*);

    void saved(bool isSaved);
    bool saved();

  protected:

  private:
    CHAR_INFO *cnvsBuffer;

    char *szName;
    SMALL_RECT outBuffRect;
    bool modified;

    friend std::ostream& operator<<(std::ostream& ,_CANVAS&);
    friend std::istream& operator>>(std::istream& ,_CANVAS&);
};

#endif // CANVAS_H
