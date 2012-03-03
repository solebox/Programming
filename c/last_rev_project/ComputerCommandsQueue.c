#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ComputerCommandsQueue.h"
/*the command queue initializer function*/
CmdQueue CreateCmdQueue()
{
	CmdQueue Q=(CmdQueue)malloc(sizeof(struct _CmdRec));
	if(Q==NULL)
		ErrorHandler(OutOfMemory,"While creating commands queue");
	Q->next=Q;
	Q->previous=Q;
	return Q;
}
/*checks if a given queue is empty
Q - the head of the cmd queue to check
return value - true full/false empty */
enum Boolean IsCmdQueueEmpty(CmdQueue Q)
{
	if(Q->next==Q)
		return TRUE;
	else
		return FALSE;
		
}
/*function adds element to command queue*/
void CmdQueue_AddRecord(Cmd item, CmdQueue Q)
{
	PtrToCmdRecord newRecord=(CmdQueue)malloc(sizeof(struct _CmdRec));
	if(newRecord==NULL)
		ErrorHandler(OutOfMemory,"While creating new commad queue record.");
	newRecord->_command=item;
	if(IsCmdQueueEmpty(Q)==TRUE)
		Q->next=newRecord;
	newRecord->previous=Q->previous;
	Q->previous=newRecord;
	newRecord->next=Q;
	newRecord->previous->next=newRecord;
}
/*returns the next element in line(dequeue)*/
Cmd RetrieveRecord(CmdQueue Q)
{
	Cmd record;
	if(IsCmdQueueEmpty(Q)==FALSE)
	{
		PtrToCmdRecord temp=(CmdQueue)malloc(sizeof(struct _CmdRec));
		temp->next=Q->next->next;
		record=Q->next->_command;
		free(Q->next);
		Q->next=temp->next;
		Q->next->previous=Q;
		free(temp);
		return  record;
	}
	return NULL;

}
/* function removes an element without retriving it*/
void RemoveRecordFromCmdQueue(CmdQueue Q)
{
	PtrToCmdRecord temp=(CmdQueue)malloc(sizeof(struct _CmdRec));
	temp->next=Q->next;
	temp->next->next->previous=Q;
	Q->next=temp->next->next;
	free(temp->next);
	free(temp);
}
/*function removes all elements from command queue*/
void EmptyCmdQueue(CmdQueue Q)
{
	while(IsCmdQueueEmpty(Q)==FALSE)
	{
		RemoveRecordFromCmdQueue(Q);
	}
}
BinaryMachineCode CreateBmcCode(char *binaryNumber)
{
	BinaryMachineCode newCode;
	newCode.a=NULL;
	newCode.b=NULL;
	newCode.c=NULL;
	newCode.d=NULL;
	newCode.e=NULL;
/*	ALLOCATE_STRING(newCode.a,4);*/
	FIX_NULL_STRING(newCode.a);
	FIX_NULL_STRING(newCode.b);
	FIX_NULL_STRING(newCode.c);
	FIX_NULL_STRING(newCode.d);
	FIX_NULL_STRING(newCode.e);
	strncpy(newCode.a,binaryNumber,4);
	/*newCode.a[sizeof(newCode.a)-1]='\0';*/
	binaryNumber+=4;
	strncpy(newCode.b,binaryNumber,3);
	/*newCode.b[sizeof(newCode.b)-1]='\0';*/
	binaryNumber+=3;
	strncpy(newCode.c,binaryNumber,3);
	/*newCode.c[sizeof(newCode.c)-1]='\0';*/
	binaryNumber+=3;
	strncpy(newCode.d,binaryNumber,3);
	/*newCode.d[sizeof(newCode.d)-1]='\0';*/
	binaryNumber+=3;
	strncpy(newCode.e,binaryNumber,3);
	/*newCode.e[sizeof(newCode.e)-1]='\0';*/

	return newCode;
}
/*helper function to create a command representation object*/
Cmd CreateCmdObject(char* labelName,char decimal_address[],	char base_12_address[],	char* command,	char* operands,	BinaryMachineCode bmc,char base_12_machine_code[],char kind)
{
	Cmd item=(Cmd)malloc(sizeof(struct CmdStructure));
	char *tempc=NULL;
	int len;
	FIX_NULL_STRING(tempc);
	len=strlen(labelName);
	item->labelName=(char*)malloc(len+1);
	strcpy(item->labelName,labelName);

	item->labelName[len]='\0';

	len=strlen(operands);
	item->operands=(char*)malloc(len+1);
	strcpy(item->operands,operands);
	item->operands[len]='\0';

	strcpy(item->decimal_address,decimal_address);
	item->decimal_address[MAX_ADDRESS_DIGITS]='\0';
	strcpy(item->base_12_address,base_12_address);
	item->base_12_address[MAX_ADDRESS_DIGITS]='\0';

	len=strlen(command);
	item->command=(char*)malloc(len+1);
	strcpy(item->command,command);
	item->command[len]='\0';

	item->bmc=bmc;


	strcpy(tempc,item->labelName);
	strcpy(item->base_12_machine_code,base_12_machine_code);

	item->kind=kind;
	return item;
}
/* function converts a command element to a string ,*/
char *ConvertCmdToString(Cmd command,char *Scommand)
{
	int len;
	Scommand= AddMachineFieldToTemplate(Scommand,command->labelName);
	Scommand= AddMachineFieldToTemplate(Scommand,command->decimal_address);
	Scommand= AddMachineFieldToTemplate(Scommand,command->base_12_address);
	Scommand= AddMachineFieldToTemplate(Scommand,command->command);
	Scommand= AddMachineFieldToTemplate(Scommand,command->operands);
	Scommand= AddMachineFieldToTemplate(Scommand,convertBinaryMachineCodeToString(command->bmc,PrintStyle));
	Scommand= AddMachineFieldToTemplate(Scommand,command->base_12_machine_code);
	Scommand= AddMachineFieldToTemplate(Scommand,&(command->kind));

	len= strlen(Scommand)+2;
	Scommand=(char*)realloc(Scommand,len);
	Scommand[len-2]='\n';
	Scommand[len-1]='\0';
	return Scommand;
}
char* AddMachineFieldToTemplate(char *command,char *itemToAdd)
{
	enum Boolean first;
	int len,commandLength;
	if(command==NULL)
		first=TRUE;
	else
		first=FALSE;
	if(first==TRUE)	
		commandLength=0;
	else
		commandLength=strlen(command);
	len = strlen(itemToAdd);
	len+=2;
	commandLength+=len;
	command=(char*)realloc(command,commandLength);
	if(len==3)
		command[commandLength-3]=itemToAdd[0];
		else
		{
		if(first==TRUE)
			strcpy(command,itemToAdd);
		else
			strcat(command,itemToAdd);
		}
	command[commandLength-2]=' ';
	command[commandLength-1]='\0';

	return command;
}
/* function converts binary machine code to string */
char *convertBinaryMachineCodeToString(BinaryMachineCode bmc,enum StringStyle style)
{
	char *code=NULL;
	if(style==BmcStyle)
		ALLOCATE_STRING(code,BMC_LENGTH+1)
	else
		ALLOCATE_STRING(code,BMC_LENGTH+5) /* additional spots for spaces */

	strcpy(code,bmc.a);
	if(style==PrintStyle)
		strcat(code," ");
	strcat(code,bmc.b);
	if(style==PrintStyle)
	strcat(code," ");
	strcat(code,bmc.c);
	if(style==PrintStyle)
	strcat(code," ");
	strcat(code,bmc.d);
	if(style==PrintStyle)
	strcat(code," ");
	strcat(code,bmc.e);
	if(style==BmcStyle)
		code[BMC_LENGTH]='\0';
	else
		code[BMC_LENGTH+5]='\0';

	return code;
}
/*changes the binary machine code in a  binary machine code element*/
BinaryMachineCode AlterBmcValue(enum BmcField field,int value,BinaryMachineCode bmc)
{
	char* tmp=NULL;
	switch(field)
	{
	case BmcSrcAddType:
	case BmcSrcReg:
	case BmcDstAddType:
	case BmcDstReg:
			ALLOCATE_STRING(tmp,3);
			tmp=ConvertIntToCharByBase(value,ConversionToBmcOpRegField,2);
			break;
	case BmcOperationCode:
			ALLOCATE_STRING(tmp,4);
			tmp=ConvertIntToCharByBase(value,ConversionToBmcOpCode,2);

		break;
	default:
		break;
	}
	switch(field)
	{
	case BmcSrcAddType:
		strcpy(bmc.b,tmp);
		break;
	case BmcSrcReg:
		strcpy(bmc.c,tmp);
		break;
	case BmcDstAddType:
		strcpy(bmc.d,tmp);
		break;
	case BmcDstReg:
		strcpy(bmc.e,tmp);
			break;
	case BmcOperationCode:
		strcpy(bmc.a,tmp);
		break;
	default:
		break;
	}
	return bmc;
}
/*
void PrintComputerCommandsQueue(CmdQueue Q)
{
	Cmd tempRecord=NULL;
	printf("Label|\tDecimal Address|\tBase 12 Address|\tCommand|\tOperands|\tBinary Machine Code|\tBase 12 Machine Code|\tKind\n");
	while(IsCmdQueueEmpty(Q)==FALSE)
	{
		if(tempRecord==Q->next)
			break;
		tempRecord=RetrieveRecord(Q);
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%c\n",tempRecord->labelName,tempRecord->decimal_address,tempRecord->base_12_address,tempRecord->command,tempRecord->operands,convertBinaryMachineCodeToString(tempRecord->bmc,PrintStyle),tempRecord->base_12_machine_code,tempRecord->kind);
	}
}
*/
/* Sort */

CmdQueue KindOfSort_CmdQ(CmdQueue Q)
{
	CmdQueue sortedQueue,temp;
	int items=0,i=0,t1,t2,rounds=0;
	char *max=NULL,*min=NULL,*tempC=NULL;
	temp=Q->next;
	sortedQueue=CreateCmdQueue();
	FIX_NULL_STRING(max);
	FIX_NULL_STRING(min);
	strcpy(max,"0");
	while(temp!=Q)
	{
		items++;
		if(strcmp(max,temp->_command->decimal_address)==-1)
			strcpy(max,temp->_command->decimal_address);
		temp=temp->next;
	}
	temp=Q->next;
	strcpy(min,max);
	while(temp!=Q)
	{
		if(strcmp(min,temp->_command->decimal_address)==1)
			strcpy(min,temp->_command->decimal_address);
		temp=temp->next;
	}
	FIX_NULL_STRING(tempC);
	temp=Q->next;
	for(i=0;i<items;)
	{

		if(temp==Q)
		{
			temp=temp->next;
			rounds++;
		}
		t1=ConvertCharToInt(temp->_command->decimal_address);
		t2=ConvertCharToInt(min)+i;
		if(t1==t2)
		{
			CmdQueue_AddRecord(temp->_command,sortedQueue);
			temp->previous->next=temp->next;
			i++;
			rounds=0;
		}
		temp=temp->next;
		if(rounds>=2)
		{
			i++;
			SetCompilingError();

		}
	}
	return sortedQueue;
}


