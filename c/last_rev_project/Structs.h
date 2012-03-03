#include <stdio.h>
#include "Global_Defines.h"
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct
{
	char op[4];
	int value_8;
	int operand_count;
	int adddressing_type_src[MAX_ADDRESSING_AMOUNT];
	int adddressing_type_dst[MAX_ADDRESSING_AMOUNT];

}opcode;

opcode GetOpcodeDefinition(char op[], opcode opcodesList[]);



#endif
