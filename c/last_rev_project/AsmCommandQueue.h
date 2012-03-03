#include <stdio.h>
#include "miscellaneous.h"
#include "Global_Defines.h"
#include <malloc.h>


struct AsmCommandRecord;
typedef struct AsmCommandRecord *PtrToAsmRecord;
typedef struct CmdStructure *Asm;
typedef PtrToAsmRecord AsmQueue;
struct AsmCommandRecord
{
	char *asmString;
	PtrToAsmRecord next;
	PtrToAsmRecord previous;
};

AsmQueue CreateAsmQueue();
enum Boolean IsAsmQueueEmpty(AsmQueue queue);
char *RetrieveAsmRecord(AsmQueue queue);
void AsmQueue_AddRecord(char *asmCommand, AsmQueue queue);
void RemoveRecordFromAsmQueue(AsmQueue Q);
void EmptyAsmQueue(AsmQueue queue);
AsmQueue **CreateAsmQueueArray(int arraySize);
/*
void DisposeCmdStack(CmdQueue queue);
void CmdQueue_Remove(CmdQueue queue);
*/