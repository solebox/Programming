#include "Enums.h"
#include "Global_Defines.h"

#ifndef _GLOBAL_DEFINES_H
#define _GLOBAL_DEFINES_H
/* global identifier decleration to handle error while compiling */
/* end of decleration */
char* ConvertIntToCharByBase(int num,enum TypeOfConversion convType,int base_Dest);
char* ValidateLabel(char* label);
void ErrorHandler(enum RuntimeErrors error,char *moreInfo);
char **ObtainFileNames(int argc,char *argv[]);
char* StringTrim(char *stringToTrim);
char *AddCharToString(char *string,char item);
char *ConvertIntToCharOld(int num,enum TypeOfConversion,int baseToConvertTo);
char *StringMoveToNextItem(char* text);
int ConvertCharToInt(char *number);
char *Create_Base_12_Machine_Code(char binary);
int OctalToDecimal(int octal);
char *ConvertBinaryStringToBase12(char *bmcString); 
int IdentifyAddressing(char* param);
enum ParamType FindParamType(char *param);
enum Boolean IsAddressingAllowedForCommand(int addressing,int allowedAddressing[]);
enum Boolean IsMachineRegister(char* str);
enum Boolean WasThereCompilingError();
enum Boolean IsLegalNumber(char *strToCheck);
void SetCompilingError();

#endif