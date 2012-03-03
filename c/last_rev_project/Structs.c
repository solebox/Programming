#include <string.h>
#include <stdlib.h>
#include "Structs.h"

opcode GetOpcodeDefinition(char op[],opcode opcodesList[])
{
	int i;
	opcode temp;
	char* tempOpName;
	strcpy(temp.op,"?");
	/*FIX_NULL_STRING(tempOpName);*/
	tempOpName=(char*)malloc(sizeof(char));
	for(i=0;i<OPCODE_COUNT;i++)
	{
		strcpy(tempOpName,opcodesList[i].op);
		if(strcmp(tempOpName,op)==0)
			return opcodesList[i];
	}
	return temp;

}
