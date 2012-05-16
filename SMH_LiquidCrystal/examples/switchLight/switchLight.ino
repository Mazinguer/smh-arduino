/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-May-2012
 * DESCRIPTION:
 *   Example for the SMH_LiquidCrystal Arduino library.
 *   The arduino will turn on and off the backlight of the attached LCD.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

//NOTE: When you use the SMH_LiquidCrystal library, you'll need to include also
// the LiquidCrystal library in the main sketch due to the Arduino IDE linking issues.

#include <LiquidCrystal.h>
#include <SMH_LiquidCrystal.h>

//Initialize the library with the numbers of the interface pins.
//NOTE: this pin layout may not fit your lcd. Please read the doc of your screen.
SMH_LiquidCrystal lcd(8,9,4,5,6,7);


void setup(){
  lcd.begin(16,2);           //The screen is 2 lines of 16 characters
  lcd.setLightSwitcher(10);  //Pin which controls the backlight
}


void loop(){
  lcd.switchLight(true);  //Light on
  delay(1000);
  lcd.switchLight(false); //Light off
  delay(1000);
  lcd.switchLight();      //Change the state. Light on?
  delay(300);
  lcd.switchLight();      //Change the state. Light off?
  delay(300);
}
