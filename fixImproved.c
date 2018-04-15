/*
 * fixImproved.c
 *
 *  Created on: Feb 6, 2018
 *      Author: W7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int fixImproved(const char *dirPath, char** fileList, int listLen)
{
	char newDirName[100] = {0};
	char newFileName[100] = {0};
	char newDirPath[256] = {0};
	char oldfilePath[256] = {0};
	char newFilePath[256] = {0};
	int res = 0;
	
	for (int  i = 0; i < listLen; ++i)
	{
		int orgFileIndex = 0;
		for(; fileList[i][orgFileIndex] != ' '; orgFileIndex++)
		{
			newDirName[orgFileIndex] = fileList[i][orgFileIndex];
		}
		newDirName[orgFileIndex] = '\0';
		orgFileIndex++;
		for(int j = 0; fileList[i][orgFileIndex] != '\0'; orgFileIndex++)
		{
			if (fileList[i][orgFileIndex] == ')' || fileList[i][orgFileIndex] == '(')
			{
				continue;
			}
			newFileName[j++] = fileList[i][orgFileIndex];
		}
		sprintf(newDirPath, "%s/%s", dirPath, newDirName);
		mkdir(newDirPath);
		sprintf(oldfilePath, "%s/%s", dirPath,  fileList[i]);
		sprintf(newFilePath, "%s/%s", newDirPath, newFileName);
		res = rename(oldfilePath, newFilePath);
		if (res != 0)
		{
			printf("Error can't move \n%s \nto \n%s\n", oldfilePath, newFilePath);
		}
	}
	
	return 0;
}
