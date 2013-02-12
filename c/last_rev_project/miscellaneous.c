#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "miscellaneous.h"

static enum Boolean  _CompilingError = FALSE;
/* a function that converts an int to any given radix and returns its string representation*/
char* ConvertIntToCharByBase(int num,enum TypeOfConversion convType,int baseToConvertTo)
{
	enum Boolean two_complement=FALSE;
	char* returnVal=NULL;
	int tempNum=num,i,j,max_digits;
	/*ALLOCATE_STRING(returnVal,1);*/
	returnVal=(char*)malloc(sizeof(char));
/*	FIX_NULL_STRING(returnVal);*/
	/*returnVal[0]='\0';*/
	if(num<0)
	{
		if(convType==ConversionToBase_12_Code && baseToConvertTo!=2 )
		{
			returnVal=ConvertIntToCharByBase(num,convType,2);
			returnVal=ConvertBinaryStringToBase12(returnVal);
			return returnVal;
		}
		num=0-num;
		two_complement=TRUE;
	}
	for(i=1;num>0;i++)
	{
		tempNum=num%baseToConvertTo;
		/*ALLOCATE_STRING(returnVal,(i+1))*/
		returnVal=(char*)realloc(returnVal,(i+1)*sizeof(char));
			for(j=i;j>0;j--)
				returnVal[j]=returnVal[j-1];
		if(tempNum==10)
			*returnVal='A';
		else if(tempNum==11)
			*returnVal='B';
		else
			*returnVal='0'+tempNum;
		num=num/baseToConvertTo;
		if(num>0)
		{

		}
	}
	if(convType==ConversionToSimple)
		max_digits=strlen(returnVal);
	else if(convType==ConversionToAddress)
		max_digits=MAX_ADDRESS_DIGITS;
	else if(convType==ConversionToBmcType)
		max_digits=BMC_LENGTH;
	else if(convType==ConversionToBase_12_Code)
		max_digits=BASE_12_MACHINE_CODE_DIGITS;
	else if(convType==ConversionToBmcOpCode)
		max_digits=BMC_OPCODE_LENGTH;
		else if(convType==ConversionToBmcOpRegField)
		max_digits=BMC_REG_LENGTH;
	
		tempNum=i;/* last digit position*/
		while(i <= max_digits) /*plus 1 for null char*/
		{
			returnVal=(char*)realloc(returnVal,(i+1)*sizeof(char));
			for(j=i;j>=i+1-tempNum;j--)
			{
				returnVal[j]=returnVal[j-1];
			}
			for(;j>=0;j--)
				returnVal[j]='0';
		i++;		
		}
		ALLOCATE_STRING(returnVal,strlen(returnVal)+1);
		returnVal[strlen(returnVal)]='\0';

		if(two_complement==TRUE)
		{
			for(i=0;i<strlen(returnVal);i++)/* convert 0's to 1's and 1's to 0's */
				if(returnVal[i]=='0')
					returnVal[i]='1';
				else
					returnVal[i]='0';
			if(returnVal[strlen(returnVal)-1]=='0')
				returnVal[strlen(returnVal)-1]='1';/* add 1 to the LSB when it's 0 */
			else
				{
					for(i=strlen(returnVal)-1;i>=0 && returnVal[i]=='1';i--)
						returnVal[i]='0';/* convert 1's to 0's - like adding 1 does */ 
					if(i>0)
						returnVal[i]='1';/* carrying the 1's has over, no more carries */
				}
			
		}
	return returnVal;
}
/* a function that validates label legality existance*/
char* ValidateLabel(char* label)
{
	int length,i=0;
	char* newLabel=NULL;
	length=strlen(label);
	if(length>2)
		if(label[length-1] == ':')
			if((label[0]>='a' && label[0]<='z') || (label[0]>='A' && label[0]<='Z'))
			{
				newLabel=(char*)malloc((length)* sizeof(char));
				if(newLabel==NULL)
					ErrorHandler(OutOfMemory,"while adding label");
				while(i<length-1)
				{
				if((label[i]>='a' && label[i]<='z') || (label[i]>='A' && label[i]<='Z') || (label[i]>='0' && label[i]<='9'))
					newLabel[i]=label[i];
				else
					return NULL;

				i++;
				}
				newLabel[length-1]='\0';
				return newLabel;
			}
			return NULL;

}
/*a function that recognises the error type and sets the error message accordingly*/
void ErrorHandler(enum RuntimeErrors error,char *moreInfo)
{
	char *message=NULL;
	int errorNumber=0;
	enum Boolean showMessage=FALSE,exitProgram=FALSE;
	
	ALLOCATE_STRING(message,100);
		
	switch(error)
	{
	case OutOfMemory:
		showMessage=TRUE;
		exitProgram=TRUE;
		errorNumber=1;
		strcpy(message,"\nOut Of Memory.\n");
		break;
	case StackEmpty:
		showMessage=TRUE;
		exitProgram=FALSE;
		errorNumber=2;
		message[0]='a';
		strcpy(message,"\rStack Empty.\n");
		break;
	case UnableToOpenFile:
		showMessage=TRUE;
		exitProgram=TRUE;
		errorNumber=3;
		strcpy(message,"\nUnable to open file.\n");
		break;
	case NCA:
		showMessage=TRUE;
		exitProgram=TRUE;
		errorNumber=4;
		strcpy(message,"\nNo command-line arguments entered!\n");
		break;
	case CompilingError:
		showMessage=TRUE;
		exitProgram=FALSE;
		errorNumber=5;
		strcpy(message,"\nCompilation error! \n");
		break;
	case FatalError:
		showMessage=TRUE;
		exitProgram=TRUE;
		errorNumber=6;
		strcpy(message,"\nFatalError\n");
		break;
	default:
	/* 
		impossible situation because using enum and code direction only.
		cosmetic only.
	*/
		errorNumber=6;
		break;
	}
	if(showMessage==TRUE)
	{
		if(strlen(moreInfo)>1)
		{
			strcat(message,"\n *additional info: ");
			strcat(message,moreInfo);

		}
		strcat(message,"\n");

		printf("%s",message);
	}
	if(exitProgram==TRUE)
	{
		 printf("\nExiting...\n");
		 exit(errorNumber);
	}
	SetCompilingError();
}
/* this function gets the arguments of the commandline from main
then checks if any exist, if not it returns and error if yes
it returns a files dynamic array*/
char **ObtainFileNames(int numOfFiles,char *filesV[])
{
	char **files;
	int i;
	if(numOfFiles<1)
		ErrorHandler(NCA,"");
	
	files=(char**)malloc(numOfFiles*sizeof(char*));
	for(i=0;i<numOfFiles;i++)
	{
		files[i]=(char*)malloc(strlen(filesV[i+1]));
		strcpy(files[i],filesV[i+1]);
	}
	return files;
}
/*this function takes a string trims out all the ignored stuff and returns it*/
char* StringTrim(char *stringToTrim)
{
	int stringLength,curPos=0;
	char *tempString,curItem,lastItem='?';
	enum Boolean firstPart=TRUE,inQuotes=FALSE,addChar=TRUE;
	stringLength=strlen(stringToTrim);
	tempString=NULL;
	while(curPos<stringLength)
	{
		if(stringToTrim[curPos]==' ' ||stringToTrim[curPos]=='\t')
			curPos++;
		else
			break;
	}
	if(stringLength<2 || curPos>=stringLength)
	{
		tempString=(char*)malloc((stringLength+1)*sizeof(char));
		if(stringLength==0  || curPos>=stringLength)
			{
				tempString[0]='\0';
				return tempString;
			}
		else if(stringLength==1)
		{
				tempString[0]=stringToTrim[0];
				tempString[1]='\0';
				return tempString;	
		}
	}
	while(curPos<stringLength)
	{
		
		if(firstPart==TRUE)/*remove leading spaces */
			{
				for(;curPos<stringLength;curPos++)
				{
					curItem=stringToTrim[curPos];
					/*if(curPos>=stringLength)break;
					if(curItem>='a' && curItem<='z')break;
					if(curItem>='A' && curItem<='Z')break;
					if(curItem>='0' && curItem<='9')break;
					if(curItem=='.')break;
					*/
					if(curItem!=' ')break;
				}
				firstPart=FALSE;
			}
		if(strlen(stringToTrim)<2)
			break;
		curItem=stringToTrim[curPos];
		if(curItem=='\t')
		{
			curItem=' ';
		}
		if(stringToTrim[curPos]=='\"')
			{
				if(inQuotes==FALSE)
					inQuotes=TRUE;
				else
					inQuotes=FALSE;

			}

		else if(curItem==NULL || curItem==' ')
		{
			if(inQuotes==FALSE)
					if(lastItem==' ')
						addChar=FALSE;
		}



		lastItem=curItem;
		curPos++;
		if(addChar==TRUE)
			tempString=AddCharToString(tempString,curItem);
		else
			addChar=TRUE;
		if(curPos>=stringLength)
		{
			if(lastItem==' ')
				if(tempString==NULL)
				{
					ALLOCATE_STRING(tempString,1);
					tempString[stringLength-1]='\0';
				}

			return tempString;
		}
		}
	return NULL;
}
/*adds a wanted character to the end of a string and teturns the result
string - the string
item - the char
return value - a pointer to the new string in the heap */
char *AddCharToString(char *string,char item)
{
	char *tmpstr;
	int length;
	if(string==NULL)
		{
			length=2;
			tmpstr=(char*)malloc(length*sizeof(char));
			tmpstr[0]=item;
		}
	else
	{
		length=strlen(string)+2;
		tmpstr=(char*)malloc(length*sizeof(char));
		strcpy(tmpstr,string);
		tmpstr[length-2]=item;
	}
	tmpstr[length-1]='\0';
		return tmpstr;
}

char *StringMoveToNextItem(char* text)
{
	char* temp=NULL;
	int i=0,sizeOfNewString=0;
	text=StringTrim(text);
	for(;text[i]!=' ' && text[i]!=':';i++);
		i++;
	while(text[i]!='\0')
	{
		temp=(char*)realloc(temp,(++sizeOfNewString)*sizeof(char));
		temp[sizeOfNewString-1]=text[i];
		i++;
	}
		temp=(char*)realloc(temp,(++sizeOfNewString)*sizeof(char));
		temp[sizeOfNewString-1]='\0';
		return temp;
}
/*as this function name emplyst the function converts a given number in 
character form and returns it as an integer*/
int ConvertCharToInt(char *inputNumber)
{
	int number=0,stringLength,index=0;

	stringLength=strlen(inputNumber);
	if(stringLength==0)
		return 0;
	for(index+=((inputNumber[0]=='-' || inputNumber[0]=='+')?1:0);index<stringLength;index++)
	{
		number+=(inputNumber[index]-'0');
		if(index+1<stringLength)
			number*=10;
	}
	return inputNumber[0]=='-'?0-number:number;
}
int OctalToDecimal(int octal)
{
    int temp,translated=0,i;
    for(i=0;octal>0;i++)
    {
        temp=octal%10;
        translated=translated+temp*(int)(pow(8,i));
        octal=octal/10;
    }
	return translated;
}
/* this function takes a binary in string form and converts it into base 12*/
char *ConvertBinaryStringToBase12(char *bmcString)
{
	long i,j,t=0,s=0;
	char *tempNum=NULL;
	for(i=0,j=0;i<BMC_LENGTH;i++)
	{

		t=pow(2,i);
		s=(bmcString[BMC_LENGTH-i-1]-'0');
		j+=(s*t);
	}
	tempNum=ConvertIntToCharByBase(j,ConversionToBase_12_Code,12);
	return tempNum;
}
/*this function finds a parameters type*/
enum ParamType FindParamType(char *param)
{
	int i=0,length,blocksCount=0;
	enum Boolean inBlock=FALSE,asterixFound=FALSE;
	length=strlen(param);

	if(length==0)
		return Param_error;

	if(param[0]=='#')/* number */
	{
		i++;
		if(!isdigit(param[i]) && param[i]!='-' && param[i]!='+')
			return Param_error; /* illegal value, after # should be only number,minus or plus sign and number. */
		if(param[i]=='-' || param[i]=='+')
			i++; /* legal number negetive or positive */

		for(;i<length;i++)
		{
		if(isdigit(param[i])) 
			continue; /* verify the value is legal till it's end. */
		else
			return Param_error;
		}
		return Param_Number;
	}

	if(param[0]=='r') /* check if is a register */
	{
		if(length==2 && param[1]-'0'>= 0 && param[1]-'0' < 8)
			return Param_register; /* rX type (0<=X<=7) == register -> register direct addressing*/
	}

	if(!isalpha(param[0])) 
		return Param_error; /* illegal operand (other than letter) */

			while(i<length && (isalpha(param[i]) || isdigit(param[i]))) i++;/* while a cahr or digit */
			if(i==length) /* (letters to the end: ABCD-> label or a variable -> direct addressing*/
				return Param_word;

			for(;i<length;i++)
			{
				if(blocksCount>=2)
					return Param_error;

				if(isdigit(param[i]) || isalpha(param[i]))
				{
					if(param[i]=='r')
						if(param[i-1]=='[')
							if((i+1)<length && param[i+1]-'0'>= 0 && param[i+1]-'0' < 8)
								if((i+2)==length-1 && param[i+2]==']' && inBlock==TRUE && blocksCount>1)
									return Param_register;
					continue;
				}

				else 
				{
					if(param[i]=='[')
					{
						if(blocksCount==2)
							return Param_error; /* too many relative addresses */
						if(asterixFound==TRUE)
							return Param_error;/* illegal value: " [*][...] " */

						if(inBlock==FALSE)
						{
							inBlock=TRUE;
							continue;
						}
						else
						{
							return Param_error; /* illegal value: " [[ " */
						}
					}
					else if(param[i]==']')
					{
						if(inBlock==FALSE)
							return Param_error; /* illegal value: closing block without opening it  */
						else
						{
							inBlock=FALSE;
							blocksCount++;
							continue;
						}
					}
					else if(param[i]=='*')
						{
							if(inBlock==FALSE)
								return Param_error;/* illegal value: relative address outside a block  */
							else
							{
								if(asterixFound==TRUE)
									return Param_error;/* illegal value: two relative addresses in one block or asterix already been used in other one.  */
								else
								{
									if(blocksCount>=1)
										return Param_error; /* probably the asterix is in the second block */
									else 
										asterixFound=TRUE;
								}
							}
						}

				}

			}
			if(asterixFound==TRUE)
				return Param_relative;
			if(blocksCount==2)
				return Param_dimentional;
			return Param_error;
}
/* this function identifies the addressing methond to be used*/
int IdentifyAddressing(char* param)
{
	enum ParamType pType;
	pType=FindParamType(param);

	switch(pType)
	{
	case Param_Number:
		return 0;
		break;
	case Param_word:
		return 1;
		break;
	case Param_relative:
		return 2;
		break;
	case Param_dimentional:
		return 3;
		break;
	case Param_register:
		return 4;
		break;
	default:
		if(strlen(param)==0)
			return -1;
		else
		{
			ErrorHandler(CompilingError,"operand is illegal");
			return -2; /* error */
		}
		break;
	}
	if(strlen(param)==0)
		return -1;
}
/* this function does a comparison between a list of allowed addressing methods
and the one used */
enum Boolean IsAddressingAllowedForCommand(int addressing,int allowedAddressing[])
{
	int i;
	for(i=0;i<sizeof(allowedAddressing)+1;i++)
		if(allowedAddressing[i]==addressing)
			return TRUE;
	return FALSE;
}
enum Boolean IsMachineRegister(char* str)
{
	if(str==NULL)
		return FALSE;
	if(strlen(str)==2 && (str[0]=='r' && str[1]>='0' && str[1]<='9'))
		return TRUE;
	else
		return FALSE;

}
/* function returns compiler error status , true - exists, false - doesnt*/
enum Boolean WasThereCompilingError()
{
	return _CompilingError;
}
/*checks if a given number in string form is a legal num*/
enum Boolean IsLegalNumber(char *strToCheck)
{
	int i=0;
	for(i+=(strToCheck[0]=='-'?1:strToCheck[0]=='+'?1:0) ; i<(strlen(strToCheck)) ; i++)/* check if is legal number, jumps over # and minus or plus signs if any */
		if(!isdigit(strToCheck[i]))
			return FALSE;
	return TRUE;
}
/*helper function - sets compiler error boolean to true*/
void SetCompilingError()
{
	_CompilingError=TRUE;
}
