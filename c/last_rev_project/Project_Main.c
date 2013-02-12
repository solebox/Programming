#include <stdio.h>
#include <malloc.h>
#include "InitializationFunctions.h"
#include "Global_Defines.h"
#include "WorkFlow.h"

/*this program is a two pass assambler , without linker/loader support
	this project was written by - tomer zilka and jacob (koby) kilimnik*/
int main(int argc,char* argv[])
{
	char **fileNames=ObtainFileNames(argc-1,argv);
	FirstPass(fileNames,argc-1);
	if(WasThereCompilingError()==TRUE)
		printf("There were compiling errors, cannot continue to second pass\n");
	else
		SecondPass(fileNames[0]);
	return 1;
}
