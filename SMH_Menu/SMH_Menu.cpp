/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  7-May-2012
 * DESCRIPTION:
 *   Arduino C code class for displaying menus (on a LCD screen) and interacting with them through a keypad.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/


#include "SMH_Menu.h"


/*
 * CONSTRUCTOR
 *
 * PARAMETERS:
 *   lcd: pointer to the lcd screen object.
 *   input: pointer to the keypad object.
 *
*/
SMH_Menu::SMH_Menu(SMH_LiquidCrystal* lcd, SMH_AnalogKeyPad* input){
  this->lcd = lcd;
  this->input=input;
}

/*
 * MENU
 *
 * PARAMETERS:
 *   items: array of chars representing each one a menu item.
 *   itemsLength: number of the items in the menu = length of items.
 *   func: array of functions to be called when a menu item is selected. func length = items length = itemsLength
 *
 * DESCRIPTION:
 *   This function takes the control of the program and represents the given menu. When an item is selected (RIGHT KEY)
 *    the corresponding function is called (from func array).
 *
 * KEYS:
 *   UP-DOWN: next - previous item.
 *   RIGHT:   call function
 *   LEFT:    exit menu, return to the function which called the menu.
 *   SELECT:  switch the backlight of the lcd screen.
*/
void SMH_Menu::menu(char** items, int itemsLength, void (**func)(SMH_LiquidCrystal*,SMH_AnalogKeyPad*)){
  int stat = 0; //Current menu item.
  short key = 0;
  boolean exit = false;
  while (!exit){
    lcd->clear();
    lcd->print(items[stat]);
    do{
      key = input->readKeyRep();
      delay(100);
    }while(key==NO_KEY);
    
    if (key==K_UP){
      stat--;
    }else if(key==K_DOWN){
      stat++;
    }else if(key==K_RIGHT){
      func[stat](this->lcd,this->input);
    }else if(key==K_LEFT){
      exit=true;
    }else if(key==K_SELECT){
      lcd->switchLight();
    }
    stat = (stat+itemsLength)%itemsLength;
  }
}

