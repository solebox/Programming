/*****************************************************************************
                The Open University - OS course

   File:        ut.h

   Written by:  OS course staff

   Description: this file defines a simple library for creating & scheduling 
                user-level threads. 

                           DO NOT CHANGE THIS FILE!
 ****************************************************************************/
#ifndef _UT_H
#define _UT_H

#include <ucontext.h>

#define MAX_TAB_SIZE 128 // the maximal threads table size.
#define MIN_TAB_SIZE 2   // the minimal threads table size.

#define SYS_ERR -1       // system-related failure code
#define TAB_FULL -2      // full threads table failure code

#define STACKSIZE 8192   // the thread stack size.

/* The TID (thread ID) type. TID of a thread is actually the index of the thread in the
   threads table. */
typedef short int tid_t;

/*
This type defines a single slot (entry) in the threads table. Each slot describes a single
thread. Note that we don't need to keep the thread state since every thread is always ready
or running. We also don't have to support adding/stopping thread dynamically, so we also don't
have to manage free slots. 
*/
typedef struct _ut_slot {
  void  *stack;         // points to the thread stack.
  ucontext_t uc;
  unsigned long vtime;  // the CPU time (in milliseconds) consumed by this thread. 
  void (*func)(int);    // the function executed by the thread.
  int arg;              // the function argument.
} ut_slot_t, *ut_slot;


/*****************************************************************************
 Initialize the library data structures. Create the threads table. If the given 
 size is otside the range [MIN_TAB_SIZE,MAX_TAB_SIZE], the table size will be 
 MAX_TAB_SIZE.
 
 Parameters:
    tab_size - the threads_table_size.

 Returns:
    0 - on success.
	SYS_ERR - on failure 
*****************************************************************************/
int ut_init(int tab_size);

/*****************************************************************************
 Add a new thread to the threads table. Allocate the thread stack and update the
 thread context accordingly. This function DOES NOT cause the new thread to run.
 All threads start running only after ut_start() is called.

 Parameters:
    func - a function to run in the new thread. We assume that the function is
	infinite and gets a single int argument.	
	arg - the argument for func.
  
 Returns:
	non-negative TID of the new thread - on success (the TID is the thread's slot
	                                     number.
    SYS_ERR - on system failure (like failure to allocate the stack).
    TAB_FULL - if the threads table is already full.
 ****************************************************************************/
tid_t ut_spawn_thread(void (*func)(int), int arg);


/*****************************************************************************
 Starts running the threads, previously created by ut_spawn_thread. Sets the 
 scheduler to switch between threads every second (this is done by registering
 the scheduler function as a signal handler for SIGALRM, and causing SIGALRM to
 arrive every second). Also starts the timer used to collect the threads CPU usage
 statistics and establishes an appropriate handler for SIGVTALRM,issued by the 
 timer.
 The first thread to run is the thread with TID 0.

 Parameters:
    None.
  
 Returns:	                                   
    SYS_ERR - on system failure (like failure to establish a signal handler).
    Under normal operation, this function should start executing threads and 
	never return.
 ****************************************************************************/
int ut_start(void);

/*****************************************************************************
 Returns the CPU-time consumed by the given thread.

 Parameters:
    tid - a thread ID.
  
 Returns:
	the thread CPU-time (in millicseconds).
 ****************************************************************************/
unsigned long ut_get_vtime(tid_t tid);

#endif
