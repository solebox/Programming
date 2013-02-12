#include "mm.h"
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>


#define MIN_SIZE 0
#define MAX_SIZE 10000000
#define BYTE_NUM 100 
#define ARR1_SIZE 8
#define ARR2_SIZE 9
#define ARR3_SIZE 1000
#define LOW_B 300
#define UPPER_B 600
#define COMP_INTERVAL 10

// cell size
int  gnCellSize = BYTE_NUM + sizeof(Header) + sizeof(int);



int absVal(int nVal){
  return (nVal<0)?(-nVal):nVal;
}



void SimpleCompactionPrint(int **nvArr, char* s){
  int i;

  printf("\n%s\n", s);
 

  for(i=0; i < ARR1_SIZE ;i++)
    printf( "nvArr[%d] = %u\n" ,i, (unsigned)nvArr[i] );
  
}



void Test1_SimpleCompaction( )
{
  int i = 0, *nvArr[ARR1_SIZE];


  printf("\nSimple_Compaction test\n\n");



  // malloc
  for(i=0; i < ARR1_SIZE ;i++)
    nvArr[i] = malloc(&nvArr[i] , BYTE_NUM);
  SimpleCompactionPrint(nvArr, "Simple Compaction - after allocation");
  


  // free odd
  for(i=1; i < ARR1_SIZE ;i+=2)
    free(&nvArr[i]);
  SimpleCompactionPrint(nvArr, "Simple Compaction - after free, before mcompaction"); 
  print_free_list();
  
  // compaction: all, no TIMEOUT
  mcompaction( COMPACTION_TIMEOUT ,MIN_SIZE  , MAX_SIZE  );
  
 
  
  // print after compaction
  SimpleCompactionPrint(nvArr, "Simple Compaction - after compaction");
  print_free_list();
  
  
  for(i=0; i < ARR1_SIZE ;i+=2){
    printf("%d\n",i);
    print_free_list();
    free(&nvArr[i]);
    print_free_list();
  }
  printf("\nEnd_Simple_Compaction1\n\n");
  //mcompaction( COMPACTION_TIMEOUT ,MIN_SIZE  , MAX_SIZE  );
  print_free_list();
}















void Test2_CompactionMinMax( ){
  
  int i = 0, *nvArr[ARR2_SIZE], *nvArrTmp[ARR2_SIZE];
  printf("\nCompaction_Min_Max_2\n\n");
  
  // malloc
  for(i=0; i < ARR2_SIZE ;i++)
    nvArr[i] = malloc(&nvArr[i] , i*BYTE_NUM);
  print_free_list();  
  
  
  // free all odd
  for(i=0; i < ARR2_SIZE ;i++)
    if(i%2!=0)
      free(&nvArr[i]);
      
  // print before compaction
  printf("\nCompaction_Min_Max_2 before compaction\n");

  print_free_list();
  
  for(i=0; i < ARR2_SIZE ;i++){
    printf( "nvArr[%d] = %u\n" ,i, (unsigned)nvArr[i] );
    nvArrTmp[i]=nvArr[i];
  }

  
  // compaction: LOW_B - UPPER_B, no TIMEOUT
  mcompaction( 0 ,LOW_B  , UPPER_B  );


 
  
  // print before compaction
  printf("\nCompaction_Min_Max_2 after compaction\n");
  for(i=0; i < ARR2_SIZE ;i++)
    printf( "nvArr[%d] = %u\n" ,i, (unsigned)nvArr[i] );
  print_free_list();
 
  
 
  for(i=0; i < ARR2_SIZE ;i++)
  	if(i%2==0)
    	free(&nvArr[i]);
    
 	print_free_list();
  
  printf("\nEnd_Compaction_Min_Max_2\n\n");
}

void Test3_CompactionTOUT( )
{
  int i = 0, *nvArr[ARR3_SIZE], nCompIndex = 0 , nWrComp=0;
  char strWrComp[ARR3_SIZE*32];
  memset(strWrComp,0,sizeof(strWrComp));
  sprintf(strWrComp,"\nCompaction_TOUT_3:  chunk jumps:\n");
  
  printf("\nCompaction_TOUT_3\n\n");
  // malloc
  for(i=0; i < ARR3_SIZE ;i++)
    nvArr[i] = malloc(&nvArr[i] , BYTE_NUM);

  
  // free all odd
  for(i=0; i < ARR3_SIZE ;i++)
    if(i%2!=0)
      free(&nvArr[i]);

  
  // print before compaction
  printf("\nCompaction_TOUT_3 before compaction\n");



  
  // compaction: MIN_SIZE  , MAX_SIZE , with TIMEOUT
  mcompaction( COMP_INTERVAL ,MIN_SIZE  , MAX_SIZE   );
  
  // print before compaction
  printf("\nCompaction_TOUT_3 after compaction\n");
  
  // no print after compaction, huge size
  
  //simple check of correctness, where the compaction stopped
  for(i=0; i < ARR3_SIZE ;i++){
    if(i<2 || i%2!=0)
     	continue;
    if(i%2==0){ // even cell
     	if(absVal((unsigned)nvArr[i]-(unsigned)nvArr[i-2])!= gnCellSize && absVal((unsigned)nvArr[i]-(unsigned)nvArr[i-2])!= (2*gnCellSize) )
				sprintf( strWrComp+strlen(strWrComp),"entries %d-%d = %d\n", i-2, i, absVal((unsigned)nvArr[i]-(unsigned)nvArr[i-2]));
     	if (nWrComp++%10==0) 
				sprintf( strWrComp+strlen(strWrComp),"\n");
    }
    if(absVal(nvArr[i]-nvArr[i-2]) == (2*gnCellSize) && nCompIndex == 0){
     	printf( "\nCompaction_TOUT_3: Compaction stopped in entry: %d , size = %d\n",i-2, (unsigned)nvArr[i]-(unsigned)nvArr[i-2]);
     	nCompIndex = i;
    }
  }
  
  printf( "%s \n",strWrComp);

  if(nCompIndex == 0)
    printf( "\nCompaction_TOUT_3: Compaction stopped after timeout\n");
  
  for(i=0; i < ARR3_SIZE ;i++)
  	if(i%2==0)
	    free(&nvArr[i]);
    
  printf("\nEnd of Compaction_TOUT_3\n\n");
}





int main()
{
  Test1_SimpleCompaction( );
  Test2_CompactionMinMax( );
  Test3_CompactionTOUT( );
  return 0;
}

