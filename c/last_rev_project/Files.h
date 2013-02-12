#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "ComputerCommandsQueue.h"
#include "Enums.h"
#include "Linkage_Symbols.h"

FILE *openFile(char *filename,char* mode);
void WriteObjFile(char *filename,CmdQueue Q,int ic,int dc);
FILE **CreateInputFileArray(char **files,int filesCount);
char *ReadLineFromFile(FILE *fp,long filesSize);
long GetFileSize(FILE *fp);
void WriteExtAndEntFiles(char* fileName,LinkedList_Linkage *linkage);
char* CreateFileName(char *filename,enum FileExtension extension);

