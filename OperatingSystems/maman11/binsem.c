/*****************************************************************************
                The Open University - OS course

   File:        binsem.h

   Written by:  jacob 
   

   Description: this file implements a simple binary semaphores library for
                user-level threads. 
                Only 2 values are allowed for a binary semaphore - 0 and 1. 
                If a semaphore value is 0, down() on this semaphore will cause 
                the calling thread to wait until some other thread raises it 
                (by performing up()). Note that any number of therads may be 
                waiting on the same semaphore, and up() will allow only one of
                them to continue execution. 
                If a semaphore value is 1, up() on this semaphore has no 
                effect.

                         
 ****************************************************************************/
/**
 *  
 **/
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "binsem.h"
#include "ut.h"

/*****************************************************************************
  Initializes a binary semaphore.
  Parameters:
    s - pointer to the semaphore to be initialized.
    init_val - the semaphore initial value. If this parameter is 0, the 
    semaphore initial value will be 0, otherwise it will be 1.
*****************************************************************************/
void binsem_init(sem_t* s, int init_val){
    if (!s)
       return;
    if (!init_val)
        *s = 0;
    else
        *s = 1;
    return;
}
/*****************************************************************************
  The Up() operation.
  Parameters:
    s - pointer to the semaphore to be raised.    
*****************************************************************************/
void binsem_up(sem_t* s){
        if (!s)
            return;
        xchg(s, 1);
        return;
}
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
int binsem_down(sem_t* mutex){
   unsigned long reg;

   while (1){
    reg = 0;                   /* TSL */
    reg = xchg(mutex, reg);         /* TSL */
    if (reg == 1)
        return 0;
   
    if (raise(SIGALRM))
        return -1;
   }

}
