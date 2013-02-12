#include <utime.h>
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>

#define true 1
#define false 0
#define MAGIC_NUMBER "TAR"
#define BUF_SIZE 1024
#define EXTRACT_FAILD -1
#define HEADER_SIZE  7
#define PATHBKPERROR     "Could not backup whatever is found in this path\n"
#define BKPERROR    "An error occurred while trying to write to the backup file!\n"
#define RSTWRITEERROR    "An error occurred while trying to write to a restored file!\n"

#define USAGE         "usage: [<mkbkp <-c|-x> <backup_file> [<backuped_file | backuped_directory>]\n"
#define GENERALERROR  "Error please contact your dev!\n"

typedef int boolean;
typedef struct stat entryStats;
typedef struct sOffset
{
  size_t offset;
  struct sOffset* next;
} Offset;


FILE    *backupFile;                      
char    WD[FILENAME_MAX];             
char    *REALPATH;
size_t  currentOffset = 0; 
size_t  inFileLocationTableOffset = 0; 
uint    currentOffsetIndex = 0;        
Offset* pointerToOffserList = NULL;             
Offset* pointerToCurrentOffset = NULL;       
boolean       makeTarFile(char bkpFile[FILENAME_MAX]);
boolean       pathBackup(char path[FILENAME_MAX]);
boolean       backupFolderHirerchy(char dir[FILENAME_MAX]);
boolean       RestoreFrombackupAFile(char bkpFile[FILENAME_MAX]);
boolean       IsbackupAFileOpen();
boolean       createTarHeader(uint nEntries);
boolean       writeToTar(void* data,size_t length);
boolean       backupAFile(char FilePath[FILENAME_MAX],char SavedPath[FILENAME_MAX]);
boolean       backupAFolder(char FolderPath[FILENAME_MAX],char SavedPath[FILENAME_MAX]);
boolean       backupASymbolicLink(char FilePath[FILENAME_MAX],char SavedPath[FILENAME_MAX]);
boolean       traverseFolder(char root[FILENAME_MAX],uint prefixLength,mode_t mode);
size_t     getStatsForEntry(size_t offset,entryStats *StatBuf,char *path);
size_t getOffsetTabLoc();
size_t     extractEntry(size_t entryOffset);
void   svOffsetsTable();
size_t     extractFile(size_t offset,entryStats StatBuf,char FileDirPath[FILENAME_MAX],char FileName[256]);
boolean       extractAfolder(entryStats StatBuf,char DirPath[FILENAME_MAX]);
boolean       extractASymbolicLink(size_t offset,entryStats StatBuf,char FilePath[FILENAME_MAX]);
void   raiseOffsetIndex(size_t n);
boolean       setFileStats(char FilePath[FILENAME_MAX],entryStats StatBuf);
int        mkpath(const char *path, mode_t mode);
static int do_mkdir(const char *path, mode_t mode);


void   svOffset(size_t offset);
size_t getNextEntryDist();
