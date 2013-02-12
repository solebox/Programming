/*
 * ut.c
 *
 *  Created on: Nov 24, 2012
 *      Author: solekiller 
 */


#include "ut.h"
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>




ut_slot thread_table;

int tt_top;
int tt_size;



static volatile int currThreadNum;
static volatile int nextThreadNum;
#define error(msg) \
    do {printf("\nerror message: "); perror(msg); printf("%s error",msg); exit(1); } while (0)
void handler(int );

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
int ut_init(int tab_size){
	if (tab_size < MIN_TAB_SIZE || tab_size > MAX_TAB_SIZE)
		tab_size = MAX_TAB_SIZE;
	tt_size = tab_size; //added place for main context
	thread_table = malloc(tt_size * sizeof(ut_slot_t));
	tt_top = 0;
	currThreadNum = 0;



	if (thread_table)
		return 0;
	else
		return SYS_ERR;
}

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
tid_t ut_spawn_thread(void (*func)(int), int arg){
	if (tt_top == tt_size)
		return TAB_FULL;
	thread_table[tt_top].arg = arg;
	thread_table[tt_top].func = func;
	thread_table[tt_top].stack = malloc(STACKSIZE);//kinda redundant but fuck it
	thread_table[tt_top].vtime = (unsigned long)0;

	if (!thread_table[tt_top].stack || getcontext(&(thread_table[tt_top].uc)) == -1)
			return SYS_ERR;

	thread_table[tt_top].uc.uc_link = &thread_table[0].uc; // main will always be located in 0
	thread_table[tt_top].uc.uc_stack.ss_sp = thread_table[tt_top].stack;
	thread_table[tt_top].uc.uc_stack.ss_size = STACKSIZE;



	makecontext(&(thread_table[tt_top].uc), (void(*)(void)) thread_table[tt_top].func, 1, thread_table[tt_top].arg);

	tt_top++;

	return (tid_t) (tt_top - 1);
}


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
int ut_start(void){
	struct sigaction sa;
	struct itimerval itv;

	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sa.sa_handler = handler;
	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec = (1000*100);
	itv.it_value = itv.it_interval;
	if ((sigaction(SIGALRM, &sa, NULL) < 0)
		 || (setitimer(ITIMER_VIRTUAL, &itv, NULL) < 0)
		 || (sigaction(SIGVTALRM, &sa, NULL) < 0)
		 )
		return SYS_ERR;
	alarm(1);
	if (setcontext(&(thread_table[0].uc)))
		error("setcontext");
	while(1)
		;
	return 0;
}

/*****************************************************************************
 Returns the CPU-time consumed by the given thread.

 Parameters:
    tid - a thread ID.

 Returns:
	the thread CPU-time (in millicseconds).
 ****************************************************************************/
unsigned long ut_get_vtime(tid_t tid){
    if (tid < 0 || tid >= tt_top)
        return 0;
	return thread_table[tid].vtime;
}

void handler(int signal) {
	if (signal == SIGVTALRM) {
			thread_table[currThreadNum].vtime += 100;
	} else if (signal == SIGINT) { // if CTRL-C is pressed print the statistics and terminate
			exit(0);
	}
	if (signal == SIGALRM){
		alarm(1);
			int thread_num = (tt_top);
			int prevThreadNum = currThreadNum;
			currThreadNum = ((currThreadNum+ 1) % thread_num) ;
			if (swapcontext(&((thread_table[prevThreadNum]).uc), &((thread_table[currThreadNum]).uc)))
				error("swapcontext");
	}
}
