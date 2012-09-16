/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-May-2012
 * DESCRIPTION:
 *   Arduino C code headers for the SMH_Menu class (Menu widget).
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#ifndef SMH_Menu_h
#define SMH_Menu_h

//Arduino IDE way to specify paths (compiling issues)
#include <../SMH_LiquidCrystal/SMH_LiquidCrystal.h>
#include <../SMH_AnalogKeyPad/SMH_AnalogKeyPad.h>

class SMH_Menu{
  private:
    SMH_LiquidCrystal *lcd;
    SMH_AnalogKeyPad *input;
    char** items;
    void (**functions)(SMH_LiquidCrystal*,SMH_AnalogKeyPad*);
    short state,itemsLength;
  public:
    SMH_Menu(SMH_LiquidCrystal*,SMH_AnalogKeyPad*);
    void config(char**, int, void (**)(SMH_LiquidCrystal*,SMH_AnalogKeyPad*));
    void setState(short);
    short run();
};

#endif

