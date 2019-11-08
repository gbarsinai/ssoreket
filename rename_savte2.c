#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "QRRead.h"
#include "ssPrint.h"
#include "fixImproved.h"
#include "config.h"

#define M_FIX_IMPROVED 	4
#define M_B 			3
#define M_A 			2
#define M_REVERSE 		1
#define M_DO_NOTHING 	0
#define M_INVALIDE 		-1

#define UNICODE
#define _UNICODE

#define HEB

#ifdef HEB
#define DIR_SHKUFIYOT "שקופיות"
#define DIR_TIFZORET "תפזורת"
#define DIR_A "אלבומים"
#define DIR_AD "אלבומי דבק"
#define DIR_AK "אלבומי כיסים"
#define DIR_IMPROVED "משופרות"
#else
#define DIR_SHKUFIYOT "SH"
#define DIR_TIFZORET "T"
#define DIR_A "A"
#define DIR_AD "AD"
#define DIR_AK "AK"
#define DIR_IMPROVED "M"
#endif

int g_choice;
char* s_exeName;

char *g_fileList[10000];
int g_fileListLen = 0;

void printlist();

void freeFileList()
{
	printf("free:\n");
	for (int i = 0; i < g_fileListLen ; ++i)
	{
		free(g_fileList[i]);
		g_fileList[i] = NULL;
	}
}

int isJpg(char *fileName)
{
	int len = 0;

	len = strlen(fileName);
	return 	(fileName[len - 4] == '.' &&
			(fileName[len - 3] == 'j' || fileName[len - 3] == 'J') &&
			(fileName[len - 2] == 'p' || fileName[len - 2] == 'P') &&
			(fileName[len - 1] == 'g' || fileName[len - 1] == 'G'));
}

void setFileList(DIR *d, struct dirent* currentFile)
{
	int i = 0;

	do{
		if (currentFile->d_type == DT_DIR)
		{
			printf("Not supporting mixed files and folders!!!! (Ignoring %s)\n", currentFile->d_name);
			continue;
		}

		if (!isJpg(currentFile->d_name))
		{
			printf("Not JPG!!!! (Ignoring %s)\n", currentFile->d_name);
			continue;
		}

		//printf("%d - %s\n", i, currentFile->d_name);
		g_fileList[i] = malloc(strlen(currentFile->d_name));
		strcpy(g_fileList[i], currentFile->d_name);
		i++;
	}while ((currentFile = readdir(d)) != NULL);
	g_fileList[i] = 0;
	g_fileListLen = i;
}

int getNumber(char *str)
{
	char tmpStr[200] = {0};
	int j = 0, i = 0;
	int len = strlen(str);

	for (i = 0; i < len; ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			break;
		}
	}

	if (i == len)
	{
		return -1;
	}

	while(str[i] >= '0' && str[i] <= '9')
	{
		tmpStr[j] = str[i];
		i++;
		j++;
	}
	return atol(tmpStr);
}

int myCompar(char *strA, char *strB)
{
	int numA = getNumber(strA);
	int numB = getNumber(strB);

	if (numA > -1 && numB > -1)
	{
		if (numA > numB)
		{
			return 1;
		}
		else if (numB > numA)
		{
			return -1;
		}else
		{
			return 0;
		}
	}
	return strcmp(strA, strB);
}

void sortFileList()
{
	char *tmp = NULL;
	int swap = 0;

	printf("Sorting....\n");
	do
	{
		swap = 0;
		for (int i = 0; i < g_fileListLen - 1; ++i)
		{
			if (myCompar(g_fileList[i], g_fileList[i + 1]) > 0)
			{
				tmp = g_fileList[i];
				g_fileList[i] = g_fileList[i + 1];
				g_fileList[i + 1] = tmp;
				swap = 1;
			}
		}
	}while(swap);
}

void printlist()
{
	printf("list:\n");
	for (int i = 0; i < g_fileListLen ; ++i)
	{
		printf("%s, ", g_fileList[i]);
	}
}

void printAll(const char *path, int mode, const char* parent)
{
	struct dirent *dir;
	DIR *d = opendir(path);

	if (d)
	{
		printf("%s\n", path);
		printf("------------------------------\n");
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
			if (!strcmp(dir->d_name, ".") ||
					!strcmp(dir->d_name, "..") ||
					!strcmp(dir->d_name, "Thumbs.db") ||
					!strcmp(dir->d_name, s_exeName))
			{
				continue;
			}
			if (dir->d_type == DT_DIR )
			{
				char newDir[MAX_PATH] = {0};
				int shouldBreak = 0;

				sprintf(newDir, "%s/%s", path, dir->d_name);
				if (!strcmp(DIR_A, dir->d_name) || !strcmp(DIR_AK, dir->d_name))
				{
					printf("enter M_REVERSE\n");
					mode = M_REVERSE;
				}
				if (!strcmp(DIR_TIFZORET, dir->d_name) ||
					!strcmp(DIR_SHKUFIYOT, dir->d_name) || 
					!strcmp(DIR_IMPROVED, dir->d_name))
				{
					if (!strcmp(DIR_IMPROVED, dir->d_name) && g_choice == CHOICE_IMP)
					{
						printf("enter M_FIX_IMPROVED\n");
						mode = M_FIX_IMPROVED;
					}else
					{
						printf("enter M_DO_NOTHING\n");
						mode = M_DO_NOTHING;
					}
				}
				if (!strcmp("_a",dir->d_name))
				{
					printf("enter _a\n");
					mode = M_A;
				}
				if (!strcmp("_b",dir->d_name))
				{
					printf("enter _b\n");
					mode = M_B;
					shouldBreak = 1;
				}
				if (mode == M_A || mode == M_B)
				{
					printAll(newDir, mode, parent);
				}else
				{
					printAll(newDir, mode, dir->d_name);
				}
				if (shouldBreak)
				{
					if (g_choice != CHOICE_MAKE_AB)
					{
						//Delete folders _a and _b
						char path_a[MAX_PATH] = {'\0'};
						char path_b[MAX_PATH] = {'\0'};
						int reta = 0;
						int retb = 0;

						sprintf(path_a, "%s/%s", path, "_a");
						sprintf(path_b, "%s/%s", path, "_b");
						reta = rmdir(path_a);
						retb = rmdir(path_b);
						if (reta == -1 || retb == -1)
						{
							printf("[error %d] Fail on delete: %s OR %s\n", errno, path_a, path_b);
						}
					}
					return;
				}
			}else
			{

				//Run on files
				if (g_choice == CHOICE_IMP && mode != M_FIX_IMPROVED)
				{
					return;
				}
				setFileList(d, dir);
				sortFileList();

				if (mode == M_FIX_IMPROVED)
				{
					fixImproved(path, g_fileList, g_fileListLen);
					return;
				}

				if (g_choice == CHOICE_REMOVE_EMPTY)
				{
					int emptyIndex = 0;
					for (int  i = 0; i < g_fileListLen; ++i) {
						char newName[MAX_PATH] = {0};
						char oldName[MAX_PATH] = {0};
						int ret = 0;
						char newPath[MAX_PATH] = {0};
						int fileNameLen = 0;

						sprintf(newPath, "%s", path);
						sprintf(newName , "%s/%d %s%s", newPath, emptyIndex, parent, ".jpg");
						sprintf(oldName , "%s/%s", path, g_fileList[i]);
						fileNameLen = strlen(oldName);
						if (fileNameLen > 3 && !strcmp(&(oldName[fileNameLen - 7]), "D__.jpg"))
						{
							remove(oldName);
							continue;
						}
						ret = rename(oldName, newName);
						emptyIndex++;
						if (ret == -1)
						{
							printf("[%d] Fail on file: %s\n", errno, oldName);
						}
					}
					return;
				}

				//=== For QR
				if (g_choice == CHOICE_MAKE_AB)
				{
					renameQR(path, g_fileList, g_fileListLen);
					return;
				}
				//==========

				for (int  i = 0; i < g_fileListLen; ++i) {
					char newName[MAX_PATH] = {0};
					char oldName[MAX_PATH] = {0};
					int oldNameLen = 0;
					int ret = 0;
					int index = i;
					char newPath[MAX_PATH] = {0};

					sprintf(newPath, "%s", path);
					if (mode == M_REVERSE)
					{
						index = g_fileListLen - i;
					}else if (mode == M_A)
					{
						index = i * 2 + 1;
					}else if (mode == M_B)
					{
						index = (g_fileListLen - i) * 2;
					}
					if (mode == M_A || mode == M_B)
					{
						newPath[strlen(newPath)-3] = '\0';
					}
					if (mode == M_INVALIDE)
					{
						printf("Fail on file (no mode was set): %s\n", oldName);
						continue;
					}
					if(mode == M_DO_NOTHING)
					{
						continue;
					}
					sprintf(oldName , "%s/%s", path, g_fileList[i]);
					oldNameLen = strlen(oldName);
					if (oldNameLen > 3 && !strcmp(&(oldName[oldNameLen - 7]), "D__.jpg"))
					{
						sprintf(newName , "%s/%d %s_D__%s", newPath, index, parent, ".jpg");
					}else
					{
						sprintf(newName , "%s/%d %s%s", newPath, index, parent, ".jpg");
					}
					ret = rename(oldName, newName);
					if (ret == -1)
					{
						printf("[%d] Fail on file: %s\n", errno, oldName);
					}
				}
			}
			//closedir(d);
		}
	}
}

int main(int argc, char **argv)
{
	if(!config()){
		printf("Fail in configuration!. by by.\n");
		getchar();
		return 1;
	}
	s_exeName = strrchr(argv[0], '\\');
	if (s_exeName != NULL)
	{
		s_exeName++; //Skip the '\'
	}else
	{
		s_exeName = argv[0];
	}
	if (argc == 1)
		g_choice = getChoice();
	else
		g_choice = atoi(argv[1]);

	if (g_choice == CHOICE_AB_RENAME_EMPTY)
	{
		g_choice = CHOICE_MAKE_AB;
		printAll(".", M_INVALIDE, "");
		g_choice = CHOICE_RENAME;
		printAll(".", M_INVALIDE, "");
		g_choice = CHOICE_REMOVE_EMPTY;
		printAll(".", M_INVALIDE, "");
	}else
	{
		printAll(".", M_INVALIDE, "");
	}

	printf("Done.");
	getchar();
	return(0);
}
