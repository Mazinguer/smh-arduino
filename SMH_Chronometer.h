/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  9-May-2012
 * DESCRIPTION:
 *   Arduino C code headers for the SMH_Chronometer class.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#ifndef SMH_Chronometer_h
#define SMH_Chronometer_h

#include "Arduino.h"
#include "SMH_LiquidCrystal.h"
#include "SMH_AnalogKeyPad.h"

class SMH_Chronometer{
  private:
    unsigned long auxTime;             //While running will store init time, while stopped, elapsed time.
    unsigned long lapTime;             //Stored time
    boolean running;                   //Is the time running?
    SMH_LiquidCrystal* lcd;
    SMH_AnalogKeyPad* input;  
    
    void printTime(int,int,unsigned long);
    void reset();
    void startStop();
  
  public:
    SMH_Chronometer();
    void chronometer(SMH_LiquidCrystal*, SMH_AnalogKeyPad*);
    void uptime(SMH_LiquidCrystal*, SMH_AnalogKeyPad*);
};

#endif
