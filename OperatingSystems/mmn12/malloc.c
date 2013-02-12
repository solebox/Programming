
/*****************************************************************************
   File:        malloc.c

   Written by: solekiller 

   Description: implementation of mm.h
 ****************************************************************************/


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>


#include "mm.h"
#include "defs.h"


             
static Header base;	    /* empty list to get started */
static Header *freep = NULL;/* start of free list */

// global variable to distinguish whether the calls of free are 
// from outside or from the morecore function
int free_flag; 
//global variables for computing FACTOR with metric: unit=sizeof(Header)
double total_used = 0;
double heap_size  = 0;
//macro for computing load factor, be carefull heap_s must be > 0
#define FACTOR(total_u,heap_s) ((float) ((total_u)/heap_s))

#define FALSE 0
#define TRUE  1


//----------------------------------------
/* morecore: ask system for more memory */
//----------------------------------------
static Header *morecore (unsigned nu) {
	char * cp;
	Header * up, *tmp;

	if (nu < NALLOC)
		nu = NALLOC;

	cp = sbrk (nu * sizeof(Header));
	if (cp == (char *)-1)
		return NULL;
	up = (Header*) cp;
	up->s.size = nu;
	heap_size += nu;
	tmp = (up+1);
	free ((void*)&tmp);
    heapSize += nu;
	return freep;
}



//----------------------------------------------------------------------  
void* malloc( void* varAddress , unsigned nbytes )
{
  Header *p, *prevp;
  unsigned nunits;
  bool compacted = false;
  //unsigned *address;
  
  
  //address = (unsigned *) varAddress;
  if (!mallocCalled){
    mallocCalled = true;
    initializeHashTable();
  }
  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  
  if ((prevp = freep) == NULL) { /* no free list yet */
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  
  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {		/* big enough */
      if (p->s.size == nunits) {	/* exactly */
	prevp->s.ptr = p->s.ptr;
      }
      else {						/* allocate tail end */
	p->s.size -= nunits;
	p += p->s.size;
	p->s.size = nunits;
      }
      freep = prevp;
      *(void**)(varAddress) = (void*)(p+1);
      registerVariable(varAddress);
        totalAllocated += nunits; 
      return (void *) (p+1);
    }
    if (p == freep){ 	/* wrapped around free list */
        if (!compacted && needCompaction()){
            mcompaction(COMPACTION_TIMEOUT,MIN_SEGMENT_SIZE,MAX_SEGMENT_SIZE);
            compacted = true;
            p = &base;
        }
        else{
          if((p = morecore(nunits)) == NULL)
            return NULL; // none left

        }
    }
  }
}


//----------------------------------------------------------------------  
void free( void* varName )
{
  if (!varName)
      return;
  Header * bp, * p;
  unsigned *varAddr;
  
  varAddr = (unsigned*) varName;
  
  bp = ((Header*) *varAddr) - 1; // point to block header
  totalAllocated -= bp->s.size; 
  if (totalAllocated < 0){
    totalAllocated = 0;    
  }
  if(free_flag == TRUE) //don't decrement total_used if it called from morecore
    total_used -= bp->s.size;
  
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break; /* freed block at start or end of arena */
    }
  }
  
  if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
    
  } else {
    bp->s.ptr = p->s.ptr;
  }
  if (p + p->s.size == bp) { /* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
    
  } else {
    p->s.ptr = bp;
  }
  unregisterVariable(varName);
  freep = p;
}





//----------------------------------------------------------------------  
void* assignPointer( void* toVar , void* fromVar )
{
    updatePointerValue(toVar,fromVar);
    return (void *)NULL;
}



//----------------------------------------------------------------------  
int registerVariable( void* varAddress )
{
    return add(varAddress);
}



//----------------------------------------------------------------------  
void unregisterVariable( void* varAddress )
{
    removePointer(varAddress);
}



//----------------------------------------------------------------------
int mcompaction( unsigned dt , unsigned minSegment , unsigned maxSegment )
{
   Header *freeList = base.s.ptr;
   Header *prevFreeList = &base;
   Header *segStart;
   Header *ptrNextFree;
   unsigned int dataGapSize = 0;
   unsigned int offset = 0;
  struct timeval tvStart;
  if (gettimeofday(&tvStart,0)){//starting time
    return RET_ERROR; //according to the man and stackoverflow its a syscall wrapper, hence the ret
  }
  while (freeList->s.ptr != &base && !timeHasPassed(&tvStart,dt)){
    ptrNextFree = freeList->s.ptr;    
    dataGapSize = ((freeList->s.ptr)-freeList)-(freeList->s.size);
    if (dataGapSize >= minSegment && dataGapSize <= maxSegment){
        segStart = (freeList+freeList->s.size);
        offset = segStart - freeList;
        memmove(freeList,segStart,dataGapSize);
        prevFreeList->s.ptr = (freeList + dataGapSize);
        ((Header*)(freeList+dataGapSize))->s.size = offset + ((Header*)ptrNextFree)->s.size; 
        ((Header*)(freeList+dataGapSize))->s.ptr = ((Header*)ptrNextFree)->s.ptr; 
        freeList = (freeList+dataGapSize);
        freep = &base;
        updateAddressesInHashTable((unsigned int)segStart, (unsigned int)(segStart+dataGapSize),offset*sizeof(Header)); 
    }
    
    prevFreeList = freeList;
    freeList = freeList->s.ptr;

    if (freeList == &base)
        break; //might deprecate due to abvoius reasons
  }
  if (timeHasPassed(&tvStart,dt))
      return RET_OK_TIME;
  return RET_OK;
}


//----------------------------------------------------------------------  
bool timeHasPassed(struct timeval* tv, unsigned int dt){
    struct timeval tvCurrent;
    struct timeval tvTemp;
    unsigned int tmpTime = 0;
    gettimeofday(&tvCurrent,NULL);
    timersub(&tvCurrent,tv,&tvTemp);
    tmpTime = tvTemp.tv_usec;
    if (tmpTime >= dt)
        return true;
    else
        return false;
}
void print_free_list(){
  Header *p;			
  
  printf("[base,%u] -> ",(unsigned)&base);
  for (p = base.s.ptr; p != &base; p = p->s.ptr){
     printf("[%d,%u] -> ",p->s.size,(unsigned)p);
  }
   printf("[base,%u]\n",(unsigned)&base);
}

int hashFunction(void *pointer){
	return (int)((unsigned)pointer%BUCKETS);
}
bool isEmpty(t_cell cell){
    if (cell.p == NULL || cell.pp == NULL)
        return true;
    return false;
}
int add(void **pp){
	int bucket = hashFunction(*pp); //pointer , check out other comment
	bool full = true;
	int i = 0;
	for (i = 0; i < BUCKET_DEPTH; ++i) {
		if(isEmpty(hashTable[bucket][i])){
			full = false;
			break;
		}
	}
	if (!full){
		hashTable[bucket][i].p = *pp; //pointer (thinking of getting rid of first param)
		hashTable[bucket][i].pp = pp;
        return RET_OK;
	}
    return RET_ERROR;

}
void removePointer(void **pp){
    int bucket = hashFunction(*pp); // pointer
    int i = 0;
    t_cell tmp;
    t_cell null;
    null.p = NULL;
    null.pp = NULL;
    for (i = 0; i < BUCKET_DEPTH; i++){
            tmp = hashTable[bucket][i];
            if (tmp.p != NULL && tmp.pp != NULL && 
                tmp.p == (*pp) && tmp.pp == pp){
               hashTable[bucket][i] = null; 
            }
    }
}
// remove all pointers from hashtable that have the same value as the given pointer
void removePointers(void **pp){
    int bucket = hashFunction(*pp);
    int i = 0;
    t_cell null,tmp;
    null.p = NULL;
    null.pp = NULL;
    tmp = null;
    for (i = 0; i < BUCKET_DEPTH;i++){
        tmp = hashTable[bucket][i];
        if (tmp.p != NULL && tmp.p == (*pp)){
            hashTable[bucket][i] = null;       
        }
    }
    
}
void initializeHashTable(){
	int i,k;
    t_cell null; 
    null.p = NULL;
    null.pp = NULL;
	for (i = 0; i < BUCKETS; ++i) {
		for (k = 0; k < BUCKET_DEPTH; ++k) {
			hashTable[i][k] = null;
		}
	}
}
//take the value from source and put it in destination
// update hashtable accordingly
void updatePointerValue(void **destination, void **source){
    int bucket = hashFunction(*destination);
    int i = 0;
    t_cell tmp;
    bool changed = false;
    tmp.p = NULL;
    for ( i = 0; i < BUCKET_DEPTH; i++){
        tmp = hashTable[bucket][i];
        if (tmp.p != NULL && tmp.p == (*destination) && tmp.pp == destination){
            changed = true;
            removePointer(tmp.pp);
            (*(tmp.pp)) = (*source); 
            tmp.p = (*source);
            add(tmp.pp);
        }    
    }
    if (!changed){//case were the destination doesnt exist already in table
         tmp.pp = destination;
         tmp.p = (*source);
         (*(tmp.pp)) = tmp.p;
         add(tmp.pp);
    }
}
// checks if a specific pointer isnt in the table (checks by address not by value) 
// meaning that if there is 
// a pointer with the same value in the table but 
// the given pointer is not in the table
// this func will still 
// return false
bool notInTable(void **pp){ // might be dreprecated TODO: need to test if works
    int bucket = hashFunction(*pp);
    int i = 0;
    bool inTable = false;
    t_cell tmp;

    tmp.p = NULL;
    tmp.pp = NULL;
    for (i =0; i < BUCKET_DEPTH;i++){
        tmp = hashTable[bucket][i];
        if (tmp.p != NULL && tmp.pp != NULL && tmp.pp == (pp))
            inTable = true;
    }
    return inTable;
}
void updateAddressesInHashTable(unsigned int startAddy, unsigned int endAddy, unsigned int offset){
    int i = 0;
    int k = 0;
    t_cell tmp;
    for (i = 0; i < BUCKETS; i++){
        for (k = 0; k < BUCKET_DEPTH; k++){
            tmp = hashTable[i][k];
            if (tmp.p != NULL && (unsigned int)tmp.p >= startAddy && (unsigned int)tmp.p <= endAddy){
                tmp.p -= offset;
                (*(tmp.pp)) -= offset;
            }
        }
    }
}
bool needCompaction(){
    if (totalAllocated / heapSize >= LOAD_FACTOR){
        return true;    
    }else{
        return false;    
    }
}
void printHashTable(){
    int i,k;
    printf("bucket #<num>   <key> => [<values>] \n");
    for (i = 0; i < BUCKETS; i++){
        bool before = false;
        for (k = 0; k < BUCKET_DEPTH; k++){
            if (!isEmpty(hashTable[i][k])){
               if (before){
                    printf(",%u",(unsigned)hashTable[i][k].pp);
               }else{
                    before = true;
                    printf("bucket #%d: %u =>  [",i,(unsigned)hashTable[i][k].p);
                    printf("%u",(unsigned)hashTable[i][k].pp);
               }
            }    
        }    
        if (before)
            printf("]\n");
    }
}
// lets test it
//
//
//int main(){
//    int *a,*b,*c;
//    a = malloc(&a,sizeof(int));
//    c = malloc(&c,sizeof(int));
//    *a = 6;
//    *c = 7;
//    b = NULL;
//    initializeHashTable();
//    add((void *)&a);
//    add((void *)&b);
//    add((void *)&c);
////    removePointer((void *)&b);
//    updatePointerValue((void**)&b,(void**)&c);
//    printHashTable();
//    printf("a: %u, b: %u, c: %u\n",(unsigned)a,(unsigned)b,(unsigned)c);
//    return 0;    
//}

//----------------------------------------------------------------------  
//                              EOFi---------------------------------------------------  
