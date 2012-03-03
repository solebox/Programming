#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AsmCommandQueue.h"
/* a functions that creates the initial queue for the presented and parsed commands*/
AsmQueue CreateAsmQueue()
{
	AsmQueue Q=(AsmQueue)malloc(sizeof(struct AsmCommandRecord));
	if(Q==NULL)
		ErrorHandler(OutOfMemory,"While creating commands queue");
	Q->next=Q;
	Q->previous=Q;
	return Q;
}
/*checks if the queue data struct is empy (has no elements)*/
enum Boolean IsAsmQueueEmpty(AsmQueue Q)
{
	if(Q->next==Q)
		return TRUE;
	else
		return FALSE;
		
}
/* function adds an element to the queue*/
void AsmQueue_AddRecord(char *input, AsmQueue Q)
{
	PtrToAsmRecord newRecord=(AsmQueue)malloc(sizeof(struct AsmCommandRecord));
	int inputLenth=strlen(input);
	if(newRecord==NULL)
		ErrorHandler(OutOfMemory,"While creating new commad queue record.");

		newRecord->asmString=NULL;
		ALLOCATE_STRING(newRecord->asmString,inputLenth);

	strcpy(newRecord->asmString,input);
	
	
	if(IsAsmQueueEmpty(Q)==TRUE)
		Q->next=newRecord;
	newRecord->previous=Q->previous;
	Q->previous=newRecord;
	newRecord->next=Q;
	newRecord->previous->next=newRecord;
}
char *RetrieveAsmRecord(AsmQueue Q)
{
	int recordLength;
	char* tempAsmCommand=NULL;
	PtrToAsmRecord temp;
	if(IsAsmQueueEmpty(Q)==FALSE)
	{
		recordLength=strlen(Q->next->asmString);
		temp=(AsmQueue)malloc(sizeof(struct AsmCommandRecord));

		ALLOCATE_STRING(tempAsmCommand,recordLength);

		temp->asmString=NULL;
		ALLOCATE_STRING(temp->asmString,recordLength);

		strcpy(tempAsmCommand,Q->next->asmString);

		temp=Q->next;
		temp->next->previous=Q;
		Q->next=Q->next->next;
		/*

		Q->next=Q->next->next;

		temp->next=Q->next->next;
		temp->next->previous=Q;
		free(Q->next);
		*/
		free(temp);
		return  tempAsmCommand;
	}
	return NULL;

}
/*removes element from queue*/
void RemoveRecordFromAsmQueue(AsmQueue Q)
{
	PtrToAsmRecord temp=(AsmQueue)malloc(sizeof(struct AsmCommandRecord));
	temp->next=Q->next;
	temp->next->next->previous=Q;
	Q->next=temp->next->next;
	free(temp->next);
	free(temp);
}
/*a function to empty the queue*/
void EmptyAsmQueue(AsmQueue Q)
{
	while(IsAsmQueueEmpty(Q)==FALSE)
	{
		RemoveRecordFromAsmQueue(Q);
	}
}
/*creates an array to hold such queues in a given length*/
AsmQueue **CreateAsmQueueArray(int arraySize)
{
	AsmQueue **asmQueueArray=(AsmQueue**)malloc(arraySize*sizeof(AsmQueue*));
	return asmQueueArray;
}
