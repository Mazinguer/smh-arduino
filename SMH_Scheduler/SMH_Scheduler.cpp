/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  2-Sep-2012
 * DESCRIPTION:
 *   Arduino C code class for scheduling tasks.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/


#include "SMH_Scheduler.h"

//#include "Arduino.h"

/*
 * CONSTRUCTOR
 *
 * PARAMETERS:
 *
*/
SMH_Scheduler::SMH_Scheduler(){
  this->taskList = NULL;
  this->taskCursor = NULL;
}


/*
 * RUN
 *
 * PARAMETERS:
 *
 * DESCRIPTION:
 *  Starts a schedule round. Find functions that should be executed
 *   and calls them. 
 */
void SMH_Scheduler::run(){
  unsigned long time = millis();
  this->taskCursor = this->taskList;
  while (this->taskCursor != NULL){
    if(this->taskCursor->next_time <= time){
      this->taskCursor->next_time += this->taskCursor->period;
      this->taskCursor->func(this->taskCursor->funcData);
    }
    this->taskCursor = this->taskCursor->next;
  }
  
}


/*
 * ADDTASK
 *
 * PARAMETERS:
 *   func:     pointer to the function to be executed. It must receive one void* argument.
 *   period:   time between two consecuent executions.
 *
 * DESCRIPTION:
 *  Wrapper to addTask general function.
 */
void SMH_Scheduler::addTask(void (*func)(void*), unsigned long period){
  this->addTask(func, period, 0, NULL);  
}  


/*
 * ADDTASK
 *
 * PARAMETERS:
 *   func:     pointer to the function to be executed. It must receive one void* argument.
 *   period:   time between two consecuent executions.
 *   delay:    time before the first execution.
 *   funcData: data that will be passed when executing the function.
 *
 * DESCRIPTION:
 *  Starts a schedule round. Find functions that should be executed
 *   and calls them. 
 */
void SMH_Scheduler::addTask(void (*func)(void*), unsigned long period, unsigned long delay, void* funcData){
  this->taskCursor = (Task*) malloc(sizeof(struct Task));
  this->taskCursor->func = func;
  this->taskCursor->funcData = funcData;
  this->taskCursor->period = period;
  this->taskCursor->next_time = period+delay;
  this->taskCursor->next = this->taskList;  
  this->taskList = this->taskCursor;
}

