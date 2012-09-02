/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  2-Sep-2012
 * DESCRIPTION:
 *   Arduino C code headers for the SMH_Scheduler class.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/

#ifndef SMH_Scheduler_h
#define SMH_Scheduler_h

#include "Arduino.h"

class SMH_Scheduler{
  private:  
    struct Task{
      void  (*func)(void*);
      void* funcData;
      unsigned long period, next_time;      
      Task* next;
    };
    Task *taskList;
    Task *taskCursor;
  
  public:
    SMH_Scheduler();
    void addTask(void (*)(void*), unsigned long);
    void addTask(void (*)(void*), unsigned long, unsigned long, void*);
    void run();
};

#endif

