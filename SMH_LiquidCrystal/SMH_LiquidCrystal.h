/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-May-2012
 * DESCRIPTION:
 *   Arduino C code headers for the SMH_LiquidCrystal class.
 *   Wrapper for LiquidCrystal with backlight functions.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#ifndef SMH_LiquidCrystal_h
#define SMH_LiquidCrystal_h

//Arduino IDE way to specify paths (compiling issues)
#include "../LiquidCrystal/LiquidCrystal.h"

#include "Arduino.h"

#define SMH_LiquidCrystal_NOLIGHTSWITCHER 255

class SMH_LiquidCrystal: public LiquidCrystal{
  private:
    //Pin that controls the backlight.
    //  Positive, light on.
    //  Negative, light off = -(pin+1)
    int lightSwitcher;
  public:
    SMH_LiquidCrystal(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    void setLightSwitcher(uint8_t);
    void switchLight(boolean);
    void switchLight();
};

#endif
