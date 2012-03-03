#define OPCODE_COUNT 16
#define MAX_ADDRESS_DIGITS 4
#define BASE_12_MACHINE_CODE_DIGITS 7
#define BMC_LENGTH 16
#define INPUTFILE_EXT ".as"
#define MINIMUM_STRING_LENGTH 2 /* logically */
#define DATA_INSTRUCTION ".data"
#define STRING_INSTRUCTION ".string"
#define EXTERN_INSTRUCTION ".extern"
#define ENTRY_INSTRUCTION ".entry"
#define MAX_ADDRESSING_AMOUNT 5
#define BMC_OPCODE_LENGTH 4
#define BMC_REG_LENGTH 3
#define IC_STARTING_ADDRESS 100
/* pre-defined functions */

#define NOT_ENOUGH_MEMORY {\
	ErrorHandler(OutOfMemory,"while trying to dynamicaly allocate memory");\
	}
#define FIX_NULL_STRING(STRING){\
	if(STRING==NULL){\
		STRING=(char*)malloc(sizeof(char));\
		STRING[0]='\0';\
		}\
	}
#define ALLOCATE_STRING(STRING,STR_LENGTH){\
	if(STRING==NULL){\
		STRING=(char*)malloc(STR_LENGTH*sizeof(char));\
	}\
	else {\
		STRING=(char*)realloc(STRING,STR_LENGTH*sizeof(char));\
		}\
 }
