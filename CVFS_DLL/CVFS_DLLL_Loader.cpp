#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include<fcntl.h>
#include <iostream>
#include<io.h>

typedef void (*INITIALISESUPERBLOCK)();
INITIALISESUPERBLOCK ptrInitialiseSuperBlock;
typedef void (*CREATEDILB)();
CREATEDILB ptrCreateDILB;
typedef void (*LS_FILE)();
LS_FILE ptrLSFile ;

typedef int (*COUNTFILES)();
COUNTFILES PtrCountFiles;
typedef void (*CLOSEALLFILE)();
CLOSEALLFILE ptrCloseAllFile;
typedef void (*DISPLAYHELP)();
 DISPLAYHELP ptrDisplayHelp;
typedef int (*CREATEFILE)(char*, int);
CREATEFILE ptrCreateFile;
typedef int (*OPENFILE)(const char*, int);
OPENFILE ptrOpenFile;
typedef int (*CLOSEFILEBYNAME)(const char*);
CLOSEFILEBYNAME ptrCloseFileByName;
typedef int (*READFILE)(int, char*, int);
 READFILE ptrReadFile;
typedef int (*WRITEFILE)(int, const char*, int);
WRITEFILE ptrWriteFile;
typedef int (*RM_FILE)(char *);
RM_FILE ptrRm_File;
typedef int (*LSEEKFILE)(int, int, int	);
LSEEKFILE ptrLseekFile;
typedef int (*STATFILE)(const char*);
STATFILE ptrStatFile;
typedef int (*FSTATFILE)(int);
 FSTATFILE ptrFstatFile;
typedef int (*TRUNCATEFILE)(const char*);
TRUNCATEFILE ptrTruncateFile;
typedef int (*GETFDFROMNAME)(const char*);
GETFDFROMNAME ptrGetFDFromName;
typedef void (*MAN)(const char*);
MAN ptrMan;
typedef int (*CHANGEFILEPERMISSIONS)(char*, int);
CHANGEFILEPERMISSIONS ptrChangeFilePermissions;

typedef int (*RENAMEFILENAME)(char *,char *);
RENAMEFILENAME ptrRenameFileName;

int main() 
{
    // Load the DLL
    HMODULE hDLL= LoadLibrary(TEXT("C:\\Users\\User\\Desktop\\CVFS_DLL\\Debug\\CVFS_DLL.dll"));
    if (hDLL == NULL) {
        std::cerr << "Could not load the DLL!" << std::endl;
        return -1;
    }

    // Function pointers
     ptrInitialiseSuperBlock = (INITIALISESUPERBLOCK)GetProcAddress(hDLL, "InitialiseSuperBlock");
     ptrCreateDILB = (CREATEDILB)GetProcAddress(hDLL, "CreateDILB");
     ptrLSFile = (LS_FILE)GetProcAddress(hDLL, "ls_file");
	 PtrCountFiles=(COUNTFILES)GetProcAddress(hDLL,"countFiles");
     ptrCloseAllFile = (CLOSEALLFILE)GetProcAddress(hDLL, "CloseAllFile");
     ptrDisplayHelp = (DISPLAYHELP)GetProcAddress(hDLL, "DisplayHelp");
     ptrCreateFile = (CREATEFILE)GetProcAddress(hDLL, "CreateFile");
     ptrOpenFile = (OPENFILE)GetProcAddress(hDLL, "OpenFile");
     ptrCloseFileByName = (CLOSEFILEBYNAME)GetProcAddress(hDLL, "CloseFileByName");
     ptrReadFile = (READFILE)GetProcAddress(hDLL, "ReadFile");
     ptrWriteFile = (WRITEFILE)GetProcAddress(hDLL, "WriteFile");
	 ptrRm_File=(RM_FILE)GetProcAddress(hDLL, "rm_File");
     ptrLseekFile = (LSEEKFILE)GetProcAddress(hDLL, "LseekFile");
     ptrStatFile = (STATFILE)GetProcAddress(hDLL, "stat_file");
     ptrFstatFile = (FSTATFILE)GetProcAddress(hDLL, "fstat_file");
     ptrTruncateFile = (TRUNCATEFILE)GetProcAddress(hDLL, "truncate_File");
     ptrGetFDFromName = (GETFDFROMNAME)GetProcAddress(hDLL, "GetFDFromName");
     ptrMan = (MAN)GetProcAddress(hDLL, "man");

	 ptrChangeFilePermissions=(CHANGEFILEPERMISSIONS)GetProcAddress(hDLL,"ChangeFilePermissions");
     ptrRenameFileName=(RENAMEFILENAME)GetProcAddress(hDLL,"RenameFileName");
    // Call initialization functions
    ptrInitialiseSuperBlock();
    ptrCreateDILB();

    char* ptr = NULL;
    int fd = 0, count = 0;
    int ret = 0;
    char command[4][80], str[80], arr[1040];

   
    while (1)
    {
        fflush(stdin);
        strcpy(str, "");
        printf("Kunal VFS : > ");

        if (fgets(str, sizeof(str), stdin) == NULL)
        {
            perror("Error reading input");
            continue;
        }

        count = sscanf(str, "%s%s%s%s", command[0], command[1], command[2], command[3]);

        if (count == 1)
        {
            if (strcmp(command[0], "ls") == 0)
            {
                ptrLSFile();
            }
			else if(strcmp(command[0], "countfiles") == 0)
			{
				int NoOfFiles=PtrCountFiles();

				if(NoOfFiles==-1)
				{
					printf("Error:there are no files\n");
				}
				else
				{
					printf("Number of files is :%d\n",NoOfFiles);
				}
			}
            else if (strcmp(command[0], "closeall") == 0)
            {
                ptrCloseAllFile();
                printf("All files closed successfully\n");
                continue;
            }
            else if (strcmp(command[0], "clear") == 0)
            {
                system("cls"); // Use "clear" for Unix-like systems
                continue;
            }
            else if (strcmp(command[0], "help") == 0)
            {
                ptrDisplayHelp();
                continue;
            }
            else if (strcmp(command[0], "exit") == 0)
            {
                ptrCloseAllFile();
                printf("Terminating the Semisoft Virtual File System\n");
                break;
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if (count == 2)
        {
            if (strcmp(command[0], "stat") == 0)
            {
                ret = ptrStatFile(command[1]);
                if (ret == -1)
				{
					printf("ERROR : Incorrect parameter\n");
				}
                else if (ret == -2)
				{
                    printf("ERROR : There is no such file\n");
				}
                continue;
            }
            else if (strcmp(command[0], "fstat") == 0)
            {
                ret = ptrFstatFile(atoi(command[1]));
                if (ret == -1)
				{
                    printf("ERROR : Incorrect parameter\n");
				}
                else if (ret == -2)
				{
                    printf("ERROR : There is no such file\n");
				}
                continue;
            }
            else if (strcmp(command[0], "close") == 0)
            {
                ret = ptrCloseFileByName(command[1]);
                if (ret == -1)
				{
                    printf("ERROR : There is no such file\n");
				}
                continue;
            }
            else if (strcmp(command[0], "rm") == 0)
            {
                ret = ptrRm_File(command[1]);
                if (ret == -1)
				{
                    printf("ERROR : There is no such file\n");
				}
                continue;
            }
            else if (strcmp(command[0], "man") == 0)
            {
				char * name=command[1];
                ptrMan(name);
            }
            else if (strcmp(command[0], "write") == 0)
            {
                fd = ptrGetFDFromName(command[1]);
                if (fd == -1)
                {
                    printf("Error: Incorrect parameter\n");
                    continue;
                }
                printf("Enter the data : \n");
                scanf(" %[^\n]", arr); // Fixed to properly read input

                int len = strlen(arr);
                if (len == 0)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
				ret = ptrWriteFile(fd, arr, len);
                if (ret == -1)
				{
                    printf("Permission denied\n");
				}
                else if (ret == -2)
				{
                    printf("ERROR: There is no sufficient memory to write\n");
				}
                else if (ret == -3)
				{
                    printf("ERROR : It is not a regular file\n");
				}
            }
            else if (strcmp(command[0], "truncate") == 0)
            {

				ret = ptrTruncateFile(command[1]);
                if (ret == -1)
				{
                    printf("Error : Incorrect parameter\n");
				}
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if (count == 3)
        {
            if (strcmp(command[0], "create") == 0)
            {
				ret = ptrCreateFile(command[1],atoi(command[2]));

                if (ret >= 0)
				{
                    printf("File is successfully created with file descriptor : %d\n", ret);
				}
                else if (ret == -1)
				{
                    printf("ERROR : Incorrect parameter\n");
				}
                else if (ret == -2)
				{
                    printf("ERROR : There are no inodes\n");
				}
                else if (ret == -3)
				{
                    printf("ERROR : File already exists\n");
				}
                else if (ret == -4)
				{
                    printf("ERROR : Memory allocation failure\n");
				}
                continue;
            }
            else if (strcmp(command[0], "open") == 0)
            {
                //ret = OpenFile(command[1], atoi(command[2]));
				ret = ptrOpenFile(command[1], atoi(command[2]));
                if (ret >= 0)
				{
                    printf("File is successfully opened with file descriptor : %d\n", ret);
				}
                else if (ret == -1)
				{
                    printf("ERROR : Incorrect parameter\n");
				}
                else if (ret == -2)
				{
                    printf("ERROR : File not present\n");
				}
                else if (ret == -3)
				{
                    printf("ERROR : Permission denied\n");
				}
                continue;
            }
			else if(strcmp(command[0],"mv")==0)
			{
				ret=ptrRenameFileName(command[1],command[2]);
				if (ret > 0)
				{
                    printf("File rename successfully\n");
				}
                else if (ret == -1)
				{
                    printf("ERROR : Incorrect parameter\n");
				}
                else if (ret == -2)
				{
                    printf("Error:there are no files\n");
				}
			    continue;
			}
            else if (strcmp(command[0], "read") == 0)
            {
                //fd = GetFDFromName(command[1]);
				fd = ptrGetFDFromName(command[1]);
                if (fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                int size = atoi(command[2]);
                ptr = (char *)malloc(size + 1);
                if (ptr == NULL)
                {
                    printf("Error : Memory allocation failure\n");
                    continue;
                }
                //ret = ReadFile(fd, ptr, size);
				ret=ptrReadFile(fd,ptr,size);

                if (ret == -1)
				{
                    printf("ERROR : File not existing\n");
				}
                else if (ret == -2)
				{
                    printf("ERROR : Permission denied\n");
				}
                else if (ret == -3)
				{
                    printf("ERROR : Reached end of file\n");
				}
                else if (ret == -4)
				{
                    printf("ERROR : It is not a regular file\n");
				}
                else if (ret == 0)
				{
                    printf("ERROR : File empty\n");
				}
                else if (ret > 0)
				{
                    _write(2, ptr, ret);
				    printf("\n");
				}
                free(ptr);
                continue;
            }
			if (strcmp(command[0], "changefilepermission") == 0)
            {

				ret = ptrChangeFilePermissions(command[1],atoi(command[2]));

                if (ret > 0)
				{
                    printf("File is permission change successfully\n");
				}
                else if (ret == -1)
				{
                    printf("ERROR : Incorrect parameter\n");
				}
                else if (ret == -2)
				{
                    printf("Error:there are no files\n");
				}
                continue;
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if (count == 4)
        {
            if (strcmp(command[0], "lseek") == 0)
            {
                //fd = GetFDFromName(command[1]);
				fd = ptrGetFDFromName(command[1]);
                if (fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
				ret = ptrLseekFile(fd, atoi(command[2]), atoi(command[3]));
                if (ret == -1)
                {
                    printf("ERROR : Unable to perform lseek\n");
                }
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else
        {
            printf("\nERROR : Command not found !!!\n");
            continue;
        }
    }


    // Free the DLL
    FreeLibrary(hDLL);
    return 0;
}




