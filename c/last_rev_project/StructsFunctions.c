#include <string.h>
#include "Structs.h"
#include "Global_Defines.h"

opcode* ReturnOpcodeValue(opcode* _list,char opcodeName[]) /*returns -1 if opcode is not found.*/
{
	int i;
	for(i=0;i<OPCODE_COUNT;_list++)
		if(strcmp(_list->op,opcodeName)==0)
			return _list;
	return NULL;
}
