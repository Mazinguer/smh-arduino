/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-May-2012
 * DESCRIPTION:
 *   Example for the SMH_Chronometer Arduino library.
 *   You have a chronometer on yout lcd screen.
 * KEYS:
 *   UP:     Start/Stop
 *   DOWN:   Reset/Store current time (Lap).
 *   RIGHT:  -
 *   LEFT:   exit, return to the function which called the the chronometer.
 *   SELECT: switch the backlight of the lcd screen (if configured, not this example).
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#include <LiquidCrystal.h>
#include <SMH_LiquidCrystal.h>
#include <SMH_AnalogKeyPad.h>
#include <SMH_Chronometer.h>

//Initialize the library with the numbers of the interface pins.
//NOTE: this pin layout may not fit your lcd. Please read the doc of your screen.
SMH_LiquidCrystal lcd(8,9,4,5,6,7);

//Keypad attached to the analog input 0
SMH_AnalogKeyPad kp(A0,(int[]){64,200,400,600,900,SMH_AnalogKeyPad_END},(short[]){K_RIGHT,K_UP,K_DOWN ,K_LEFT,K_SELECT,NO_KEY});

//Chronometer object
SMH_Chronometer chrono;

void setup(){
  lcd.begin(16,2);           //The screen is 2 lines of 16 characters
}

void loop(){
  chrono.chronometer(&lcd,&kp);
}




