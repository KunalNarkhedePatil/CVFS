// VFS.h
#ifndef VFS_H
#define VFS_H

#ifdef VFS_EXPORTS
#define VFS_API __declspec(dllexport)
#else
#define VFS_API __declspec(dllimport)
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
struct SUPERBLOCK {
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
    int permission; //  1  23
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
    VFS_API void InitialiseSuperBlock();
    VFS_API void CreateDILB();
    VFS_API int CreateFile(const char* name, int permission);
    VFS_API int OpenFile(const char* name, int mode);
    VFS_API int CloseFileByName(const char* name);
    VFS_API void CloseAllFile();
    VFS_API int ReadFile(int fd, char* buffer, int size);
    VFS_API int WriteFile(int fd, const char* buffer, int size);
    VFS_API int LseekFile(int fd, int size, int from);
    VFS_API void ls_file();
    VFS_API int fstat_file(int fd);
    VFS_API int stat_file(const char* name);
    VFS_API int truncate_File(const char* name);
    VFS_API int GetFDFromName(const char* name);
    VFS_API void DisplayHelp();
    VFS_API void man(const char* command);
}

#endif // VFS_H
