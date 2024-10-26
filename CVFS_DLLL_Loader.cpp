#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef void (*INITIALISESUPERBLOCK)();
typedef void (*CREATEDILB)();
typedef void (*LS_FILE)();
typedef void (*CLOSEALLFILE)();
typedef void (*DISPLAYHELP)();
typedef int (*CREATEFILE)(const char*, int);
typedef int (*OPENFILE)(const char*, int);
typedef int (*CLOSEFILEBYNAME)(const char*);
typedef int (*READFILE)(int, char*, int);
typedef int (*WRITEFILE)(int, const char*, int);
typedef int (*LSEEKFILE)(int, int, int);
typedef int (*STATFILE)(const char*);
typedef int (*FSTATFILE)(int);
typedef int (*TRUNCATEFILE)(const char*);
typedef int (*GETFDFROMNAME)(const char*);
typedef void (*MAN)(const char*);

int main() {
    // Load the DLL
    HINSTANCE hDLL = LoadLibrary("VFS.dll");
    if (hDLL == NULL) {
        std::cerr << "Could not load the DLL!" << std::endl;
        return -1;
    }

    // Function pointers
    INITIALISESUPERBLOCK ptrInitialiseSuperBlock = 
        (INITIALISESUPERBLOCK)GetProcAddress(hDLL, "InitialiseSuperBlock");
    CREATEDILB ptrCreateDILB = 
        (CREATEDILB)GetProcAddress(hDLL, "CreateDILB");
    LS_FILE ptrLSFile = 
        (LS_FILE)GetProcAddress(hDLL, "ls_file");
    CLOSEALLFILE ptrCloseAllFile = 
        (CLOSEALLFILE)GetProcAddress(hDLL, "CloseAllFile");
    DISPLAYHELP ptrDisplayHelp = 
        (DISPLAYHELP)GetProcAddress(hDLL, "DisplayHelp");
    CREATEFILE ptrCreateFile = 
        (CREATEFILE)GetProcAddress(hDLL, "CreateFile");
    OPENFILE ptrOpenFile = 
        (OPENFILE)GetProcAddress(hDLL, "OpenFile");
    CLOSEFILEBYNAME ptrCloseFileByName = 
        (CLOSEFILEBYNAME)GetProcAddress(hDLL, "CloseFileByName");
    READFILE ptrReadFile = 
        (READFILE)GetProcAddress(hDLL, "ReadFile");
    WRITEFILE ptrWriteFile = 
        (WRITEFILE)GetProcAddress(hDLL, "WriteFile");
    LSEEKFILE ptrLseekFile = 
        (LSEEKFILE)GetProcAddress(hDLL, "LseekFile");
    STATFILE ptrStatFile = 
        (STATFILE)GetProcAddress(hDLL, "stat_file");
    FSTATFILE ptrFstatFile = 
        (FSTATFILE)GetProcAddress(hDLL, "fstat_file");
    TRUNCATEFILE ptrTruncateFile = 
        (TRUNCATEFILE)GetProcAddress(hDLL, "truncate_File");
    GETFDFROMNAME ptrGetFDFromName = 
        (GETFDFROMNAME)GetProcAddress(hDLL, "GetFDFromName");
    MAN ptrMan = 
        (MAN)GetProcAddress(hDLL, "man");

    // Call initialization functions
    ptrInitialiseSuperBlock();
    ptrCreateDILB();

    char* ptr = NULL;
    int fd = 0, count = 0;
    int ret = 0;
    char command[4][80], str[80], arr[1040];

    while (1) {
        fflush(stdin);
        strcpy(str, "");
        printf("\Semisoft VFS : > ");

        if (fgets(str, sizeof(str), stdin) == NULL) {
            perror("Error reading input");
            continue;
        }

        count = sscanf(str, "%s%s%s%s", command[0], command[1], command[2], command[3]);

        if (count == 1) {
            if (strcmp(command[0], "ls") == 0) {
                ptrLSFile();
            } else if (strcmp(command[0], "closeall") == 0) {
                ptrCloseAllFile();
                printf("All files closed successfully\n");
                continue;
            } else if (strcmp(command[0], "clear") == 0) {
                system("cls"); // Use "cls" for Windows
                continue;
            } else if (strcmp(command[0], "help") == 0) {
                ptrDisplayHelp();
                continue;
            } else if (strcmp(command[0], "exit") == 0) {
                ptrCloseAllFile();
                printf("Terminating the Semisoft Virtual File System\n");
                break;
            } else {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        } else if (count == 2) {
            if (strcmp(command[0], "stat") == 0) {
                ret = ptrStatFile(command[1]);
                if (ret == -1)
                    printf("ERROR : Incorrect parameter\n");
                else if (ret == -2)
                    printf("ERROR : There is no such file\n");
                continue;
            } else if (strcmp(command[0], "fstat") == 0) {
                ret = ptrFstatFile(atoi(command[1]));
                if (ret == -1)
                    printf("ERROR : Incorrect parameter\n");
                else if (ret == -2)
                    printf("ERROR : There is no such file\n");
                continue;
            } else if (strcmp(command[0], "close") == 0) {
                ret = ptrCloseFileByName(command[1]);
                if (ret == -1)
                    printf("ERROR : There is no such file\n");
                continue;
            } else if (strcmp(command[0], "rm") == 0) {
                ret = rm_File(command[1]); // Ensure this function is defined
                if (ret == -1)
                    printf("ERROR : There is no such file\n");
                continue;
            } else if (strcmp(command[0], "man") == 0) {
                ptrMan(command[1]);
            } else if (strcmp(command[0], "write") == 0) {
                fd = ptrGetFDFromName(command[1]);
                if (fd == -1) {
                    printf("Error: Incorrect parameter\n");
                    continue;
                }
                printf("Enter the data : \n");
                scanf(" %[^\n]", arr); // Fixed to properly read input

                int len = strlen(arr);
                if (len == 0) {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                ret = ptrWriteFile(fd, arr, len);
                if (ret == -1)
                    printf("Permission denied\n");
                else if (ret == -2)
                    printf("ERROR: There is no sufficient memory to write\n");
                else if (ret == -3)
                    printf("ERROR : It is not a regular file\n");
            } else if (strcmp(command[0], "truncate") == 0) {
                ret = ptrTruncateFile(command[1]);
                if (ret == -1)
                    printf("Error : Incorrect parameter\n");
            } else {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        } else if (count == 3) {
            if (strcmp(command[0], "create") == 0) {
                ret = ptrCreateFile(command[1], atoi(command[2]));
                if (ret >= 0)
                    printf("File is successfully created with file descriptor : %d\n", ret);
                else if (ret == -1)
                    printf("ERROR : Incorrect parameter\n");
                else if (ret == -2)
                    printf("ERROR : There are no inodes\n");
                else if (ret == -3)
                    printf("ERROR : File already exists\n");
                else if (ret == -4)
                    printf("ERROR : Memory allocation failure\n");
                continue;
            } else if (strcmp(command[0], "open") == 0) {
                ret = ptrOpenFile(command[1], atoi(command[2]));
                if (ret >= 0)
                    printf("File is successfully opened with file descriptor : %d\n", ret);
                else if (ret == -1)
                    printf("ERROR : Incorrect parameter\n");
                else if (ret == -2)
                    printf("ERROR : File already exists\n");
                else if (ret == -3)
                    printf("ERROR : There are no sufficient inodes\n");
                else if (ret == -4)
                    printf("ERROR : Memory allocation failure\n");
                continue;
            } else if (strcmp(command[0], "lseek") == 0) {
                fd = atoi(command[1]);
                int offset = atoi(command[2]);
                ret = ptrLseekFile(fd, offset, SEEK_SET);
                if (ret == -1) {
                    printf("ERROR: Incorrect parameter\n");
                } else {
                    printf("New file position : %d\n", ret);
                }
                continue;
            }
        } else if (count == 4) {
            if (strcmp(command[0], "write") == 0) {
                fd = ptrGetFDFromName(command[1]);
                if (fd == -1) {
                    printf("Error: Incorrect parameter\n");
                    continue;
                }
                printf("Enter the data : \n");
                scanf(" %[^\n]", arr);

                int len = strlen(arr);
                if (len == 0) {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                ret = ptrWriteFile(fd, arr, len);
                if (ret == -1)
                    printf("Permission denied\n");
                else if (ret == -2)
                    printf("ERROR: There is no sufficient memory to write\n");
                else if (ret == -3)
                    printf("ERROR : It is not a regular file\n");
            } else {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        } else {
            printf("\nERROR : Command not found !!!\n");
            continue;
        }
    }

    // Free the DLL
    FreeLibrary(hDLL);
    return 0;
}
