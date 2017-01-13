
/**
 * @Author               : Tausif Ali
 * @Date                 : 04-Jan-2017
 * @Email                : anodecode@gmail.com
 * @Filename             : main.cpp
 * @Last modified by     : Tausif Ali
 * @Last modified time   : 13-Jan-2017
 * @Copyright            : feel free to use, adding reference appreciated :)
**/

/** an improved paint application with user friendly interface and functionality **/

/** features sketch

new save delete open edit-implicitly impiled

**/

#include <windows.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <io.h>
#include <time.h>
#include <vector>
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
  colrSelFore.setViewOption(Head,len,1,18,36,0,cWHITE,false,false);
  colrSelFore.RegView();

  Head[0]={"Background"};
  colrSelBack.setViewOption(Head,len,1,18,15,0,cWHITE,false,false);
  colrSelBack.RegView();

  Head[0]={" "};
  len[0]=36;
  colrSelMid.setViewOption(Head,len,1,20,15,0,cWHITE,false,true);
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
  entry[0] = "Black/Blank";
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

  for (short i = 0; i < 16; i++) {
  cc = {30,short(i+1)};
  FillConsoleOutputAttribute(hW,i,1,cc,&temp);
  FillConsoleOutputCharacter(hW,static_cast<char>(0xDB),1,cc,&temp);
  cc = {51,short(i+1)};
  FillConsoleOutputAttribute(hW,i,1,cc,&temp);
  FillConsoleOutputCharacter(hW,static_cast<char>(0xDB),1,cc,&temp);
}

  int x = NOT_ON_MENU;
  bool n1 = 0,n2 = 0,n3 = 0;

  do {
    PeekConsoleInput(hR,ir,1,&temp);
    if(temp)
    {
      if (ir[0].EventType == MOUSE_EVENT) {
        mvr = ir[0].Event.MouseEvent;
        cc = mvr.dwMousePosition;
        if(((cc.X >= 14 && cc.X <= 51)&&(cc.Y <= 24 && cc.Y >= 19)) || n1)
        {
          x = colrSelMid.selectView();
          if(x == ON_MENU) n1 = true;
          else n1 = false;
        }
        if (((cc.X >= 35 && cc.X <= 51)&&(cc.Y < 19)) || n2) {
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
        if(((cc.X >= 14 && cc.X <= 31)&&(cc.Y < 19)) || n3) {
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
  invMenu charSel[16];

  const char *Head[1] = {" "};
  short len[1] = {3};

  for(int i = 0 ; i < 15 ; i++)
  {
    charSel[i].setViewOption(Head,len,1,19,( i * 5 + 1 ),0,cWHITE,false,false);
    charSel[i].setHigh(cbackRED|cWHITE);
    charSel[i].RegView();
  }
  len[0]={4};
  charSel[15].setViewOption(Head,len,1,19,( 15 * 5 ),0,cWHITE,false,true);
  charSel[15].setHigh(cbackRED|cWHITE);
  charSel[15].RegView();

  const char *entry[1] ;
  char ch;
  int cnt = 0;
  std::stringstream ss;
  std::string str;

  for(int i = 1 ; i < 255 ; i++, cnt++)
  {
    if (i == 7) i = 14;
    if (i == 32) i++;

    ch = i;
    ss << ch;
    str = ss.str();
    entry[0] =  str.c_str();
    charSel[cnt/16].addEntry(entry);
    ss.str("");
  }
  entry[0] = "Clr";
  charSel[15].addEntry(entry);
  for(int i = 0;i<16;i++)
  {
    charSel[i].finalizeView();
    charSel[i].paintView();
  }

  COORD cc;
  DWORD temp;
  HANDLE hR = GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD ir[1];
  MOUSE_EVENT_RECORD mvr;

  int x = NOT_ON_MENU;
  bool n[16]={};

  do {
    PeekConsoleInput(hR,ir,1,&temp);
    if(temp)
    {
      if (ir[0].EventType == MOUSE_EVENT) {
        mvr = ir[0].Event.MouseEvent;
        cc = mvr.dwMousePosition;
        if(((cc.X >= 0 && cc.X < 5)&&(cc.Y <= 20)) || n[0]) {
          x = charSel[0].selectView();
          if(x == ON_MENU) n[0] = true;
          else n[0] = false;
        }
        if(((cc.X >= 5 && cc.X < 10)&&(cc.Y <= 20)) || n[1]) {
          x = charSel[1].selectView();
          if(x == ON_MENU) n[1] = true;
          else {
            n[1] = false;
            if(x != NOT_ON_MENU)
            x+=16;
          }
        }
        if(((cc.X >= 10 && cc.X < 15)&&(cc.Y <= 20)) || n[2]) {
          x = charSel[2].selectView();
          if(x == ON_MENU) n[2] = true;
          else {
            n[2] = false;
            if(x != NOT_ON_MENU)
            x+=16*2;
          }
        }
        if(((cc.X >= 15 && cc.X < 20)&&(cc.Y <= 20)) || n[3]) {
          x = charSel[3].selectView();
          if(x == ON_MENU) n[3] = true;
          else {
            n[3] = false;
            if(x != NOT_ON_MENU)
            x+=16*3;}
        }
        if(((cc.X >= 20 && cc.X < 25)&&(cc.Y <= 20)) || n[4]) {
          x = charSel[4].selectView();
          if(x == ON_MENU) n[4] = true;
          else {
            n[4] = false;
            if(x != NOT_ON_MENU)
            x+=16*4;}
        }
        if(((cc.X >= 25 && cc.X < 30)&&(cc.Y <= 20)) || n[5]) {
          x = charSel[5].selectView();
          if(x == ON_MENU) n[5] = true;
          else {
            n[5] = false;
            if(x != NOT_ON_MENU)
            x+=16*5;}
        }
        if(((cc.X >= 30 && cc.X < 35)&&(cc.Y <= 20)) || n[6]) {
          x = charSel[6].selectView();
          if(x == ON_MENU) n[6] = true;
          else {
            n[6] = false;
            if(x != NOT_ON_MENU)
            x+=16*6;}
        }
        if(((cc.X >= 35 && cc.X < 40)&&(cc.Y <= 20)) || n[7]) {
          x = charSel[7].selectView();
          if(x == ON_MENU) n[7] = true;
          else {
            n[7] = false;
            if(x != NOT_ON_MENU)
            x+=16*7;}
        }
        if(((cc.X >= 40 && cc.X < 45)&&(cc.Y <= 20)) || n[8]) {
          x = charSel[8].selectView();
          if(x == ON_MENU) n[8] = true;
          else {
            n[8] = false;
            if(x != NOT_ON_MENU)
            x+=16*8;
        }}
        if(((cc.X >= 45 && cc.X < 50)&&(cc.Y <= 20)) || n[9]) {
          x = charSel[9].selectView();
          if(x == ON_MENU) n[9] = true;
          else {
            n[9] = false;
            if(x != NOT_ON_MENU)
            x+=16*9;}
        }
        if(((cc.X >= 50 && cc.X < 55)&&(cc.Y <= 20)) || n[10]) {
          x = charSel[10].selectView();
          if(x == ON_MENU) n[10] = true;
          else {
            n[10] = false;
            if(x != NOT_ON_MENU)
            x+=16*10;
        }}
        if(((cc.X >= 55 && cc.X < 60)&&(cc.Y <= 20)) || n[11]) {
          x = charSel[11].selectView();
          if(x == ON_MENU) n[11] = true;
          else {
            n[11] = false;
            if(x != NOT_ON_MENU)
            x+=16*11;
        }}
        if(((cc.X >= 60 && cc.X < 65)&&(cc.Y <= 20)) || n[12]) {
          x = charSel[12].selectView();
          if(x == ON_MENU) n[12] = true;
          else {
            n[12] = false;
            if(x != NOT_ON_MENU)
            x+=16*12;
        }}
        if(((cc.X >= 65 && cc.X < 70)&&(cc.Y <= 20)) || n[13]) {
          x = charSel[13].selectView();
          if(x == ON_MENU) n[13] = true;
          else {
            n[13] = false;
            if(x != NOT_ON_MENU)
            x+=16*13;
        }}
        if(((cc.X >= 70 && cc.X < 75)&&(cc.Y <= 20)) || n[14]) {
          x = charSel[14].selectView();
          if(x == ON_MENU) n[14] = true;
          else{
            n[14] = false;
            if(x != NOT_ON_MENU)
            x+=16*14;
        }}
        if(((cc.X >= 75 && cc.X < 80)&&(cc.Y <= 20)) || n[15]) {
          x = charSel[15].selectView();
          if(!x) break;
          if(x == ON_MENU) n[15] = true;
          else {
            n[15] = false;
            if(x != NOT_ON_MENU)
            x+=16*15;
        }}
      }FlushConsoleInputBuffer(hR);
    }
  } while(x == NOT_ON_MENU || x == ON_MENU);
  if (!x) return 0;
  if (x > 6) x += 7;
  if (x > 32) x++;
  return x;
}

void safe(_CANVAS &canvas)
{
  clearScreen(0,0);
  CreateDirectory("C:/pbt/",NULL);
  std::string fstr = canvas.getName();
  if(!fstr.length())
  {
    std::cout << "Enter the file name:" << '\n';
    std::cin >> fstr;
    canvas.setName(fstr.c_str());
  }
  fstr.insert(0,"C:\\pbt\\");
  fstr.append(".pbt");
  std::fstream file(fstr.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
  file << canvas;
  file.close();
}

int handleCanvasMenu(CHAR_INFO &charInfo,_CANVAS &canvas)
{
  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

  COORD cc;
  DWORD temp;
  HANDLE hW = GetStdHandle(STD_OUTPUT_HANDLE);

  for (short i = 0; i < 25; i++) {
    goxy(65,i);
    cc = {65,i};
    FillConsoleOutputAttribute(hW, cGRAY, 15,cc, &temp);
    WriteConsoleOutputCharacter(hW,"|               ",15,cc,&temp);
  }
  static bool erase = false;
  static char tt = ' ';
  static int att = 0;
  const char *p = erase?"ON":"OFF";

  cc = {74,6};
  FillConsoleOutputAttribute(hW,charInfo.Attributes,1,cc,&temp);
  FillConsoleOutputCharacter(hW,static_cast<char>(0xDB),1,cc,&temp);
  cc = {75,6};
  FillConsoleOutputAttribute(hW,charInfo.Attributes,1,cc,&temp);
  FillConsoleOutputCharacter(hW,' ',1,cc,&temp);
  cc = {74,7};
  FillConsoleOutputCharacter(hW,charInfo.Char.AsciiChar,1,cc,&temp);
  cc = {74,8};
  WriteConsoleOutputCharacter(hW,p,3,cc,&temp);

  consoleMenu cnvsOpts("OPTION");
  cnvsOpts.setOptions(66,3,8,7,0,ENABLE_PLAIN,ALIGN_LEFT|SELECT_HIGHLIGHT,USE_MOUSE,true,false,true,"Exit");
  cnvsOpts.setHigh(cWHITE|cbackDARKRED);
  cnvsOpts.setmnBG(cWHITE);
  cnvsOpts.RegisterOptions();
  cnvsOpts.newItem("Colour",NULL);
  cnvsOpts.newItem("Brush",NULL);
  cnvsOpts.newItem("Eraser",NULL);
  cnvsOpts.newItem("Save",NULL);
  cnvsOpts.newItem("Back",NULL);
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
    char seldChar = charSel();
    if(seldChar)
      charInfo.Char.AsciiChar = seldChar;
    break;
  }
  case 3:
  {
    if (erase) {
      erase = false;
      charInfo.Char.AsciiChar = tt;
      charInfo.Attributes = att ;
    }
    else
    {
      erase = true;
      tt = charInfo.Char.AsciiChar;
      att = charInfo.Attributes;
      charInfo.Char.AsciiChar = ' ';
      charInfo.Attributes = 0;
    }

    break;
  }
  case 4:
  if (!canvas.saved())
    safe(canvas);
    canvas.saved(true);
  }
  clearScreen(0,0);
  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
  if (x) return 0;
  else return 1;
}

int createCanvas(std::string fileOpen)
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
  if(fileOpen.length())
    {
      fileOpen.insert(0,"C:\\pbt\\");
      std::ifstream fstr(fileOpen,std::ios::in|std::ios::binary);
      fstr >> curCanvas;
      curCanvas.DrawCnvs(GetStdHandle(STD_OUTPUT_HANDLE));
      curCanvas.saved(true);
      fstr.close();
    }

  CHAR_INFO bStencil;
  bStencil.Char.AsciiChar = static_cast<char>(0xDB);
  bStencil.Attributes = cWHITE;

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
            curCanvas.StoreCnvs(hWcon);
            int val = handleCanvasMenu(bStencil,curCanvas);
            if (val) return 1;
            FlushConsoleInputBuffer(hRcon);
            curCanvas.DrawCnvs(hWcon);
          }
        }
        break;
    }
  }while(true);
}

std::string open(bool mode)
{
  clearScreen(0,0);
  invMenu openFile;
  const char *str[2]= {"FILE","DATE/TIME"};
  short len[2]={47,30};
  openFile.setViewOption(str,len,2,10,0,5,cBLACK|cbackGREEN,true,true);
  openFile.RegView();

  std::vector<std::string> v;
  _finddata_t data;
  int retVal = _findfirst("C:\\pbt\\*.pbt",&data);
  if (retVal != -1)
  {
    std::string holdTime;
    const char *entry[2];
    int length;
    int res=0;
    while (res != -1)
    {
      v.push_back(data.name);

      entry[0] = data.name;

      holdTime = ctime(&data.time_create);
      length = holdTime.length();
      if (holdTime[length-1] == '\n') {
        holdTime.replace(length-1,1,"\0");
      }
      length = holdTime.length();
      if (holdTime[length-1] == '\r') {
        holdTime.replace(length-1,1,"\0");
      }

      entry[1] = holdTime.c_str();
      openFile.addEntry(entry);

      res = _findnext(retVal, &data);
    }
    _findclose(retVal);
  }

  openFile.finalizeView();
  openFile.paintView();

  int x ;

  do {
    x = openFile.selectView();
  } while(x == NOT_ON_MENU || x == ON_MENU);

  if (mode && x) {
    std::string fileOpen = v.at(x-1);
    fileOpen.insert(0,"C:\\pbt\\");
    remove(fileOpen.c_str());
  }

  if(x)
    return v.at(x-1);
  else
    return "";
}

void help()
{
  clearScreen(0,0);
  std::cout << "\n  NEW:\n==========\n Opens a new canvas for drawing" << '\n';
  std::cout << " In the drawing area Press \'T\' to toggle options" << '\n';
  std::cout << " Options include selecting Colours and Paint-Brush character" << '\n';
  std::cout << "\nOPEN:\n==========\n Open a previously saved drawing" << '\n';
  std::cout << "\nDELETE:\n==========\n Delete a previously saved drawing" << '\n';
  std::cout << "\n\n\nPress Enter to return to Menu" << '\n';
  std::cin.ignore();
}

void about()
{
  clearScreen(0,0);
  int i=7;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,5);std::cout  << "PPPPPPPP AAAAAAAAA  IIIIIIII NNNN     NN TTTTTTTT ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,6);std::cout  << "PP    PP AA     AA     II    NN NN    NN    TT    ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,7);std::cout  << "PP    PP AA     AA     II    NN  NN   NN    TT    ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,8);std::cout  << "PPPPPPPP AAAAAAAAA     II    NN   NN  NN    TT    ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,9);std::cout  << "PP       AA     AA     II    NN    NN NN    TT    ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,10);std::cout << "PP       AA     AA     II    NN     NNNN    TT    ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,11);std::cout << "PP       AA     AA  IIIIIIII NN      NNN    TT    ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,13);std::cout << "================================================= ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i++);
  goxy(10,15);std::cout << "            DEVELOPED BY - TAUSIF ALI             ";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cWHITE);
  std::cout << "\n\n\nPress Enter to return to Menu" << '\n';
  std::cin.ignore();
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
    case 1:
      {
        createCanvas("");
        break;
      }
    case 2:
      {
        std::string fileName = open(0);
        if (fileName.length()) createCanvas(fileName);
        break;
      }
    case 3:
      {
        open(1);
        break;
      }
    case 4:
      {
        help();
        break;
      }
    case 5:
      {
        about();
        break;
      }
    }
  }while (x);
  return 0;
}
