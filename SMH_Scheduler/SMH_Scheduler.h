/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-Sep-2012
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
      unsigned short id;
      void  (*func)(void*);
      void* funcData;
      unsigned long period, next_time;      
      Task* next;
    };
    Task *taskList;
  
  public:
    SMH_Scheduler();
    unsigned short addTask(void (*)(void*), unsigned long);
    unsigned short addTask(void (*)(void*), unsigned long, unsigned long, void*);
    bool deleteTask(unsigned short id);
    void run();
};

#endif

