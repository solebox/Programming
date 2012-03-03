#include <stdio.h>
#include "miscellaneous.h"
#include "Global_Defines.h"
#include "Enums.h"

#ifndef _CommandsQueue_
#define _CommandsQueue_
struct _CmdRec;
typedef struct _CmdRec *PtrToCmdRecord;
typedef struct CmdStructure *Cmd;
typedef PtrToCmdRecord CmdQueue;
/*
typedef struct
{
	char a[5];
	char b[4];
	char c[4];
	char d[4];
	char e[4];

}BinaryMachineCode;
*/
typedef struct
{
	char *a;
	char *b;
	char *c;
	char *d;
	char *e;

}BinaryMachineCode;
struct CmdStructure
{
	char* labelName;
	char decimal_address[MAX_ADDRESS_DIGITS+1];
	char base_12_address[MAX_ADDRESS_DIGITS+1];
	char* command;
	char* operands;
	BinaryMachineCode bmc;
	char base_12_machine_code[9];
	char kind;
};
struct _CmdRec
{
	Cmd _command;
	PtrToCmdRecord next;
	PtrToCmdRecord previous;
};

CmdQueue CreateCmdQueue();
enum Boolean IsCmdQueueEmpty(CmdQueue queue);
Cmd RetrieveRecord(CmdQueue queue);
void CmdQueue_AddRecord(Cmd item, CmdQueue queue);
void RemoveRecordFromCmdQueue(CmdQueue Q);
void EmptyCmdQueue(CmdQueue queue);
Cmd CreateCmdObject(char* labelName,char decimal_address[],	char base_12_address[],	char* command,	char* operands,	BinaryMachineCode bmc,char base_12_machine_code[],char kind);
BinaryMachineCode CreateBmcCode(char *binaryNumber);
char  *ConvertCmdToString(Cmd command,char *Scommand);
char* AddMachineFieldToTemplate(char *command,char *itemToAdd);
char *convertBinaryMachineCodeToString(BinaryMachineCode bmc, enum StringStyle style);
BinaryMachineCode AlterBmcValue(enum BmcField field,int value,BinaryMachineCode bmc);
/*void PrintComputerCommandsQueue(CmdQueue Q);*/
CmdQueue KindOfSort_CmdQ(CmdQueue Q);
#endif

