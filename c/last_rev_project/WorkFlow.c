#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "WorkFlow.h"

FILE static **_FilesList;
static AsmQueue **_AssemblerCommandsQueue;
static labelNode *_labels;
static CmdQueue computerLanguage;
static int IC=IC_STARTING_ADDRESS;
static int DC;
static const char DELIMITERS[]={' ',':',',','\t','\0','\r','\n'};
static opcode *opcodes;
static int* zeroPointer;
static int zero=0;
static LinkedList_Linkage Linkage_List;
/*this function starts the first pass procedure*/
void FirstPass(char **files,int filesCount)
{
	static int zeroInt;
	zeroPointer=&zeroInt;
	printf("\nBegining first pass...\r");
	FirstPassInitialization(files,filesCount);
	ReadFiles(filesCount);
}
/*this function starts the first pass procedure*/
void SecondPass(char* fileName)
{
	CmdQueue layoutQueue;
	Cmd tempRecord;
	printf("\nBegining second pass...\n");
	CalculateAddressesForLabels(_labels,IC);
	UpdateEntryLabels(&Linkage_List,_labels);
	layoutQueue=CreateCmdQueue();
	while(IsCmdQueueEmpty(computerLanguage)==FALSE)
	{
		tempRecord=RetrieveRecord(computerLanguage);
		AddItemToLayout(tempRecord,layoutQueue);
	}
	layoutQueue=KindOfSort_CmdQ(layoutQueue);
	if(WasThereCompilingError()==TRUE)
		ErrorHandler(FatalError," cannot proceed!\n");
	WriteObjFile(fileName,layoutQueue,IC,DC);
	WriteExtAndEntFiles(fileName,&Linkage_List);
	printf("\nCompilation was successful, files were created.\n");
}
void FirstPassInitialization(char **files,int filesCount)
{
	computerLanguage=CreateCmdQueue();
	_FilesList=CreateInputFileArray(files,filesCount);
	_AssemblerCommandsQueue=CreateAsmQueueArray(filesCount);
	_labels=CreateLabelNode();
	IC=100;
	DC=0;
	zeroPointer=&zero;
	opcodes = InitializeOpcodeList(opcodes);
}
void ReadFiles(int filesCount)
{
	int FCounter;
	for(FCounter=0;FCounter<filesCount;FCounter++)
	{
		_AssemblerCommandsQueue[FCounter]=CreateAsmQueue();
		ReadFile(FCounter);
	}
}
void ReadFile(int index)
{
		long fileSize=0;
		char *tempInputCommand;
		fileSize=GetFileSize(_FilesList[index]);
		do{
		tempInputCommand=ReadLineFromFile(_FilesList[index],fileSize);
		if(tempInputCommand==NULL)
			break;
		tempInputCommand= StringTrim(tempInputCommand);

		if(AnalyzeText(tempInputCommand)==TRUE) /*analyze line */
		{
			AsmQueue_AddRecord(tempInputCommand,_AssemblerCommandsQueue[index]);
		}
		}
		while(1);
}
enum Boolean AnalyzeText(char *tempInputCommand)
{
		enum Boolean labelFound=FALSE,firstField=TRUE,handleLineDone=FALSE;
		char *directive=NULL;
		enum ItemType type;
		char *tempItem=NULL;
		char *label=NULL,*command=NULL,*operands=NULL;
		int loc=0;
		enum Directive currentDirective;
		int *curLoc,stringLength;


		curLoc=&loc;

		stringLength=strlen(tempInputCommand);
		if(strlen(tempInputCommand)==0 || strcmp(tempInputCommand,"")==0)
				return FALSE;
		if(tempInputCommand[0]==';')
			return FALSE;
		while((*curLoc)<stringLength && handleLineDone==FALSE)
		{
			tempItem=ReadWord(tempInputCommand,curLoc,' ');

			tempItem=StringTrim(tempItem);
			if(tempItem[strlen(tempItem)-1]==':')
			{
					type=TLabel;
					labelFound=TRUE;
			}
			else if(tempItem[0]=='.')
					type=TDirective;
			else
				type=TCommand;

			switch(type)
			{
			case TDirective:
				/*directive*/

				ALLOCATE_STRING(directive,strlen(tempItem));
				strcpy(directive,tempItem);

				/* Create BMC  */
				CreateBmc(tempInputCommand+(*curLoc),directive,type,label,command,operands);
				handleLineDone=TRUE;
				currentDirective=WhatDirective(directive);

				if(currentDirective!=EXTERN && currentDirective !=ENTRY)
					HandleDirective(tempInputCommand,label,directive);	
				else
				{
					operands=ReadWord(tempInputCommand,curLoc,' ');
					operands=StringTrim(operands);
					FIX_NULL_STRING(operands);
					AddLinkageItem(&Linkage_List,currentDirective,operands,"?");
				}

					break;
			case TCommand:
				AnalyzeCommand(tempInputCommand);
				handleLineDone=TRUE;
					break;
			case TLabel:
				label=(char*)malloc(sizeof(char));
				label=HandleLabel(tempItem,tempInputCommand,curLoc);
					break;
				default: /* cosmetics only*/
					break;
			}
			firstField=FALSE;

		}
return TRUE;
}
enum Boolean IsLabel(char *string)
{
	return TRUE;
}
char *ReadWord_by_value(char *text,int curLoc,char specificDelimiter)
{
	char *tempItem=NULL,*tempText=NULL;
	enum Boolean delimiterFound=FALSE,inQuotes=FALSE;
	int i;
/*	if(specificDelimiter==NULL)
		specificDelimiter=' ';*/
	tempText = StringTrim(text+curLoc);
		if(strlen(tempText)==0)
			return NULL;

		for(i=0;delimiterFound==FALSE;i++)
		{
			if(tempText[i]=='\"')
				if(inQuotes==TRUE)
					inQuotes=FALSE;
				else		
					inQuotes=TRUE;
			else
				if(IsDelimiter(tempText[i],specificDelimiter)==TRUE)
						{
							delimiterFound=TRUE;
							if(i==0)
							{
								delimiterFound=FALSE;
								break;
							}							
							if(tempText[i]==':')
							{

									tempItem=(char*)realloc(tempItem,(i+1)*sizeof(char));
									tempItem[i]=tempText[i];
									i++;
							}
							else if(tempText[i]==' ' && inQuotes==TRUE)
							{
							delimiterFound=FALSE;
							tempItem=(char*)realloc(tempItem,(i+1)*sizeof(char));
							tempItem[i]=tempText[i];
								continue;
							}
							tempItem=(char*)realloc(tempItem,(i+1)*sizeof(char));
							tempItem[i]='\0';	
							break;
						
						}
				
			if(delimiterFound==FALSE)
			{
				tempItem=(char*)realloc(tempItem,(i+1)*sizeof(char));
				tempItem[i]=tempText[i];
			}
		}
		return tempItem;


}
char *ReadWord(char *text,int* curLoc,char specificDelimiter) /* white space fix (bug fix: input changed to "by reference") */
{
	char *tempItem=NULL,*tempText=NULL;
	enum Boolean delimiterFound=FALSE,inQuotes=FALSE;
	int i,newstr_index=0,t;
	/*if(specificDelimiter==NULL)
		specificDelimiter=' ';*/
	if(text==NULL || strlen(text)==0)
		return NULL;
	tempText = StringTrim(text+(*curLoc));
		if(strlen(tempText)==0 || *curLoc>strlen(text))
			return NULL;
		t=strlen(tempText);
		for(i=0;IsDelimiter(tempText[i],' ')==TRUE && i<strlen(tempText);i++,(*curLoc)++)
		{
			continue;
		}
		tempText+=i;
		for(i=0;delimiterFound==FALSE;i++)
		{
			if(tempText[i]=='\"')
				if(inQuotes==TRUE)
					inQuotes=FALSE;
				else		
					inQuotes=TRUE;
			else
					if(IsDelimiter(tempText[i],specificDelimiter)==TRUE)
						{
							delimiterFound=TRUE;
							if(i==0)
							{
								delimiterFound=FALSE;
								continue;
							}							
							if(tempText[i]==':')
							{
								ALLOCATE_STRING(tempItem,++newstr_index);
									tempItem[newstr_index-1]=tempText[i];
									i++;
							}
							else if(tempText[i]==' ' && inQuotes==TRUE)
							{
							delimiterFound=FALSE;
								ALLOCATE_STRING(tempItem,++newstr_index);
									tempItem[newstr_index-1]=tempText[i];
								continue;
							}
							ALLOCATE_STRING(tempItem,++newstr_index);
							tempItem[newstr_index-1]='\0';	
							break;
						
						}
				
			if(delimiterFound==FALSE)
			{
								ALLOCATE_STRING(tempItem,++newstr_index);
									tempItem[newstr_index-1]=tempText[i];
			}
		}
	
		if(tempText[i-1]!=':')
			(*curLoc)+=++i;
		else
			(*curLoc)+=i++; /* include the ':' in the return string to identify it as a label */

		return tempItem;


}
enum Directive WhatDirective(char *text)
{
	enum Directive dir;
		if(text==NULL)
			return NONE;
	if(text[0]!='.')
		return NONE;
	text=ReadWord(text,zeroPointer,' ');
	*zeroPointer=0;
	dir= strcmp(text,STRING_INSTRUCTION)==0?STRING:strcmp(text,DATA_INSTRUCTION)==0?DATA:strcmp(text,ENTRY_INSTRUCTION)==0?ENTRY:strcmp(text,EXTERN_INSTRUCTION)==0?EXTERN:NONE;
	
	return dir;
}
void HandleCommand(char *line,int* curPos,opcode thisOpcode,char* label)
{
	BinaryMachineCode bmc;
	int decimal;
	char *binaryValue=NULL,*base12code=NULL,*param1=NULL,*param2=NULL;
	int addressingType1=NULL,addressingType2=NULL;
	enum Boolean errorFound=FALSE;
	Cmd tempCommand;
		char* errmsg=NULL;


	switch(thisOpcode.operand_count)
	{
	case 0:
		param1=ReadWord(line,curPos,' ');
		if(param1==NULL)
			FIX_NULL_STRING(param1);
		param1=StringTrim(param1);

		if(strlen(param1)>0 && IsDelimiter(param1[0],' ')==FALSE)
		{
			ALLOCATE_STRING(errmsg,50);
			strcpy(errmsg,thisOpcode.op);

			strcat(errmsg," - too many arguments for command ");
			ErrorHandler(CompilingError,errmsg);
			printf("b");
			return;
		}
		decimal=OctalToDecimal(thisOpcode.value_8);
		FIX_NULL_STRING(binaryValue);

		strcpy(binaryValue,ConvertIntToCharByBase(0,ConversionToBmcType,2));
		bmc = CreateBmcCode(binaryValue);

		bmc=AlterBmcValue(BmcOperationCode,OctalToDecimal(thisOpcode.value_8),bmc);
		/*strcpy(,convertBinaryMachineCodeToString(bmc,PrintStyle));

		strcpy(binaryValue,ConvertIntToCharByBase(decimal,ConversionToBmcType,2));
		ALLOCATE_STRING(bmcString,BMC_LENGTH+2);
		strcpy(bmcString,binaryValue);
		for(i=strlen(binaryValue);i<BMC_LENGTH;i++)
			bmcString[i]='0';
		bmcString[i]='\0';
		*/
		FIX_NULL_STRING(label);
		/*bmc=CreateBmcCode(bmcString);*/
		FIX_NULL_STRING(base12code);
		strcpy(base12code,ConvertBinaryStringToBase12(convertBinaryMachineCodeToString(bmc,BmcStyle)));
		tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(IC,ConversionToAddress,10),ConvertIntToCharByBase(IC,ConversionToAddress,12),thisOpcode.op,"",bmc,base12code,'a');
		IC++;
		CmdQueue_AddRecord(tempCommand,computerLanguage);
		break;
	case 1:
		param2=ReadWord(line,curPos,' ');
		if(param2==NULL)
		{
			ALLOCATE_STRING(errmsg,50);
			strcpy(errmsg,thisOpcode.op);
			strcat(errmsg," - too few arguments for command ");
			ErrorHandler(CompilingError,errmsg);
			return;
		}
		addressingType2=IdentifyAddressing(param2);
		if(IsAddressingAllowedForCommand(addressingType2, thisOpcode.adddressing_type_dst)==FALSE)
		{
			ErrorHandler(CompilingError,"operand is not allowed for this command");
			errorFound=TRUE;
			return;
		}
		param1=ReadWord(line,curPos,' ');
		if(param1!=NULL && strlen(param1)>0)
		{
			ALLOCATE_STRING(errmsg,50);
			strcpy(errmsg,thisOpcode.op);
			strcat(errmsg," - too many arguments for command ");
			ErrorHandler(CompilingError,errmsg);
			return;
		}
		CreateBmcForCommand(line,label,thisOpcode,param1,param2,NULL,addressingType2);
		break;
	case 2:
		param1=ReadWord(line,curPos,' ');
		param2=ReadWord(line,curPos,' ');
		if(param1==NULL || param2==NULL)
		{
			ALLOCATE_STRING(errmsg,50);
			strcpy(errmsg,thisOpcode.op);
			strcat(errmsg," - too few arguments for command: ");
			ErrorHandler(CompilingError,errmsg);
			return;
		}
		if(ReadWord(line,curPos,' ') !=NULL)
		{
			ALLOCATE_STRING(errmsg,50);
			strcpy(errmsg,thisOpcode.op);
			strcat(errmsg," - too many arguments for command: ");
			ErrorHandler(CompilingError,errmsg);
			return;
		}
		addressingType1=IdentifyAddressing(param1);/* source */ 
		addressingType2=IdentifyAddressing(param2);/* destination */



		if(IsAddressingAllowedForCommand(addressingType1, thisOpcode.adddressing_type_src)==FALSE)
		{
			ErrorHandler(CompilingError,"operand is not allowed for this command");
			errorFound=TRUE;
		}
		if(IsAddressingAllowedForCommand(addressingType2, thisOpcode.adddressing_type_dst)==FALSE)
		{
			errorFound=TRUE;
			ErrorHandler(CompilingError,"operand is not allowed for this command");
		}
			
		if(errorFound==TRUE)
			return;
		
		CreateBmcForCommand(line,label,thisOpcode,param1,param2,addressingType1,addressingType2);
		
		break;
	default:
		break;
	
	}
}
/* a method that handels "LABELS:" in a given line*/
char *HandleLabel(char* label,char *line,int* loc)
{
	char *temp,*address_10=NULL,*address_12=NULL;
	enum Directive dir;
	label[strlen(label)-1]='\0';
	temp=line+(*loc);
	temp=StringTrim(temp);
	/*ALLOCATE_STRING(address_10,1);
	ALLOCATE_STRING(address_12,1);*/
	FIX_NULL_STRING(address_10);
	FIX_NULL_STRING(address_12);

	if(strlen(temp)==0) /* Label only */
	{
		strcpy(address_10,ConvertIntToCharByBase(IC,ConversionToAddress,10));
		strcpy(address_12,ConvertIntToCharByBase(IC,ConversionToAddress,12));
		AddLabelItem(_labels,label,address_10,address_12,'c');
		IC++;
	}
	else if(temp[0]=='.') /* Label with Directive */
	{
			dir=WhatDirective(temp);
			temp=StringMoveToNextItem(temp);
			temp=StringTrim(temp);
			switch(dir)
			{
			case STRING:
				strcpy(address_10,ConvertIntToCharByBase(DC,ConversionToAddress,10));
				strcpy(address_12,ConvertIntToCharByBase(DC,ConversionToAddress,12));
				AddLabelItem(_labels,label,address_10,address_12,'d');
				break;
				
				break;

			case DATA:
				strcpy(address_10,ConvertIntToCharByBase(DC,ConversionToAddress,10));
				strcpy(address_12,ConvertIntToCharByBase(DC,ConversionToAddress,12));
				AddLabelItem(_labels,label,address_10,address_12,'d');
				break;
			case EXTERN:
			case ENTRY:
				FIX_NULL_STRING(label);
				break;
			case NONE:
				strcpy(address_10,ConvertIntToCharByBase(IC,ConversionToAddress,10));
				strcpy(address_12,ConvertIntToCharByBase(IC,ConversionToAddress,12));
				AddLabelItem(_labels,label,address_10,address_12,'c');
				return NULL;
				break;
			default:
				break;
			}
	}
	else
	{
		AnalyzeCommand(line);
		*loc=strlen(line);
	}
	return label;
}
/* a function that analyzes what the comman is ought to do and if its legal */
char *AnalyzeCommand(char *temp)
{
	char *word,*label=NULL,*cmd=NULL;
	enum Boolean cmdFound=FALSE;
	int *curPos,pos=0;
	opcode op;
	curPos=&pos;
	while(cmdFound==FALSE)
	{
		word=ReadWord(temp,curPos,' ');

		if(word==NULL || strlen(word)==0)
			return NULL;
		if(word[strlen(word)-1]==':')
		{
			ALLOCATE_STRING(label,strlen(word));
			strcpy(label,word);
			label[strlen(label)-1]='\0';
			AddLabelItem(_labels,label,ConvertIntToCharByBase(IC,ConversionToAddress,10),ConvertIntToCharByBase(IC,ConversionToAddress,12),'c');
			continue;
		}
		ALLOCATE_STRING(cmd,strlen(word));
		strcpy(cmd,word);
		cmdFound=TRUE;

	}

	op=GetOpcodeDefinition(cmd,opcodes);
	if(strcmp(op.op,"?")==0)
	{
		ErrorHandler(CompilingError,"command not recognized:"); /* add command to error */
			return NULL;
	}
	else
	{
		HandleCommand(temp,curPos,op,label);
	}
	return op.op;
}
char* ReadAdditionalValues(char* line) /* need to fix in order to use */
{
	char *single=NULL,**multi=NULL;
	int i=0;
	while(line[i]!='\0')
	{
		single=ReadWord(line,0,' ');
		multi=(char**)realloc(multi,(++i)*sizeof(char*));
		multi[i-1]=single;
	}
	multi[++i]='\0';
	return single;
}
void HandleDirective(char* tempInputCommand,char* label,char* Directive)
{
	
}
/* this function creates the binary machine code for all its given parameters*/
void CreateBmc(char* inputCommand,char* directive,enum ItemType type,char *label,char* command,char* operands)
{
	enum Directive dir;
	char *tempWord=NULL;
	char *tempInputString=StringTrim(inputCommand);
	BinaryMachineCode bmc;
	char *base_12_value=NULL;
	char bmcCreator[BMC_LENGTH+1]={0};
	char newBmc[BMC_LENGTH+1]={0},kind;
	int curLoc=0,castingInteger=0,number_of_items=0,i,*pToCurloc;
	Cmd tempCommand;
	pToCurloc=&curLoc;
	FIX_NULL_STRING(base_12_value);



	switch(type)
	{
	case TCommand:
		AnalyzeCommand(inputCommand);
		break;
	case TDirective:
		dir=WhatDirective(directive);

		switch(dir)
		{
		case STRING:
			kind=' ';
			newBmc[0]='\0';
			tempWord=ReadWord(tempInputString,pToCurloc,' ');
			for(i=0;i<strlen(tempWord);i++)
			{
				if(tempWord[i]=='\"')
					continue;
				castingInteger=(int)tempWord[i];
				strcpy(base_12_value,ConvertIntToCharByBase(castingInteger,ConversionToBase_12_Code,12));
				strcpy(bmcCreator,ConvertIntToCharByBase(castingInteger,ConversionToBmcType,2));
				for(curLoc=0;curLoc<(BMC_LENGTH-strlen(bmcCreator));curLoc++)
				{
					newBmc[curLoc]='0';
				}
				newBmc[curLoc]='\0';
				strcat(newBmc,bmcCreator);
				newBmc[BMC_LENGTH]='\0';
				bmc=CreateBmcCode(newBmc);
				FIX_NULL_STRING(label);

				tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(DC,ConversionToAddress,10),ConvertIntToCharByBase(DC,ConversionToAddress,12),directive,tempInputString,bmc,base_12_value,'d');
				CmdQueue_AddRecord(tempCommand,computerLanguage);
				label="";
				directive="";
				tempInputString="";
				DC++;

			}
			castingInteger=0;
			strcpy(bmcCreator,ConvertIntToCharByBase(0,ConversionToBmcType,2));
			strcpy(base_12_value,ConvertIntToCharByBase(castingInteger,ConversionToBase_12_Code,12));

			for(curLoc=0;curLoc<(BMC_LENGTH-strlen(bmcCreator));curLoc++)
				{
					newBmc[curLoc]='0';
				}
				newBmc[curLoc]='\0';
			strcat(newBmc,bmcCreator);
			bmc=CreateBmcCode(newBmc);
			tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(DC,ConversionToAddress,10),ConvertIntToCharByBase(DC,ConversionToAddress,12),"","",bmc,base_12_value,'d');
			CmdQueue_AddRecord(tempCommand,computerLanguage);
			DC++;

			break;
		case DATA:
			while(tempWord=ReadWord(tempInputString,pToCurloc,' '))
			{
				if(tempWord==NULL)
					break;
				newBmc[0]='\0';
				kind=' ';
				number_of_items++;
				if(IsLegalNumber(tempWord)==FALSE)
				{
					ErrorHandler(CompilingError,"One or more Not-a-number in .data array");
					return;
				}
				castingInteger=ConvertCharToInt(tempWord);

				if(tempInputString[curLoc]==',')
					curLoc++;

				/* Single BMC creation - added to multi BMC link */
				strcpy(bmcCreator, ConvertIntToCharByBase(castingInteger,ConversionToBmcType,2));
				if(tempWord[0]=='-')
					bmcCreator[BMC_LENGTH]='\0';
				for(i=0;i<(BMC_LENGTH-strlen(bmcCreator));i++)
				{
					newBmc[i]='0';
				}

				newBmc[i]='\0';
				FIX_NULL_STRING(label);
				strcat(newBmc,bmcCreator);
				newBmc[BMC_LENGTH]='\0';
				bmc=CreateBmcCode(newBmc);
				FIX_NULL_STRING((base_12_value));
				strcpy(base_12_value,ConvertIntToCharByBase(castingInteger,ConversionToBase_12_Code,12));
				tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(DC,ConversionToAddress,10),ConvertIntToCharByBase(DC,ConversionToAddress,12),directive,inputCommand,bmc,base_12_value,'d');
				CmdQueue_AddRecord(tempCommand,computerLanguage);
				label="";
				DC++;
				inputCommand="";
				directive="";
			}
			break;
			
		case NONE:

			break;
		default:
			break;
		}
		default:
			break;
	}
	

}
enum Boolean IsDelimiter(char test,char specificDelimiter)
{
	int delimiter_index;
	for(delimiter_index=0;delimiter_index<sizeof(DELIMITERS);delimiter_index++) /*  find if current item is string delimiter     */
	{
		if(test==DELIMITERS[delimiter_index] || test==specificDelimiter)
		return TRUE;
	}
	return FALSE;
}
/*function creates binary machine code for a command*/
void CreateBmcForCommand(char* line,char* label,opcode thisOpcode,char* paramSrc,char* paramDst,int addressingTypeSrc, int addressingTypeDst)
{
	BinaryMachineCode bmc;
	int curLoc=0,curLocForSubItem=0,*pToCurloc;
	char *binaryValue=NULL,*bmcString=NULL,*tmpCharNum=NULL,*tmpOperands=NULL,*base_12_value=NULL,*subOperand,*tmpOpVar,*base_10=NULL;
	enum Boolean stopLoop=FALSE;
	Cmd tempCommand;
	pToCurloc=&curLoc;
	FIX_NULL_STRING(binaryValue);
	FIX_NULL_STRING(bmcString);
	FIX_NULL_STRING(base_12_value);
	FIX_NULL_STRING(base_10);
	strcpy(binaryValue,ConvertIntToCharByBase(0,ConversionToBmcType,2));
	bmc = CreateBmcCode(binaryValue);
	
	bmc=AlterBmcValue(BmcOperationCode,OctalToDecimal(thisOpcode.value_8),bmc);
	bmc=AlterBmcValue(BmcSrcAddType,addressingTypeSrc,bmc);
	bmc=AlterBmcValue(BmcDstAddType,addressingTypeDst,bmc);
	if(addressingTypeSrc==4) /* register */
	{
		ALLOCATE_STRING(tmpCharNum,2);
		tmpCharNum[0]=paramSrc[1];
		tmpCharNum[1]='\0';
		bmc=AlterBmcValue(BmcSrcReg,ConvertCharToInt(tmpCharNum),bmc);
	}
	if(addressingTypeDst==4) /* register */
	{
		ALLOCATE_STRING(tmpCharNum,2);
		tmpCharNum[0]=paramDst[1];
		tmpCharNum[1]='\0';
		bmc=AlterBmcValue(BmcDstReg,ConvertCharToInt(tmpCharNum),bmc);
	}

	strcpy(base_12_value,ConvertBinaryStringToBase12(convertBinaryMachineCodeToString(bmc,BmcStyle)));
	/*FIX_NULL_STRING(tmpOperands);*/
	ALLOCATE_STRING(tmpOperands,100);
	if(paramSrc!=NULL) /* when the function being called with two operands */
	{
		strcpy(tmpOperands,paramSrc);
		strcat(tmpOperands,",");
		strcat(tmpOperands,paramDst);
	}
	else/* when the function being called with one operand */
		strcpy(tmpOperands,paramDst);
	FIX_NULL_STRING(label);
	tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(IC,ConversionToAddress,10),ConvertIntToCharByBase(IC,ConversionToAddress,12),thisOpcode.op,tmpOperands,bmc,base_12_value,'a');
	CmdQueue_AddRecord(tempCommand,computerLanguage);
	IC++;
	label="";
	for(;;) /* write additional operands */ 
	{
		if(strlen(tmpOperands+curLoc)==0)
			break;
		subOperand=ReadWord(tmpOperands,pToCurloc,'[');
		if(subOperand==NULL)
			break;
		if(strcmp(subOperand,tmpOperands)==0)
			stopLoop=TRUE;
		if(strlen(subOperand)==0)
			break;
		subOperand=StringTrim(subOperand);
		if(IsMachineRegister(subOperand)==TRUE)
			continue;
		for(;;)
		{
			curLocForSubItem=0;
			pToCurloc=&curLocForSubItem;
			tmpOpVar=ReadWord(subOperand,pToCurloc,']');
			tmpOpVar=StringTrim(tmpOpVar);
			if(IsMachineRegister(tmpOpVar)==TRUE)
			{
			if(*pToCurloc>=strlen(subOperand))
				break;
			else
				continue;
			}
			if(tmpOpVar[0]=='#')
			{
				if(IsLegalNumber(tmpOpVar+1)==FALSE)
					{
						ErrorHandler(CompilingError,"operand errornous");
						return;
					}
				strcpy(binaryValue,ConvertIntToCharByBase(ConvertCharToInt(tmpOpVar+1),ConversionToBmcType,2));
				bmc=CreateBmcCode(binaryValue);
				strcpy(base_12_value,ConvertBinaryStringToBase12(binaryValue));
				ALLOCATE_STRING(base_10,5);
				strcpy(base_10,ConvertIntToCharByBase(IC,ConversionToAddress,10));
				tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(IC,ConversionToAddress,10),ConvertIntToCharByBase(IC,ConversionToAddress,12),"","",bmc,base_12_value,' ');				
			}
			else
			{
				strcpy(binaryValue,ConvertIntToCharByBase(0,ConversionToBmcType,2));
				bmc=CreateBmcCode(binaryValue);
				strcpy(base_12_value,ConvertBinaryStringToBase12(binaryValue));
				ALLOCATE_STRING(base_10,5);
				strcpy(base_10,ConvertIntToCharByBase(IC,ConversionToAddress,10));
				tempCommand=CreateCmdObject(label,ConvertIntToCharByBase(IC,ConversionToAddress,10),ConvertIntToCharByBase(IC,ConversionToAddress,12),"?",tmpOpVar,bmc,base_12_value,' ');
			}
			CmdQueue_AddRecord(tempCommand,computerLanguage);
				IC++;
				if(*pToCurloc>=strlen(subOperand))
					break;
			}
		pToCurloc=&curLoc;



		if(stopLoop==TRUE)
			break;
	}
}
/*adds and item to the final file layout*/
void AddItemToLayout(Cmd tempRecord,CmdQueue layoutQueue)
{
	int relativePos,staticPos,i=0;
	char *tmpItem=NULL,*errmsg=NULL,*binary=NULL;
	char static *rememberMe=NULL;
	labelNode* tmpLabelNode;
	linkageNode* link;
	FIX_NULL_STRING(errmsg);
	FIX_NULL_STRING(rememberMe);
	FIX_NULL_STRING(tmpItem);
	if(tempRecord->kind=='d')/* for .string and .data */
	{
		relativePos=ConvertCharToInt(tempRecord->decimal_address);
		staticPos=IC+relativePos;
		strcpy(tempRecord->decimal_address,ConvertIntToCharByBase(staticPos,ConversionToAddress,10));
		strcpy(tempRecord->base_12_address,ConvertIntToCharByBase(staticPos,ConversionToAddress,12));
		tempRecord->kind=' ';
	}
	if(strcmp(tempRecord->command,"?")==0) /* waiting for addresses calculation  */
	{
		relativePos=ConvertCharToInt(tempRecord->decimal_address);
		FIX_NULL_STRING(tmpItem);
		strcpy(tmpItem,tempRecord->operands);
		if(tmpItem[0]=='*')
			tmpLabelNode=FindLabel(_labels,tmpItem+1);
		else
			tmpLabelNode=FindLabel(_labels,tmpItem);

		if(tmpLabelNode==NULL)/* if label is not defined in input files, lets check if it's declared as external */
		{
		if(tmpItem[0]=='*')
			link=FindLinkage(&Linkage_List,tmpItem+1,EXTERN);
		else
			link=FindLinkage(&Linkage_List,tmpItem,EXTERN);
			if(link==NULL)
			{
				strcpy(errmsg,"the label '");
				if(tmpItem[0]=='*')
					strcat(errmsg,tmpItem+1);
				else
					strcat(errmsg,tmpItem);

				strcat(errmsg,"' has no reference");
				ErrorHandler(CompilingError,errmsg);
				return;
			}
			else
			{
				if(tmpItem[0]=='*')
				{
					strcpy(errmsg,"the label '");
					strcpy(errmsg,tmpItem+1);
					strcpy(errmsg," is external and cannot be used as rational");
					ErrorHandler(FatalError,errmsg);
					return;
				}
				else /* the label is external and is legal */
				{
					strcpy(tempRecord->command,"");
					strcpy(tempRecord->operands,"");
					FIX_NULL_STRING(binary);
					strcpy(binary,ConvertIntToCharByBase(0,ConversionToBmcType,2));
					tempRecord->bmc=CreateBmcCode(binary);
					tempRecord->kind='e';
					strcpy(tempRecord->base_12_machine_code,ConvertIntToCharByBase(0,ConversionToBase_12_Code,12));
					/* Add the EXTERN's address  */
					if(strcmp(link->lineNumber,"?")==0) /* first EXTERN use - remove and insert in order to sort it */ 
					{
						RemoveItemFromLinkageList(&Linkage_List,"?",tmpItem);
						AddLinkageItem(&Linkage_List,EXTERN,tmpItem,tempRecord->base_12_address);
					}
					else	/* the EXTERN has been used at least one time, we will add another field */
						AddLinkageItem(&Linkage_List,EXTERN,tmpItem,tempRecord->base_12_address);
				}

			}
		}
		else
		{
			if(tmpItem[0]=='*')
			{
				staticPos=ConvertCharToInt(tmpLabelNode->Value_10);
			/*	relativePos=staticPos-ConvertCharToInt(tempRecord->decimal_address);*/
				relativePos=staticPos-ConvertCharToInt(rememberMe); /* calculate the address using the one we remembered */
					strcpy(tempRecord->command,"");
					strcpy(tempRecord->operands,"");
					FIX_NULL_STRING(binary);
					strcpy(binary,ConvertIntToCharByBase(relativePos,ConversionToBmcType,2));
					tempRecord->bmc=CreateBmcCode(binary);
					tempRecord->kind='a';
					strcpy(tempRecord->base_12_machine_code,ConvertBinaryStringToBase12(binary));
					rememberMe=NULL;
			}
			else
			{
				strcpy(tempRecord->command,"");
				strcpy(tempRecord->operands,"");
				FIX_NULL_STRING(binary);
				strcpy(binary,ConvertIntToCharByBase(ConvertCharToInt(tmpLabelNode->Value_10),ConversionToBmcType,2));
				tempRecord->bmc=CreateBmcCode(binary);
				strcpy(tempRecord->base_12_machine_code,ConvertBinaryStringToBase12(binary));
				tempRecord->kind='r';
			}
		}

		if(tmpItem[0]=='*')
		{
		

		}
	
	}
	else /*check if command includes relational addressing, if it does, save it's address*/
	{
		strcpy(tmpItem,tempRecord->operands);
		for(i=0;i<strlen(tmpItem);i++)
		{
			if(tmpItem[i]=='*')
			{
				strcpy(rememberMe,tempRecord->decimal_address);
				break;
			}
		}
	}


	CmdQueue_AddRecord(tempRecord,layoutQueue);

}
