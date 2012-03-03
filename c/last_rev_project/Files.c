
#include "Files.h"
/*a method that simply opens a file and returns a FILE pointer */
FILE *openFile(char *filename,char* mode)
{
	FILE *fp;
	fp=fopen(filename,mode);
	if(fp==NULL)
	{
		ErrorHandler(UnableToOpenFile,filename);
	}
	return fp;
}
/* this method takes the command queue filename and counters and writes
the .ob file for the processed assambly file
ic - the instruction counter
dc - the data counter
CmdQueue -the command queue
filename - the asm filename
*/
void WriteObjFile(char *filename,CmdQueue Q,int ic,int dc)
{
	FILE *fp;
	char *fullFilename=NULL;
	Cmd tempRecord=NULL;
	FIX_NULL_STRING(fullFilename);
	fullFilename=CreateFileName(filename,FILE_OB);
	fp=openFile(fullFilename,"wt");
	if(fp==NULL)
		ErrorHandler(UnableToWriteFile,"for writing output");
/* i was confused which layout should be, because there were conflicting definitions of what was needed to do.
   tp prevent a mistake in the layout i left the 2 options in the sourcecode, please uncomment the next printf section and comment the other to get the alternative layout.
 */

/*
	fprintf(fp,"Label|\tDecimal Address|\tBase 12 Address|\tCommand|\tOperands|\tBinary Machine Code|\tBase 12 Machine Code|\tKind\n");

	fprintf(fp,"\t\t\t\t\t%s %s\n",ConvertIntToCharByBase(ic-IC_STARTING_ADDRESS,ConversionToSimple,12),ConvertIntToCharByBase(dc,ConversionToSimple,12));

	while(IsCmdQueueEmpty(Q)==FALSE)
	{
		tempRecord=RetrieveRecord(Q);
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%c\n",tempRecord->labelName,tempRecord->decimal_address,tempRecord->base_12_address,tempRecord->command,tempRecord->operands,convertBinaryMachineCodeToString(tempRecord->bmc,PrintStyle),tempRecord->base_12_machine_code,tempRecord->kind);
	}
*/

	fprintf(fp,"Base 12 Address|\tBase 12 Machine Code|\tKind\n");

	fprintf(fp,"\t\t\t%s %s\n",ConvertIntToCharByBase(ic-IC_STARTING_ADDRESS,ConversionToSimple,12),ConvertIntToCharByBase(dc,ConversionToSimple,12));

	while(IsCmdQueueEmpty(Q)==FALSE)
	{
		tempRecord=RetrieveRecord(Q);
		fprintf(fp,"%s\t%s\t%c\n",tempRecord->base_12_address,tempRecord->base_12_machine_code,tempRecord->kind);
}

	fclose(fp);
}
FILE **CreateInputFileArray(char **files,int filesCount)
{
	int fileCounter,stringlength;
	char *tempFilename=NULL;
	FILE **filesP;
	filesP=(FILE**)malloc(sizeof(FILE*)*filesCount);
	for(fileCounter=0;fileCounter<filesCount;fileCounter++)
	{
		stringlength=strlen(files[fileCounter])+strlen(INPUTFILE_EXT);
		ALLOCATE_STRING(tempFilename,stringlength);
		strcpy(tempFilename,files[fileCounter]);
		strcat(tempFilename,INPUTFILE_EXT);
		(filesP[fileCounter])=openFile(tempFilename,"r");
	}
	return filesP;
}
char *ReadLineFromFile(FILE *fp,long fileSize)
{
	static enum Boolean fileEnd;
	char *tempInputCommand,*tempC;
	int letterCounter=0;
	int tTell;

	if(fileEnd==TRUE)
		{
		fileEnd=FALSE;	
			return NULL;
	}
	tempC=(char*)malloc(sizeof(char));
	
		tempInputCommand=(char*)malloc(sizeof(char));
		do
		{
			letterCounter++;
			fscanf(fp,"%c",tempC);
			tTell=ftell(fp);
			if(tTell>=fileSize)
				fileEnd=TRUE;

			tempInputCommand=(char*)realloc(tempInputCommand,letterCounter*sizeof(char));
			tempInputCommand[letterCounter-1]=*tempC;

		}
		while((*tempC)!='\n' && fileEnd==FALSE);
		if(fileEnd==TRUE)
			tempInputCommand=(char*)realloc(tempInputCommand,(++letterCounter)*sizeof(char));
		tempInputCommand[letterCounter-1]='\0';
		return tempInputCommand;
}
long GetFileSize(FILE *fp)
{
	long size;
	fseek(fp,0L,SEEK_END);
	size=ftell(fp);
	fseek(fp,0L,0);
	
	return size;
}
void WriteExtAndEntFiles(char* fileName,LinkedList_Linkage *linkage)
{
	linkageNode *tempNode,*minimum;
	LinkedList_Linkage tempList;
	FILE** files=(FILE**)malloc(sizeof(FILE*)*2);
	char *f1=NULL,*f2=NULL;
	(&tempList)->next=NULL;
	f1=CreateFileName(fileName,FILE_ENT);
	f2=CreateFileName(fileName,FILE_EXT);
	files[0]=openFile(f1,"wt");/* entry file  */
	files[1]=openFile(f2,"wt");/* externals file  */
	while(tempNode=RetreiveLinkageItem(linkage))
	{
		switch(tempNode->directive)
		{
		case ENTRY:
			AddLinkageItem(&tempList,tempNode->directive,tempNode->name,tempNode->lineNumber);
			break;
		case EXTERN:
			fprintf(files[1],"%s\t%s\n",tempNode->name,tempNode->lineNumber);

			break;
		default:
			break;
		}
	}
	tempNode=NULL;
	minimum=NULL;
	while(1)
	{
		if((&tempList)->next==NULL)
			break;
		if(minimum==NULL)
			minimum=(&tempList)->next;
		if(tempNode==NULL)
			tempNode=(&tempList)->next;
		if((&tempList)->next==NULL)
		{
			fprintf(files[0],"%s\t%s\n",minimum->name,minimum->lineNumber);
			RemoveItemFromLinkageList(&tempList,minimum->lineNumber,minimum->name);
			break;		
		}
		if(strcmp(minimum->lineNumber,tempNode->lineNumber)==1)
			minimum=tempNode;
		if(tempNode->next==NULL)
		{
			fprintf(files[0],"%s\t%s\n",minimum->name,minimum->lineNumber);
			RemoveItemFromLinkageList(&tempList,minimum->lineNumber,minimum->name);
			minimum=(&tempList)->next;
			tempNode=(&tempList)->next;
			continue;
		}

		tempNode=tempNode->next;
		
	}

	if(GetFileSize(files[0])==0)
	{
		fclose(files[0]);/* close file before removing it */
			if(remove(f1)==-1)
				ErrorHandler(UnableToDeleteTempFile,f1);
	}
	else
		fclose(files[0]);/* close file if not removing it */

	if(GetFileSize(files[1])==0)
	{
		fclose(files[1]);
			if(remove(f1)==-1)
				ErrorHandler(UnableToDeleteTempFile,f2);
	}
	else
		fclose(files[1]);

}
char* CreateFileName(char *filename,enum FileExtension extension)
{
	char *fullFileName=NULL;
	if(filename==NULL || strlen(filename)==0)
		ErrorHandler(UnableToWriteFile,"filename is illegal");
	FIX_NULL_STRING(fullFileName);
	strcpy(fullFileName,filename);
	switch(extension)
	{
	case FILE_ENT:
		strcat(fullFileName,".ent");
		break;
	case FILE_OB:
		strcat(fullFileName,".ob");
		break;

	case FILE_EXT:
		strcat(fullFileName,".ext");
		break;
	default:
		break;

	}
	return fullFileName;
}

