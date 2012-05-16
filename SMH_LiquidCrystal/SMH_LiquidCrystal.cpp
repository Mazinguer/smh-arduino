/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  7-May-2012
 * DESCRIPTION:
 *   Arduino C code class wrapping official LiquidCrystal class.
 *   + Switching on/off backlight.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#include "SMH_LiquidCrystal.h"


/*
 * CONSTRUCTOR
*/
SMH_LiquidCrystal::SMH_LiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7):LiquidCrystal(rs,enable, d4, d5, d6, d7) {
  this->lightSwitcher = SMH_LiquidCrystal_NOLIGHTSWITCHER;
}


/*
 *  Sets the pin which controls the backlight
 *  Call it on the setup function.
*/
void SMH_LiquidCrystal::setLightSwitcher(uint8_t pin){
  this->lightSwitcher = pin;
  pinMode(pin, OUTPUT);
  this->switchLight(true);
}

/*
 * Switches the light on an off depending on the stat param (true=light, false=no_light)
*/
void SMH_LiquidCrystal::switchLight(boolean stat){
  if(stat==true){
    if (this->lightSwitcher<0) this->lightSwitcher = -this->lightSwitcher-1;
    digitalWrite(this->lightSwitcher, HIGH);  
  } else {
    digitalWrite(this->lightSwitcher, LOW);
    if (this->lightSwitcher > -1) this->lightSwitcher = -this->lightSwitcher-1;
  }
}


/*
 * If the light is on, turns it off and vice-versa.
*/
void SMH_LiquidCrystal::switchLight(){
  if (this->lightSwitcher!=SMH_LiquidCrystal_NOLIGHTSWITCHER){
    if (this->lightSwitcher>-1){
      this->switchLight(false);
    } else{
      this->switchLight(true);
    }
  }
}
