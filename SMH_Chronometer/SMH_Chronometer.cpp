/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  9-May-2012
 * DESCRIPTION:
 *   Arduino C code class with chronometer functionality, a widget.
 *   + As long as the object exists it can "run on background" and store the records.
 *   + Based on the millis() function.
 *   + Uptime widget.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#include "SMH_Chronometer.h"

/*
 * CONSTRUCTOR
*/
SMH_Chronometer::SMH_Chronometer(){
  this->auxTime = 0;
  this->lapTime = 0;
  this->running = false;
}


/*
 * Prints the current time on a position
 *
 * PARAMETERS:
 *   col: column of the first character.
 *   row: row of the first character.
 *   time: time to display in the format hours:mins:secs
*/
void SMH_Chronometer::printTime(int col, int row, unsigned long time){
  char formatTime[9]; // 00:00:00 + /0
  short seconds = (time/1000)%60;
  short minutes = (time/60000)%60;
  short hours   = (time/3600000)%60;
  sprintf(formatTime,"%.2d:%.2d:%.2d",hours,minutes,seconds);
  this->lcd->setCursor(col,row);
  this->lcd->print(formatTime);
}


/*
 * Resets the chronometer
*/
void SMH_Chronometer::reset(){
  this->auxTime = 0;
  this->lapTime = 0;
  this->lcd->clear();
  this->lcd->print("Start");
  this->lcd->setCursor(0,1);
  this->lcd->print("Reset");
  this->printTime(8,0,0);
}


/*
 * Prints the Start or Stop screen
*/
void SMH_Chronometer::startStop(){
  this->lcd->clear();
  if (this->running){
    this->lcd->setCursor(0,0);
    this->lcd->print("Stop ");
    this->lcd->setCursor(0,1);
    this->lcd->print("Lap  ");
  }else{
    this->lcd->setCursor(0,0);
    this->lcd->print("Start");
    this->lcd->setCursor(0,1);
    this->lcd->print("Reset");
  }
  printTime(8,0,this->auxTime);
  if (this->lapTime>0){
    this->printTime(8,1,this->lapTime);
  }
}


/*
 * Main function, chronometer widget
 *
 * PARAMETERS:
 *   lcd: pointer to the screen object.
 *   input: pointer to the keypad controller.
 *
 * DESCRIPTION:
 *   This function takes the control of the program and represents a chronometer.
 *
 * KEYS:
 *   UP:     Start/Stop
 *   DOWN:   Reset/Store current time (Lap).
 *   RIGHT:  -
 *   LEFT:   exit, return to the function which called the the chronometer.
 *   SELECT: switch the backlight of the lcd screen.
*/
void SMH_Chronometer::chronometer(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  this->lcd=lcd;
  this->input=input;  
  short key = 0;
  boolean  exit = false;  
  unsigned int trigger = input->getRepTrigger();
  input->setRepTrigger(SMH_AnalogKeyPad_NO_REP);
  this->startStop();  
  
  while(!exit){
    key = this->input->readKeyRep();
    if(key!=NO_KEY){
      if (key==K_UP){            //START/STOP
        this->running = !this->running;
        this->auxTime = millis()-this->auxTime;
        this->startStop();    
      } else if (key==K_DOWN){
        if(!this->running){     //RESET
          this->reset();
        }else{                  //LAP
          this->lapTime = millis()-this->auxTime;
          this->printTime(8,1,this->lapTime);
        }    
      } else if (key==K_LEFT){  //EXIT
        exit=true;
      }else if(key==K_SELECT){
        lcd->switchLight();
      }
    }
    
    if (this->running){
      printTime(8,0,millis()-this->auxTime);
    }
    delay(100);
  }
  input->setRepTrigger(trigger);  
}


/*
 * Uptime widget
 *
 * PARAMETERS:
 *   lcd: pointer to the screen object.
 *   input: pointer to the keypad controller.
 *
 * DESCRIPTION:
 *   This function takes the control of the program and shows the time the board
 *    has been running since the last power up/reset.
 *
 * KEYS:
 *   UP:     -
 *   DOWN:   -
 *   RIGHT:  -
 *   LEFT:   exit, return to the function which called the the uptime.
 *   SELECT: switch the backlight of the lcd screen.
*/
void SMH_Chronometer::uptime(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  this->lcd=lcd;
  this->input=input;
  short key = 0;
  boolean  exit = false;
  this->lcd->clear();
  this->lcd->setCursor(0,0);
  this->lcd->print("Uptime");
  while(!exit){
    key = this->input->readKeyRep();
    if(key!=NO_KEY){
      if (key==K_LEFT){  //EXIT
        exit=true;
      }else if(key==K_SELECT){
        lcd->switchLight();
      }
    }
    printTime(8,0,millis());
    delay(100);
  }

}
