
/**
 * @Author               : Tausif Ali
 * @Date                 : 04-Jan-2017
 * @Email                : anodecode@gmail.com
 * @Filename             : main.cpp
 * @Last modified by     : Tausif Ali
 * @Last modified time   : 08-Jan-2017
 * @Copyright            : feel free to use, adding reference appreciated :)
**/

/** an improved paint application with user friendly interface and functionality **/

/** features sketch

new save delete open edit-implicitly impiled

**/

#include <windows.h>
#include <iostream>
#include "Canvas.h"
#include "consoleMenu.h"

// using namespace std;

void goxy(short x,short y)
{
  COORD cc = {x,y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cc);
}

int clrSel(CHAR_INFO &info)
{
  clearScreen(0,0);
  invMenu colrSelFore;
  invMenu colrSelBack;
  invMenu colrSelMid;

  const char *Head[1]={"Foreground"};
  short len[1]={15};
  colrSelFore.setViewOption(Head,len,1,17,36,0,cWHITE,false,false);
  colrSelFore.RegView();

  Head[0]={"Background"};
  colrSelBack.setViewOption(Head,len,1,17,15,0,cWHITE,false,false);
  colrSelBack.RegView();

  Head[0]={" "};
  len[0]=36;
  colrSelMid.setViewOption(Head,len,1,19,15,0,cWHITE,false,true);
  colrSelMid.RegView();

  const char *entry[1] ;
  entry[0] = "Dark Blue";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Dark Green";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Dark Cyan";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Dark Red";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Dark Magenta";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Dark Yellow";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Gray";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Dark Gray";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Blue";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Green";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Cyan";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Red";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Magenta";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "Yellow";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);
  entry[0] = "White";
  colrSelFore.addEntry(entry);
  colrSelBack.addEntry(entry);

  colrSelMid.finalizeView();
  colrSelMid.paintView();
  colrSelFore.finalizeView();
  colrSelFore.paintView();
  colrSelBack.finalizeView();
  colrSelBack.paintView();


  COORD cc;
  DWORD temp;
  HANDLE hW = GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE hR = GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD ir[1];
  MOUSE_EVENT_RECORD mvr;

  for (short i = 0,q = 1; i < 15; i++) {
  cc = {51,short(i+2)};
  FillConsoleOutputAttribute(hW,q+i,1,cc,&temp);
  FillConsoleOutputCharacter(hW,static_cast<char>(0xDB),1,cc,&temp);
}

  int x = NOT_ON_MENU;
  bool n1=0,n2=0,n3=0;

  do {
    PeekConsoleInput(hR,ir,1,&temp);
    if(temp)
    {
      if (ir[0].EventType == MOUSE_EVENT) {
        mvr = ir[0].Event.MouseEvent;
        cc = mvr.dwMousePosition;
        if(((cc.X >= 14 && cc.X <= 51)&&(cc.Y <= 24 && cc.Y >= 18)) || n1)
        {
          x = colrSelMid.selectView();
          if(x == ON_MENU) n1 = true;
          else n1 = false;
        }
        if (((cc.X >= 35 && cc.X <= 51)&&(cc.Y < 17)) || n2) {
          x = colrSelFore.selectView();
          if(x == ON_MENU) n2 = true;
          else {
            if(x > 0){
              info.Attributes &= 0xF0;
              info.Attributes |= x;
            }
            n2 = false;
          }
        }
        if(((cc.X >= 14 && cc.X <= 31)&&(cc.Y < 17)) || n3) {
          x = colrSelBack.selectView();
          if(x == ON_MENU) n3 = true;
          else {
            if(x > 0){
              info.Attributes &=0x0F;
              info.Attributes |= (x<<4);
            }
            n3 = false;
          }
        }
        cc = {33,4};
        FillConsoleOutputAttribute(hW,info.Attributes,1,cc,&temp);
        FillConsoleOutputCharacter(hW,info.Char.AsciiChar,1,cc,&temp);

      }FlushConsoleInputBuffer(hR);
    }
  } while(x);

  return 0;
}

int charSel()
{
  clearScreen(0,0);
  int x;
  char i;
  for ( x = 0; x < 256; x++) {
    if(x % 6 == 0)continue;
    i = x;
    std::cout << x <<'\t'<< i <<'|';
  }
  std::cin >> x;
  return x;
}


void handleCanvasMenu(CHAR_INFO &charInfo,_CANVAS &canvas)
{
  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

  COORD cc;
  DWORD temp;
  HANDLE hW = GetStdHandle(STD_OUTPUT_HANDLE);

  for (short i = 0; i < 25; i++) {
    goxy(65,i);
    cc = {65,i};
    WriteConsoleOutputCharacter(hW,"|               ",15,cc,&temp);
  }
  static bool erase = false;
  static char tt = ' ';
  const char *p = erase?"ON":"OFF";

  cc = {74,6};
  FillConsoleOutputAttribute(hW,charInfo.Attributes,1,cc,&temp);
  FillConsoleOutputCharacter(hW,static_cast<char>(0xDB),1,cc,&temp);
  cc = {74,7};
  FillConsoleOutputCharacter(hW,charInfo.Char.AsciiChar,1,cc,&temp);
  cc = {74,8};
  WriteConsoleOutputCharacter(hW,p,3,cc,&temp);

  consoleMenu cnvsOpts("OPTION");
  cnvsOpts.setOptions(66,3,8,7,0,ENABLE_PLAIN,ALIGN_LEFT|SELECT_HIGHLIGHT,USE_MOUSE,true,false,true,"Back");
  cnvsOpts.setHigh(cWHITE|cbackDARKRED);
  cnvsOpts.setmnBG(cWHITE);
  cnvsOpts.RegisterOptions();
  cnvsOpts.newItem("Colour",NULL);
  cnvsOpts.newItem("Brush",NULL);
  cnvsOpts.newItem("Eraser",NULL);
  cnvsOpts.newItem("Save",NULL);
  cnvsOpts.Mset();
int x;
  cnvsOpts.paintMenu();
  do {
    x = cnvsOpts.selectOption();
  } while(x == NOT_ON_MENU);

switch (x) {
  case 1:
  {
    clrSel(charInfo);
    break;
  }
  case 2:
  {
    charInfo.Char.AsciiChar = charSel();
    break;
  }
  case 3:
  {
    if (erase) {
      erase = false;
      charInfo.Char.AsciiChar = tt;
    }
    else
    {
      erase = true;
      tt = charInfo.Char.AsciiChar;
      charInfo.Char.AsciiChar = ' ';
    }

    break;
  }
  case 4:
  canvas.saved(true);
  }
  clearScreen(0,0);
  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}


void createCanvas()
{
  clearScreen(0,0);
  HANDLE hWcon = GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE hRcon = GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD inRec[1];
  DWORD numOfEntries;
  DWORD temp;
  COORD press;
  MOUSE_EVENT_RECORD mRec;
  KEY_EVENT_RECORD kRec;

  _CANVAS curCanvas;

  CHAR_INFO bStencil;
  bStencil.Char.AsciiChar = static_cast<char>(0xDB);
  bStencil.Attributes = cWHITE;

  // bool isPressed = false;
do{
    ReadConsoleInput(hRcon,inRec,1,&numOfEntries);

    switch(inRec[0].EventType)
    {
      case MOUSE_EVENT :
        {
          mRec = inRec[0].Event.MouseEvent;
          press = mRec.dwMousePosition;
          if (mRec.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            FillConsoleOutputAttribute(hWcon,bStencil.Attributes,1,press,&temp);
            FillConsoleOutputCharacter(hWcon,bStencil.Char.AsciiChar,1,press,&temp);
            curCanvas.saved(false);
          }
        }
        break;
      case KEY_EVENT:
        {
          kRec = inRec[0].Event.KeyEvent;
          char ch = (char)kRec.uChar.AsciiChar;
          ch = ch | 0x20;
          if (ch == 't') {
            curCanvas.SetCnvsBuffer(hWcon);
            handleCanvasMenu(bStencil,curCanvas);
            FlushConsoleInputBuffer(hRcon);
            curCanvas.GetcnvsBuffer(hWcon);
          }
        }
        break;
    }
  }while(true);
}

void open()
{
  clearScreen(0,0);
  invMenu openFile;
  const char *str[2]= {"FILE","DATE/TIME"};
  short len[2]={50,27};
  openFile.setViewOption(str,len,2,10,0,5,cBLACK|cbackGREEN,true,true);
  openFile.RegView();

  openFile.finalizeView();
  openFile.paintView();

  int x = 1;
  do{
    do {
      x = openFile.selectView();
    } while(x == NOT_ON_MENU);
  }while(x);
  clearScreen(0,0);
}

int main()
{
  consoleMenu mnMenu("MENU");
  mnMenu.setOptions(60,14,6,15,0,ENABLE_PLAIN,ALIGN_LEFT|SELECT_TEXT,USE_MOUSE,true,false,true,"Exit");
  mnMenu.setHigh(cbackDARKRED|cDARKMAGENTA);
  mnMenu.setOutcolor(cDARKBLUE,177);
  mnMenu.setmnBG(cbackDARKCYAN|cWHITE);
  mnMenu.RegisterOptions();

  mnMenu.newItem("New",NULL);
  mnMenu.newItem("Open",NULL);
  mnMenu.newItem("Delete",NULL);
  mnMenu.newItem("Help",NULL);
  mnMenu.newItem("About",NULL);
  mnMenu.Mset();

  int x;
   do{
    mnMenu.paintBackground();
    mnMenu.paintMenu();
    do {
      x = mnMenu.selectOption();
    } while(x == NOT_ON_MENU);

  switch (x) {
    case 1:createCanvas();break;
    case 2:open();break;
    }
  }while (x);
  return 0;
}
