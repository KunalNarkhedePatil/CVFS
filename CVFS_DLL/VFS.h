// VFS.h
#ifndef VFS_H
#define VFS_H

#ifdef VFS_EXPORTS
#else
//#define VFS_API __declspec(dllimport)
#endif
#define MAXINODE 50

#define READ 1
#define WRITE 2
#define NULL 0

#define MAXFILESIZE 1024
#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2

// Custom structures used in the VFS
struct SUPERBLOCK 
{
    int TotalInodes;
    int FreeInode;
};

typedef struct inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;
    char *Buffer;
    int LinkCount;
    int ReferenceCount;
    int permission; //  1  2 3
	char fileModifiedDate[30];
    struct inode *next;
} INODE, *PINODE, **PPINODE;


typedef struct filetable
{
    int readoffset;
    int writeoffset;
    int count;
    int mode; // 1 2 3
    PINODE ptrinode;
} FILETABLE, *PFILETABLE;

typedef struct ufdt
{
    PFILETABLE ptrfiletable;
} UFDT;

UFDT UFDTArr[50];
SUPERBLOCK SUPERBLOCKobj;
PINODE head = NULL;

// Exported VFS functions
extern "C" {
    __declspec(dllimport) void InitialiseSuperBlock();
    __declspec(dllimport) void CreateDILB();
    __declspec(dllimport) int CreateFile(char* name, int permission);
    __declspec(dllimport) int OpenFile( char* name, int mode);
    __declspec(dllimport) int CloseFileByName( char* name);
    __declspec(dllimport) void CloseAllFile();
    __declspec(dllimport) int ReadFile(int fd, char* buffer, int size);
    __declspec(dllimport) int WriteFile(int fd,  char* buffer, int size);
    __declspec(dllimport) int rm_File(char *name);
    __declspec(dllimport) int LseekFile(int fd, int size, int from);
    __declspec(dllimport) void ls_file();
    __declspec(dllimport) int countFiles();
    __declspec(dllimport) int fstat_file(int fd);
    __declspec(dllimport) int stat_file( char* name);
    __declspec(dllimport) int truncate_File( char* name);
    __declspec(dllimport) int GetFDFromName( char* name);
    __declspec(dllimport) void DisplayHelp();
    __declspec(dllimport) void man(char* command);
    __declspec(dllimport) int ChangeFilePermissions(char* name, int permission);
    __declspec(dllimport) int RenameFileName(char* oldName,char *newName);
}

#endif // VFS_H
