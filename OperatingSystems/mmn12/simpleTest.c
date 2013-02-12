
/*****************************************************************************
                The Open University - OS course,  maman 14

   File:        Test.c

   Written by:  OS course staff

   Description: simple test
 ****************************************************************************/
#include "mm.h"
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#define MIN_SIZE (2*sizeof(Header))
#define MAX_SIZE (5*sizeof(Header))
#define TIMEOUT  0


int* a,*b,*c,*d, *f;

void debug_print(){
  printf("******************* free list *****************\n");
  print_free_list();

  printf("******************* variables *****************\n");
  printf( "&a = %u, a = %u\n" , (unsigned)&a,(unsigned)a-sizeof(Header));
  printf( "&b = %u, b = %u\n" , (unsigned)&b,(unsigned)b-sizeof(Header) );
  printf( "&c = %u, c = %u\n" , (unsigned)&c,(unsigned)c-sizeof(Header) );
  printf( "&d = %u, d = %u\n" , (unsigned)&d,(unsigned)d-sizeof(Header) );
  printf( "&f = %u, f = %u\n" , (unsigned)&f,(unsigned)f-sizeof(Header) );
}


void foo( int* var ){
	printf("inside foo\n");
  debug_print();  // no change on the free list because of foo's invocation
  registerVariable( &var );
  debug_print();  // no change on the free list because of the registering procedure

  printf("compaction\n");
  mcompaction( TIMEOUT ,MIN_SIZE  , MAX_SIZE  );
  debug_print();   // memory compaction is done. We have one chank of 1014 * sizeof(HEader) instead of 1010 and 14
  unregisterVariable( &var );
}

int main(){

  a = malloc( &a , 4*sizeof(Header));
  b = malloc( &b , 3*sizeof(Header));
  c = malloc( &c , 2*sizeof(Header));
  d = malloc( &d , 1*sizeof(Header));
  debug_print();

  
  printf("a = 4*sizeof(Header)\nb = 3*sizeof(Header)\nc = 2*sizeof(Header)\nd = 1*sizeof(Header)\n");
  assignPointer(&f , &a);
  assignPointer(&a , &c);
  printf("f = a\na = c\n");
  debug_print(); // wee can see 1010*sizeof(Header) bytes free. 
                 // (4+3+2+1)*sizeof(Header) allocated 
                 // sizeof(Header) * 4 an overhead (we have 4 memory chanckes allocated)
                 // total sizeof(Header) * 1024 = (4+3+2+1)*sizeof(Header) + sizeof(Header) * 4 + 1010*sizeof(Header)
  free(&b);
  printf("free b\n");
  debug_print(); // the chank of (3+1)*sizeof(Header) is retured to the free list
  foo(d);
  return 0;
}

