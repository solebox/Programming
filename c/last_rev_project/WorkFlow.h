#include "AsmCommandQueue.h"
#include "Files.h"
#include "Enums.h"
#include "Lables_LinkedList.h"
#include "ComputerCommandsQueue.h"
#include "InitializationFunctions.h"
#include "Linkage_Symbols.h"
#include "Global_Defines.h"

void FirstPass(char **files,int fileCount);
void SecondPass(char* fileName);
void FirstPassInitialization();
void ReadFiles(int filesCount);
void ReadFile(int index);
enum Boolean AnalyzeText(char *tempInputCommand);
enum Boolean IsLabel(char *string);
char *ReadWord(char *text,int *curLoc,char specificDelimiter);
enum Directive WhatDirective(char *text);
void HandleCommand(char *line,int* curPos,opcode opcode,char* label);
char *HandleLabel(char* label,char *line,int* loc);
char *AnalyzeCommand(char* temp);
char* ReadAdditionalValues(char* line);
void HandleDirective(char* tempInputCommand,char* label,char* Directive);
void CreateBmc(char* inputCommand,char* directive,enum ItemType type,char *label,char* command,char* operands);
enum Boolean IsDelimiter(char test,char specificDelimiter);
void CreateBmcForCommand(char* line,char* label,opcode thisOpcode,char* param1,char* param2,int addressingType1, int addressingType2);
void AddItemToLayout(Cmd tempRecord,CmdQueue layoutQueue);

