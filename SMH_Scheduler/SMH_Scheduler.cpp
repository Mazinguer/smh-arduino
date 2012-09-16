/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-Sep-2012
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
}


/*
 * RUN
 *
 * PARAMETERS:
 *
 * DESCRIPTION:
 *  Starts a schedule round. Finds functions that should be executed
 *   and calls them. 
 */
void SMH_Scheduler::run(){
  unsigned long time = millis();
  Task* task = this->taskList;
  while (task != NULL){
    if(task->next_time <= time){
      task->next_time += task->period;
      task->func(task->funcData);
    }
    task = task->next;
  }
  
}


/*
 * ADDTASK
 *
 * DESCRIPTION:
 *  Wrapper to addTask general function.
 */
unsigned short SMH_Scheduler::addTask(void (*func)(void*), unsigned long period){
  return(this->addTask(func, period, 0, NULL));
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
 * RETURN:
 *  The id of the added task.
 *
 * DESCRIPTION:
 *  Adds a function to the scheduler as a task.
 *  It's possible to add up to 256 tasks per scheduler object.
 */
unsigned short SMH_Scheduler::addTask(void (*func)(void*), unsigned long period, unsigned long delay, void* funcData){
  Task* task = (Task*) malloc(sizeof(struct Task));
  task->func = func;
  task->funcData = funcData;
  task->period = period;
  task->next_time = period+delay;
  task->next = this->taskList; 
  if (this->taskList == NULL){
    task->id = 0;
  } else {
    task->id = this->taskList->id+1;
  } 
  this->taskList = task;
  return (task->id);
}

/*
 * DELETETASK
 *
 * PARAMETERS:
 *   id: the id of the task to delete.
 *
 * RETURN:
 *  True if the task could be deleted, otherwise false.
 *
 * DESCRIPTION:
 *  Deletes a task from the scheduler
 */
bool SMH_Scheduler::deleteTask(unsigned short id){
  Task* task = this->taskList;
  Task* prevTask = NULL;
  bool retval = false;
  if (task!=NULL){
    while ((task!=NULL) && (task->id > id)){
      prevTask = task;
      task = task->next;
    }
    if (task!=NULL){
      if (task->id == id){
        if (prevTask==NULL){
          this->taskList = task->next; //1st element
        } else {
          prevTask->next = task->next;
        }
        free(task);
        retval = true;
      }
    }
  }
  return(retval);
}

