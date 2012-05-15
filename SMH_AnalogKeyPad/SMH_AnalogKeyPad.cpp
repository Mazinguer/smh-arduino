/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  6-May-2012
 * DESCRIPTION:
 *   Arduino C code class for reading a keypad attached to an analog input.
 *   + Repeat functionality.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#include "SMH_AnalogKeyPad.h"

/*
 * CONSTRUCTOR
 *
 * PARAMETERS:
 *   aInput: analog input pin. Where the keypad sends the signal.
 *   thresholds: array of values in the range of the analog input [0-1023]. It MUST end with a SMH_AnalogKeyPad_END value.
 *   keys: array of values to be returned when a key is pressed. It MUST be the length of thresholds -1 (doesn't need an end value).
 *
 * DESCRIPTION:
 *   When a key is pressed, the value meassured through the analog input is compared with the thresholds array ones. Choosing the inmediatly
 *   higher one and using its ordinal position (1st, 2nd...) to select the returning value from the keys array which will correspond to the
 *   key pressed.
 *   
*/
SMH_AnalogKeyPad::SMH_AnalogKeyPad(int aInput, int* thresholds, short* keys){
  this->aInput = aInput;
  this->thresholds = thresholds;
  this->keys = keys;
  this->repTrigger = 1000;
  this->repPeriod  = 300;
}



/*
 * repTrigger:
 *   When a key is pressed more than repTrigger miliseconds, key repeat starts.
*/
void SMH_AnalogKeyPad::setRepTrigger(unsigned int trigger){
  this->repTrigger = trigger;
}

unsigned int SMH_AnalogKeyPad::getRepTrigger(){
  return(this->repTrigger);
}


/*
 * repPeriod:
 *   Miliseconds between key repeats.
*/
void SMH_AnalogKeyPad::setRepPeriod(unsigned int period){
  this->repPeriod  = period;
}

unsigned int SMH_AnalogKeyPad::setRepPeriod(){
  return(this->repPeriod);
}


/*
 * NON-BLOCKING reading
 *
 * RETURN:
 *   A value from the array keys.
 *   If no key is read it returns the corresponding value (NO_KEY).
 *   
*/
short SMH_AnalogKeyPad::readKey(){
  int val = analogRead(this->aInput);
  int i = 0;
  boolean found = false;
  while (!found){
    if (this->thresholds[i]==SMH_AnalogKeyPad_END){
      found = true;   
    }else if (val< this->thresholds[i]){
      found = true;
    } else {
      i++;
    }
  }  
  return (SMH_AnalogKeyPad::keys[i]);
}


/*
 * BLOCKING reading. It waits until a key is pressed and released.
 *
 * RETURN:
 *   A value from the array keys.
 *   
*/
short SMH_AnalogKeyPad::readKeyBlocking(){
  short val = NO_KEY;
  do{
    val = this->readKey();
    delay(100); //Lower comsumption
  }while(val==NO_KEY);
  while(this->readKey()!=NO_KEY){}; //ACTIVE WAIT
  return(val);
}



/*
 * NON-BLOCKING reading with key repeat
 *
*/
short  SMH_AnalogKeyPad::readKeyRep(){
  short retval = NO_KEY;
  unsigned long now = millis();
  short key=this->readKey();
  if (key==NO_KEY){
    this->lastPressedKey = NO_KEY;
    this->rep = false;
  }else{
    if(key==this->lastPressedKey){
      if(this->repTrigger!=SMH_AnalogKeyPad_NO_REP){
        if(!rep){
          if((now-this->lastPressedTime) > this->repTrigger){
            rep=true;
            this->lastPressedTime = now;
            retval=key;
          }
        }else{
          if((now-this->lastPressedTime) > this->repPeriod){
            rep=true;
            this->lastPressedTime = now;
            retval=key;
          }
        }
      }
    }else{
      this->lastPressedKey = key;
      this->lastPressedTime = now;
      retval=key;
    }
  }
  return retval;
}

