/* 
 * File:   mkbkp.c
 * Author:solekiller 
 *
 */
#include "mkbkp.h"
#include "unistd.h"


void svOffsetsTable(){
    size_t tOffset;
    Offset* p;
    int    i;
    
    fwrite(&currentOffsetIndex,1,sizeof(size_t),backupFile);
    p = pointerToOffserList;
    for(i=0;i<currentOffsetIndex;i++){
        tOffset = p->offset;
        if(tOffset != 0xffffffff){
            fwrite(&tOffset,1,sizeof(size_t),backupFile);
            p = p->next;
        }else{
            perror(GENERALERROR);
        }
    }
    fwrite(&currentOffset,1,sizeof(size_t),backupFile);
}
void svOffset(size_t offset){
    if(pointerToOffserList == NULL){
         pointerToOffserList = (Offset*)malloc(sizeof(Offset));
         if(pointerToOffserList != NULL){
             pointerToCurrentOffset = pointerToOffserList;
         }else{
             perror(GENERALERROR);
             exit(1);
         }
    }
    pointerToCurrentOffset->offset = offset;
    pointerToCurrentOffset->next = (Offset*)malloc(sizeof(Offset));
    if(pointerToCurrentOffset->next != NULL){
        pointerToCurrentOffset = pointerToCurrentOffset->next;
        pointerToCurrentOffset->offset = 0xffffffff;
        currentOffsetIndex++;
    }else{
        perror(GENERALERROR);
        exit(1);
    }
}


size_t getNextEntryDist(){
    size_t nOffsets;
    size_t offset;
    
    fseek(backupFile,inFileLocationTableOffset,SEEK_SET);
    fread(&nOffsets,1,sizeof(size_t),backupFile);
    
    if(currentOffsetIndex < nOffsets){
        fseek(backupFile,currentOffsetIndex*sizeof(size_t),SEEK_CUR);
        fread(&offset,1,sizeof(size_t),backupFile);
        currentOffsetIndex++;
        return offset;
    }
    return (size_t)NULL;
}

boolean writeToTar(void* data,size_t len){
    int n = -1;
    n = fwrite((void**)data,1,len,backupFile);
    if(n != len){
        perror(BKPERROR);
        return false;
    }else{
        currentOffset += n;
        return true;
    }
}


int main(int argc, char** argv){
    int opt;
    getcwd((char * __restrict__)&WD,FILENAME_MAX);
    if((opt = getopt(argc, argv, "cx:")) != -1){
        switch(opt){
            case 'c':
                if(argc != 4){
                    printf(USAGE);
                    exit(EXIT_FAILURE);
                }else{
                   REALPATH = realpath(argv[3],REALPATH);    
                }
                printf("\nbackuping: \"%s\"",REALPATH);
                if(!makeTarFile(argv[2])){
                    perror("Could not create the backup file!");
                    exit(EXIT_FAILURE);
                }

                if(!pathBackup(REALPATH)){
                     exit(EXIT_FAILURE);
                }
                break;
            
            case 'x':
                if(!RestoreFrombackupAFile(argv[2])){
                    perror("Can't restore from backup file");
                     exit(EXIT_FAILURE);
                }
                break;
            default:
                printf(USAGE);
                exit(EXIT_SUCCESS);
                break;
        }
         printf("\nFinish!\n");
         exit(EXIT_SUCCESS);
    }
    printf(USAGE);
    exit(EXIT_SUCCESS);
}
size_t getOffsetTabLoc(){
    size_t pos;
    
    fseek(backupFile,(-1)*sizeof(size_t),SEEK_END);
    fread(&pos,1,sizeof(size_t),backupFile);
    return pos;
}

boolean makeTarFile(char bkpFile[FILENAME_MAX]){
    backupFile = fopen(bkpFile, "wb");
    
    if(NULL == backupFile){
        return false;
    }
    
    if(!createTarHeader(-1)){
        return false;
    }
    
    return true;
}


boolean pathBackup(char path[FILENAME_MAX]){
    struct stat	buf;
    char        *p;
    
    
    if(-1 == lstat(path,&buf)){
        return false;
    }
    
    if(S_ISDIR(buf.st_mode)){
        if(!backupFolderHirerchy(path)){
            return false;
        }
    }
    else if(S_ISREG(buf.st_mode)){
        p = strrchr(path,'/');
        if(p != NULL && !backupAFile(path,p)){
            return false;
        }
    }
    else{
        printf(PATHBKPERROR);
    }
        
    
    svOffsetsTable();
    if(fclose(backupFile) == EOF){
        return false;
    }
    return true;
}

boolean backupFolderHirerchy(char dir[FILENAME_MAX]){
    char *p;
    char tdir[FILENAME_MAX];
    
    strncpy(tdir,dir,FILENAME_MAX);
    
    p = strrchr(tdir,'/');
    
    while((p != NULL) && 
            ((int)(p-tdir) == (strlen(tdir) - 1))){
        *p = '\0'; 
        p = strrchr(tdir,'/');
    }
    p = strrchr(tdir,'/');
    if(p != NULL){
        p++;
        
        if(!traverseFolder(tdir,(int)(p-tdir),S_IFDIR)){
            return false;
        }
        if(!traverseFolder(tdir,(int)(p-tdir),S_IFREG)){
            return false;
        }
        if(!traverseFolder(tdir,(int)(p-tdir),S_IFLNK)){
            return false;
        }
    }
    
    return true;
}
boolean createTarHeader(uint nEntries){
    size_t n;
    n = fprintf(backupFile,"%s",MAGIC_NUMBER);
    if(n <= 0){
        return false;
    }else{
        currentOffset += n;
        return true;
    }
}


boolean traverseFolder(char root[FILENAME_MAX],uint prefixLength,mode_t mode){
    DIR           *d;
    struct dirent *dir;
    struct stat	  buf;
    char          tPath[FILENAME_MAX];
    char          *pName;
    
    if(-1 == lstat(root,&buf)){
        return false;
    }

    if((mode == S_IFDIR) && ((buf.st_mode & S_IFMT) == S_IFDIR)){
        pName = (root+prefixLength);
        if(!backupAFolder(root,pName)){
            return false;
        }
    }
        

    d = opendir(root);
    if(d == NULL){
        return false;
    }
    while ((dir = readdir(d)) != NULL){
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0){
            continue;
        }
        else
        {
            strncpy(tPath,root,FILENAME_MAX);
            strcat(tPath, "/");
            strcat(tPath, dir->d_name);
            if(-1 == lstat(tPath,&buf)){
                return false;
            }
            
            if(S_ISDIR(buf.st_mode)){
                 if(!traverseFolder(tPath,prefixLength,mode)){
                     return false;
                 }
            }
            else if((mode == S_IFREG) && ((buf.st_mode & S_IFMT) == S_IFREG)){
                pName = (tPath+prefixLength);
                if(!backupAFile(tPath,pName)){
                    return false;
                }
            }
            else if((mode == S_IFLNK) && ((buf.st_mode & S_IFMT) == S_IFLNK)){
                pName = (tPath+prefixLength);
                backupASymbolicLink(tPath,pName);
            }
        }
    }
    return true;
}


boolean backupAFolder(char FolderPath[FILENAME_MAX],char SavedPath[FILENAME_MAX]){
    entryStats stats;
    size_t    pathlen;
    
    svOffset(currentOffset);
    
    if(-1 == lstat(FolderPath,&stats) || !writeToTar(&stats,sizeof(struct stat))){
        return false;
    }
    
    
    
    pathlen = strlen(SavedPath);
    if(!writeToTar(&pathlen,sizeof(int))){
        perror(BKPERROR);
        return false;
    }
    
    if(!writeToTar(SavedPath,strlen(SavedPath))){
        return false;
    }
    return true; 
}

boolean backupAFile(char FilePath[FILENAME_MAX],char SavedPath[FILENAME_MAX]){
    char        buf[BUF_SIZE];
    size_t      BytesRead,BytesWritten;
    size_t      pathlen;
    entryStats	StatBuf;
    int         fd;
    
    svOffset(currentOffset);
    
    if(-1 == lstat(FilePath,&StatBuf)){
        return false;
    }
    
    if(!writeToTar(&StatBuf,sizeof(struct stat))){
        perror(BKPERROR);
        return false;
    }
    
    pathlen = strlen(SavedPath);
    if(!writeToTar(&pathlen,sizeof(int))){
        perror(BKPERROR);
        return false;
    }
    
    if(!writeToTar(SavedPath,strlen(SavedPath))){
        perror(BKPERROR);
        return false;
    }
    
    fd = open(FilePath, O_RDONLY); 
    if (-1 == fd){
        perror("Could not open the requested file!");
        return false;
    }
    while ((BytesRead = read(fd, buf, BUF_SIZE)) > 0){
        BytesWritten = fwrite(&buf,BytesRead,sizeof(char),backupFile);
        currentOffset += BytesRead;
        if(BytesWritten < 0){
            perror("An error occurred while trying to backup a file!\n \
                data couldn't be written!");
            close(fd);  
            return false;
        }
    }
    if(-1 == close(fd)){
        perror("Could not close the backed up file!");
        return false;
    }
        
    return true;
}

boolean backupASymbolicLink(char FilePath[FILENAME_MAX],char SavedPath[FILENAME_MAX]){
    char        lnkTo[FILENAME_MAX];
    entryStats	StatBuf;
    size_t      pathlen;
    
    memset(lnkTo, '\0', FILENAME_MAX);
    
    svOffset(currentOffset);
    
    if(-1 != lstat(FilePath,&StatBuf)){  
        if(writeToTar(&StatBuf,sizeof(struct stat))){
            pathlen = strlen(SavedPath);
            if(writeToTar(&pathlen,sizeof(int))){ 
                if(writeToTar(SavedPath,pathlen)){
                    if(-1 != readlink((const char *)FilePath,(char *)&lnkTo,FILENAME_MAX)){
                        pathlen = strlen(lnkTo);
                        if(writeToTar(&pathlen,sizeof(int))){                      
                            if(writeToTar(&lnkTo,pathlen)){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}



boolean RestoreFrombackupAFile(char bkpFile[FILENAME_MAX]){
    size_t e;
    
    backupFile = fopen(bkpFile, "r");
    if(backupFile == NULL){
        perror("Could not open the backup file");
        return false;
    }
    
    currentOffsetIndex= 0; 
    inFileLocationTableOffset = getOffsetTabLoc();
    
    e = getNextEntryDist();
    while(e != (size_t)NULL){
        if(!extractEntry(e)){
            perror("An error occurred while trying to extract an entry");
            return false;
        }
        e = getNextEntryDist();
    }
    
    return true;
}

size_t extractEntry(size_t offset){
    entryStats  StatBuf;
    char       FileDirPath[FILENAME_MAX];
    char       FileCreationPath[FILENAME_MAX];
    char       tPath[FILENAME_MAX];
    char       *sp;
    char       *fileName;
    int        status;
    
    if(offset == 0xffffffff){
        return EXTRACT_FAILD;
    }
    
    memset(tPath, '\0', FILENAME_MAX);
    memset(FileCreationPath, '\0', FILENAME_MAX);
    memset(FileDirPath, '\0', FILENAME_MAX);
       
    offset = getStatsForEntry(offset,&StatBuf,FileDirPath);
    if(offset == EXTRACT_FAILD){
       return EXTRACT_FAILD; 
    }
    
    strncpy(tPath,WD,strlen(WD));
    strcat(tPath, "/");
    strcat(tPath, FileDirPath);   
    strncpy(FileCreationPath,tPath,strlen(tPath));
    
    if(S_ISDIR(StatBuf.st_mode)){
        status = extractAfolder(StatBuf,tPath);
        if(status == EXTRACT_FAILD){
            perror("Something went wrong while extracting a folder");
            return EXTRACT_FAILD;
        }
    }
    else if(S_ISREG(StatBuf.st_mode)){
        sp = strrchr(tPath,'/');
        fileName = strdup(sp+1);
        *sp = '\0'; 
        
        status = extractFile(offset,StatBuf,tPath,fileName);
        if(status == EXTRACT_FAILD){
            perror("Something went wrong while extracting a file");
            return EXTRACT_FAILD;
        }
        offset = status;
    }
    else if(S_ISLNK(StatBuf.st_mode)){       
        if(!extractASymbolicLink(offset,StatBuf,FileCreationPath)){
            return EXTRACT_FAILD;
        }
        
    }
    return offset;
}

size_t getStatsForEntry(size_t offset,entryStats *StatBuf,char *path){
    size_t pathlen;
    size_t n = 0;
    char   tpath[FILENAME_MAX];
    
    memset(tpath, '\0', FILENAME_MAX);
    if(fseek(backupFile,offset,SEEK_SET) == -1){
        printf("An error occurred while trying to read from the backup file");
        return EXTRACT_FAILD;
    }
    n += fread(StatBuf,1,sizeof(entryStats),backupFile); 
    n += fread(&pathlen,1,sizeof(size_t),backupFile);    
    
    if(pathlen >0 && pathlen < FILENAME_MAX){
        fread(&tpath,pathlen,sizeof(char),backupFile);
        strncpy(path,tpath,strlen(tpath));
        n += pathlen;
    }
    else{
        perror("Illegal path name or path name length was detected! backup file might be corrupted!");
        return EXTRACT_FAILD;
    }
    
    return (size_t)offset+n;
}

size_t extractFile(size_t offset,entryStats StatBuf,char FileDirPath[FILENAME_MAX],char FileName[256]){
    entryStats   tStatBuff;
    FILE*       filep;
    char        FileCreationPath[FILENAME_MAX+256];
    char        buf[BUF_SIZE];
    size_t      FileSize;
    size_t      bytesWritten;
    size_t      bytesRead;
    size_t      bytesTail;
    size_t      n;
    
    
    if(!S_ISREG(StatBuf.st_mode)){
        return EXTRACT_FAILD;
    }
    
    
    memset(FileCreationPath, '\0', FILENAME_MAX+256);
    memset(buf, '\0', BUF_SIZE);
    
    if (stat(FileDirPath, &tStatBuff) != 0){
        if(!mkpath(FileDirPath,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
            perror("Error while trying to create a dir path to a file :-(");
            return EXTRACT_FAILD;
        }
    }
    
    strncpy(FileCreationPath,FileDirPath,strlen(FileDirPath));
    strcat(FileCreationPath,"/");
    if(strlen(FileDirPath) +  strlen(FileName) <= FILENAME_MAX){
    	strcat(FileCreationPath,FileName);
    }
    else{
	return EXTRACT_FAILD;
    }
    
    filep = fopen(FileCreationPath,"w");
    if(filep == NULL){
        perror("Error while trying to restore a file!");
        return EXTRACT_FAILD; 
    }
    
    bytesRead    = 0;
    FileSize     = StatBuf.st_size;    
    bytesTail    = FileSize % BUF_SIZE; 
    bytesWritten = 0;                   

    fseek(backupFile,offset,SEEK_SET);
    if(FileSize > BUF_SIZE){
        while(bytesWritten < FileSize - bytesTail){
            n = fread(&buf,sizeof(char),BUF_SIZE,backupFile);
            bytesRead += n;
            if(n == BUF_SIZE){
                n = fwrite(&buf,sizeof(char),BUF_SIZE,filep);
                bytesWritten += n;
                if(n < BUF_SIZE){
                    perror(RSTWRITEERROR);
                    fclose(filep);
                    return EXTRACT_FAILD;
                }
            }
            else
            {
                perror("An error occurred while trying to read from the backup file");
                fclose(filep);
                return EXTRACT_FAILD;
            }
        }
    }
    if(bytesTail > 0){
        n = fread(&buf,sizeof(char),bytesTail,backupFile);
        bytesRead += n;
        if(n == bytesTail){
            n = fwrite(&buf,sizeof(char),bytesTail,filep);
            bytesWritten += n;
            if(n < bytesTail){
                perror(RSTWRITEERROR); 
                fclose(filep);
                return EXTRACT_FAILD;
            }
        }
        else
        {
            perror("An error occurred while trying to read from the backup file");
            fclose(filep);
            return EXTRACT_FAILD;
        }
    }
    fclose(filep);
    chmod(FileCreationPath,StatBuf.st_mode);
    setFileStats(FileCreationPath,StatBuf);
    return (size_t)(offset + bytesRead); 
}

boolean extractAfolder(entryStats StatBuf,char DirPath[FILENAME_MAX]){
    return mkpath(DirPath,StatBuf.st_mode);
    setFileStats(DirPath,StatBuf);
}

boolean extractASymbolicLink(size_t offset,entryStats StatBuf,char FilePath[FILENAME_MAX]){
    char      lnkto[FILENAME_MAX];
    size_t    len;
    size_t    n;
    
    memset(lnkto, '\0', FILENAME_MAX);
    n = fread(&len,1,sizeof(int),backupFile);
    if(n == sizeof(int)){
        n = fread(&lnkto,sizeof(char),len,backupFile);
        if(n == sizeof(char)*len){
            if(-1 != symlink(lnkto,FilePath)){
                return true;
            }
        }
    }
    return false;
}

boolean setFileStats(char FilePath[FILENAME_MAX],entryStats StatBuf){
    struct utimbuf t;
    t.actime = StatBuf.st_atime;
    t.modtime = StatBuf.st_mtime;
    
    if(utime(FilePath,&t) == -1){
        perror("Could not change creation time");
        return false;
    }
    return true;    
}

static int do_mkdir(const char *path, mode_t mode){
    struct stat st;
    int         status = true;

    if (stat(path, &st) != 0){
        if (mkdir(path, mode) != 0)
            status = false;
    }
    else if (!S_ISDIR(st.st_mode)){
        status = false;
    }

    return(status);
}

int mkpath(const char *path, mode_t mode){
    char *pp;
    int  status;
    char *sp;
    char cpath[FILENAME_MAX];
    
    memset(cpath, '\0', FILENAME_MAX);
    strncpy(cpath,path,strlen(path));
    
    status = true;
    pp = cpath;
    while (status == true && (sp = strchr(pp, '/')) != 0){
        if (sp != pp){
            *sp = '\0';
            status = do_mkdir(cpath, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == true)
        status = do_mkdir(path, mode);
    return (status);
}
