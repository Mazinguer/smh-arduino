/*
 * AUTHOR:    Samuel M.H. <samuel.mh@gmail.com>
 * LAST REV:  16-Sep-2012
 * DESCRIPTION:
 *   Example for the SMH_Scheduler Arduino library.
 *   It shows how it's possible to schedule functions
 *    over the time.
 *
 *   The arduino calls functions at defined times
 *    that print strings through the serial port.
 *
 * WARNING:
 *  - It does NOT provide REALTIME executions.
 *  - Executions are NEVER done BEFORE the time set (period).
 *  - If a function never returns, the other functions
 *      will never be called.
 *
 * LICENSE: GPL V3 <http://www.gnu.org/licenses/gpl.html>
*/


#include "SMH_Scheduler.h"

//Construct the object
SMH_Scheduler sched;
int id_del;  //Id of the delete task


//Print Hello
void hello(void *data){
  Serial.println("Hello");
}

//Print World
void world(void *data){
  Serial.println("World\n");
}

//Print a String taken from data
void print(void *data){
  Serial.println((char*)data);
}

//Delete task
void wrapperDeleteTask(void *data){
  sched.deleteTask((unsigned short) data);
  Serial.println("Bazinga! deleted");
  if (sched.deleteTask(id_del)){
    Serial.println("Auto delete task.");
  }
}


void setup(){
  Serial.begin(9600);
  /*
  * Here we configure our task list.
  * WARNING: take into consideration the tasks are executed in reversed order,
  *  so if there are 2 tasks that should be executed at the same time, the last one
  *  you added will be executed first.
  */
  //Print Hello every second
  int id1 = sched.addTask(&hello, 1000);
  
  //Print World every second but delay the start 0,5 seconds
  int id2 = sched.addTask(&world, 1000, 500, NULL);
  
  //Print Bazinga! every 2 seconds by calling a function with a parameter.
  int id3 = sched.addTask(&print, 2000, 0, (void*)"Bazinga!\n");
  
  //Delete print Bazinga! after 10 by calling a wrapper.
  id_del = sched.addTask(&wrapperDeleteTask,0, 10000, (void*)id3);  
  
  Serial.print("ID - Task Hello: ");
  Serial.println(id1);
  Serial.print("ID - Task World: ");
  Serial.println(id2);
  Serial.print("ID - Task print Bazinga: ");  
  Serial.println(id3);
  
  //Trying to delete a non-existing task
  if (!sched.deleteTask(44)){
    Serial.println("Task with id=44 does not exist.");    
  }
}


void loop(){
  //Call to the scheduler
  sched.run();
}
