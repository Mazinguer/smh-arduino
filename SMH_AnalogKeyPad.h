/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  6-May-2012
 * DESCRIPTION:
 *   Arduino C code headers for the SMH_AnalogKeyPad class (reading a keypad attached to an analog input).
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#ifndef SMH_AnalogKeyPad_h
#define SMH_AnalogKeyPad_h

#include "Arduino.h"

// Ending thresholds array constant
#define SMH_AnalogKeyPad_END -1

// Constants for keys, feel free to adapt them to your needs
#define K_RIGHT  0
#define K_UP     1 
#define K_DOWN   2
#define K_LEFT   3
#define K_SELECT 4

#define NO_KEY   5

// NO REPEAT KEY CONSTANT
#define SMH_AnalogKeyPad_NO_REP 0


class SMH_AnalogKeyPad{
    
  private:
    int* thresholds;
    short* keys;
    int aInput;
    
    //REPEAT
    unsigned int repTrigger,repPeriod;
    boolean rep; //true if repTrigger was exceeded
    unsigned long lastPressedTime;
    short lastPressedKey;    
    
  public:
    SMH_AnalogKeyPad(int, int*, short*);
    short readKey();
    short readKeyBlocking();
    
    //REPEAT
    void setRepTrigger(unsigned int);
    void setRepPeriod (unsigned int);
    unsigned int getRepTrigger();
    unsigned int setRepPeriod();
    short readKeyRep();
};
#endif
