/*****************************************************************************
                The Open University - OS course

   File:        binsem.h

   Written by:  OS course staff

   Description: this file defines a simple binary semaphores library for
                user-level threads. 
                Only 2 values are allowed for a binary semaphore - 0 and 1. 
                If a semaphore value is 0, down() on this semaphore will cause 
                the calling thread to wait until some other thread raises it 
                (by performing up()). Note that any number of therads may be 
                waiting on the same semaphore, and up() will allow only one of
                them to continue execution. 
                If a semaphore value is 1, up() on this semaphore has no 
                effect.

                           DO NOT CHANGE THIS FILE!
 ****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION HINTS:
//
// 1) Use the xchg() macro defined in atomic.h. You may define your own macros 
//    based on xchg() if you find it useful. 
//
// 2) Use the fact that the user-level threads scheduler is activated by signal
//    of type SIGALRM, in the following way: a thread that must wait on a 
//    semaphore will issue SIGALRM to cause immediate switch to another 
//    thread, each time the "waiting" thread is scheduled.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _BIN_SEM_H
#define _BIN_SEM_H

#include "atomic.h"

/*****************************************************************************
  The semaphore type definition.
*****************************************************************************/

typedef unsigned long sem_t;

/*****************************************************************************
  Initializes a binary semaphore.
  Parameters:
    s - pointer to the semaphore to be initialized.
    init_val - the semaphore initial value. If this parameter is 0, the 
    semaphore initial value will be 0, otherwise it will be 1.
*****************************************************************************/
void binsem_init(sem_t *s, int init_val);

/*****************************************************************************
  The Up() operation.
  Parameters:
    s - pointer to the semaphore to be raised.    
*****************************************************************************/
void binsem_up(sem_t *s);

/*****************************************************************************
  The Down() operation.
  Parameters:
    s - pointer to the semaphore to be decremented. If the semaphore value is
    0, the calling thread will wait until the semaphore is raised by another 
    thread.
  Returns: 
      0 - on sucess.
     -1 - on a syscall failure.
*****************************************************************************/
int binsem_down(sem_t *s);

#endif
