/*****************************************************************************
                The Open University - OS course,  maman 12

   File:        mm.h

   Written by:  OS course staff

   Description: this file defines a simple library for memory allocation


                           DO NOT CHANGE THIS FILE!
 ****************************************************************************/
#ifndef MM_H
#define MM_H

 
#define NALLOC             1024 


#define RET_ERROR -1
#define RET_OK  0
#define RET_OK_TIME 1

typedef long Align;

union header{
  struct{
    union header* ptr;
    unsigned size;
  } s;

  Align x;
};

typedef union header Header;


// total of used memory regions / heap size
#define LOAD_FACTOR        0.85

// maximal timiout for compaction algorithm (in msecs, 1 msec = 10^-6 sec)
// in single malloc invocation
#define COMPACTION_TIMEOUT 4000000

// minimal segment size (in bytes) for compaction algorithm 
// in single malloc invocation
#define MIN_SEGMENT_SIZE   4

// maximal segment size (in bytes) for compaction algorithm 
// in single malloc invocation
#define MAX_SEGMENT_SIZE   100




/* 
	Params:
		nbytes - bytes to allocate
		varAddress - variable holding the memory address of allocated region

	Returns:
		NULL - upon a failure
		valid address - otherwise

	Algorithm:
	    1)     if sufficient free region is availabe{ 
		2)          register new address in the static data structure
		3)          return newly allocated address
		4)    }
		5)     else{
		6)          if factor < LOAD_FACTOR{
		7)             run compaction algorithm with COMPACTION_TIMEOUT,
		               MIN_SEGMENT_SIZE, MAX_SEGMENT_SIZE parameters
		8)             if sufficient free region is availabe {
		9)                  register new address in the static data structure
		10)                 return newly allocated address
		11)	           }
		12)         }
		13)         
		14)         extend the heap (sbrk function)
		15)         register new address in the static data structure
		16)         return newly allocated address
		17)	    
		18)    }
		19)    return NULL     
					          
  */
void* malloc( void* varAddress , unsigned nbytes );


/*
	Params:
		fromVar - variable from the right side of assignment
		toVar   - variable from the left side of assignment
	
	Returns:
		just disregard
	
	Note: assigned variable must be registered in the static data structure

  */


void* assignPointer( void* toVar , void* fromVar );



/* 
	Params: 
		varName - address of region that is about to be freed

	Note: varName must be unregistered from the the static data structure
  */
void free( void* varName );



/*
	Params: 
		varName - variable to be registered
        Returns:
		      RET_ERROR    - if varName cant be registered (in case of full bucket)
              RET_OK            - if varName was succesfully registered

  */
int registerVariable( void* varName );


/*
	Params: 
		varName - variable to be unregistered

  */
void unregisterVariable( void* varName );


/*
	Params: 
		dt - timeout in msecs (1msec = 10^-6sec)
		minSegment - minimal segment size
		maxSegment - maximal segment size
		
        Algorithm:
                1) start from base
		2) while (not wrapped around the free list){
		3)      if (dt msecs elapsed) return;
		4)      if (there is a space between the current free region and the consequent free region and
                            the size of this space is in the [minSegment,maxSegment] range)
		5)             move that space lower;
		6) }


       Returns:
       	   	   RET_ERROR - on error condition (e.g. system call failure, no space in bucket)
			   RET_OK_TIME - if dt msecs were elapced and the list was not completly traverced
			   RET_OK - if the list was completly traverced

	Notes:  1) gettimeofday function could be used to preform elapsed time mesurements

		2) memory regions could be moved using memmove function

  */
int mcompaction( unsigned dt , unsigned minSegment , unsigned maxSegment );




/*
       Params:
                None
		
       Description:
                Print the free list in the form: 
		       [base, address] -> [size, address] -> ... -> [size, address] -> [base, address]

*/


void print_free_list();



void print_table(void);


#endif
