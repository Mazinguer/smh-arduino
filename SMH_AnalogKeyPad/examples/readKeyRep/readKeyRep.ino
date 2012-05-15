/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  15-May-2012
 * DESCRIPTION:
 *   Example for the SMH_AnalogKeyPad Arduino library.
 *   The arduino will output the key you are pressing through the serial port.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/


#include <SMH_AnalogKeyPad.h>

SMH_AnalogKeyPad kp(A0,(int[]){64,200,400,600,900,SMH_AnalogKeyPad_END},(short[]){K_RIGHT,K_UP,K_DOWN ,K_LEFT,K_SELECT,NO_KEY});
short key;
char* textKeys[] ={"K_RIGHT","K_UP","K_DOWN","K_LEFT","K_SELECT"};


void setup(){
  Serial.begin(9600);
  kp.setRepTrigger(2000); //If the key is not released in 2 secs, repeat will start.
  kp.setRepPeriod(150);   //Delay between key repeats.
}


void loop(){
  key = kp.readKeyRep();
  if (key!=NO_KEY){
    Serial.println(textKeys[key]);
  }  
  delay(100); //Please make a small pause between continuous readings, otherwise youll get wrong keys.
}
