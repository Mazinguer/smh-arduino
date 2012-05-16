/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-May-2012
 * DESCRIPTION:
 *   Example for the SMH_Menu Arduino library.
 *   Please note that every element (item) in the menu calls
 *    a function when selected. Two or more items can call the
 *    same function. EJ: Credits.
 *
 * MENU STRUCTURE:
 *  -Item 1 -> function fitem
 *  -Item 2 -> function fitem
 *  -Item 3 -> function fitem
 *  -Submenu A -> function sa
 *    -Item A.1 -> function fitem
 *    -Item A.2 -> function fitem
 *    -Item A.3 -> function fitem
 *    -Credits A -> function credits
 *      -Samuel M.H.  -> function foo
 *  -Submenu B -> function sb
 *    -Item B.1 -> function fitem
 *    -Item B.2 -> function fitem
 *    -Item B.3 -> function fitem
 *  -Credits -> function credits
 *    -Samuel M.H.  -> function foo
 *   
 * KEYS:
 *   UP-DOWN: next - previous item.
 *   RIGHT:   call function, enter the item.
 *   LEFT:    exit menu, return to the function which called the menu.
 *   SELECT:  switch the backlight of the lcd screen.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#include <LiquidCrystal.h>
#include <SMH_LiquidCrystal.h>
#include <SMH_AnalogKeyPad.h>
#include <SMH_Menu.h>

//Initialize the library with the numbers of the interface pins.
//NOTE: this pin layout may not fit your lcd. Please read the doc of your screen.
SMH_LiquidCrystal lcd(8,9,4,5,6,7);

//Keypad attached to the analog input 0
SMH_AnalogKeyPad kp(A0,(int[]){64,200,400,600,900,SMH_AnalogKeyPad_END},(short[]){K_RIGHT,K_UP,K_DOWN ,K_LEFT,K_SELECT,NO_KEY});

//Menu object
SMH_Menu m(&lcd,&kp);


//Function for a selected item. The same for all
void fitem(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  lcd->clear();
  lcd->print(" Item selected!");
  lcd->setCursor(0,1);
  lcd->print("Back in 3 secs");
  delay(3000);
}

//Function for "Submenu A" item
void sa(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  m.menu((char*[]){"Item A.1","Item A.2","Item A.3","Credits A"},4,(void (*[])(SMH_LiquidCrystal*,SMH_AnalogKeyPad*)){&fitem,&fitem,&fitem,&credits});
}

//Function for "Submenu B" item
void sb(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  m.menu((char*[]){"Item B.1","Item B.2","Item B.3"},3,(void (*[])(SMH_LiquidCrystal*,SMH_AnalogKeyPad*)){&fitem,&fitem,&fitem});
}

//Empty function, tricky credits
//It's like the item function but done as a submenu :P
//This way my name stays until the left key is pressed ;)
void foo(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){}
//Function for "Credits" item
void credits(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  m.menu((char*[]){"Samuel M.H."},1,(void (*[])(SMH_LiquidCrystal*,SMH_AnalogKeyPad*)){&foo});  
}



void setup(){
  lcd.begin(16,2);           //The screen is 2 lines of 16 characters
  lcd.setLightSwitcher(10);  //Comment this line if you don't need it.
}

void loop(){
  m.menu((char*[]){"Item 1","Item 2","Item 3","Submenu A","Submenu B","Credits"},6,(void (*[])(SMH_LiquidCrystal*,SMH_AnalogKeyPad*)){&fitem,&fitem,&fitem,&sa,&sb,&credits});
}




