/*****************************************************************************
                The Open University - OS course

   File:        atomic.h

   Written by:  OS course staff

   Description: this file defines macros for storing a value in a memory 
                location and getting the value previously stored st this 
                location in a single atomic operation.
                This is code excerpted from the Linux source code file
               'include/asm-i386/atomic.h' (Copyright (C) Linus Torvalds)

                           DO NOT CHANGE THIS FILE!
 ****************************************************************************/

//#include <asm/atomic.h>

/*****************************************************************************
  This macro stores the value (x) in the location pointed by (ptr) and returns
  the previous value stored at (ptr).
*****************************************************************************/

#define xchg(ptr,x) \
 ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))

///////////////////////////////////////////////////////////////////////////////

struct __xchg_dummy { unsigned long a[100]; };

#define __xg(x) ((struct __xchg_dummy *)(x))

/*****************************************************************************
  This function actually performs the atomic operation.
  NOTE: don't use this function directly, use the xchg() macro instead.
*****************************************************************************/
static inline unsigned long __xchg(unsigned long x, void * ptr, int size)
{
	switch (size) {
		case 1:
			__asm__ __volatile__("xchgb %b0,%1"
				:"=q" (x)
				:"m" (*__xg(ptr)), "0" (x)
				:"memory");
			break;
		case 2:
			__asm__ __volatile__("xchgw %w0,%1"
				:"=r" (x)
				:"m" (*__xg(ptr)), "0" (x)
				:"memory");
			break;
		case 4:
			__asm__ __volatile__("xchgl %0,%1"
				:"=r" (x)
				:"m" (*__xg(ptr)), "0" (x)
				:"memory");
			break;
	}
	return x;
}


