/*
 * QRRead.c
 *
 *  Created on: Jan 27, 2018
 *      Author: W7
 */
#define NULL 0
#define FALSE 0
#define TRUE 1
#define MAX_PATH 1035
#define QR_TYPE_NONE 0
#define QR_TYPE_T 1
#define QR_TYPE_AD 2
#define QR_TYPE_AD_M 3
#define QR_TYPE_AD_E 4

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "config.h"

int readQR(char* jpgPath, char* outBuff)
{
	char cmd[MAX_PATH] = {0};
	strcpy(cmd, "zbarimg.exe --raw -q ");
	strcat(cmd, jpgPath);
	FILE *fp;
	char value[100] = {0};
	struct stat statFile;

	if (FALSE)//(g_config_max_qrSize != 0) //Disabled
	{
		stat(jpgPath, &statFile);
		if ((statFile.st_size > g_config_max_qrSize || statFile.st_size < g_config_min_qrSize) &&
				(statFile.st_size > g_config_max_scand_qrSize || statFile.st_size < g_config_min_scand_qrSize))
		{
			printf("%s Not QR size. its size is %d\n", jpgPath, (int)statFile.st_size);
			return FALSE;
		}
	}

	/* Open the command for reading. */
	fp = popen(cmd, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return FALSE;
	}

	/* Read the output a line at a time - output it. */
	fgets(value, sizeof(value)-1, fp);

	/* close */
	pclose(fp);

	if(strncmp(value, "SSQR_", 5) != 0)
	{
		printf("%s QR isn't starting in SSQR_\n", jpgPath);
		return FALSE;
	}

	value[strlen(value) - 1] = '\0'; // remove the \n
	strcpy(outBuff, &(value[5]));
	return TRUE;
}

int getType(char* val)
{
	if (strncmp(val, "AD_M", 4) == 0)
	{
		return QR_TYPE_AD_M;
	}
	if (strncmp(val, "AD_E", 4) == 0)
	{
		return QR_TYPE_AD_E;
	}
	if (strncmp(val, "T_", 2) == 0)
	{
		return QR_TYPE_T;
	}
	if (strncmp(val, "AD_", 3) == 0)
	{
		return QR_TYPE_AD;
	}
	return QR_TYPE_NONE;
}

int renameQR(const char *path, char** fileList, int listLen)
{
	char val[100] = {0};
	char fullPath[MAX_PATH] = {0};
	char newFullPath[MAX_PATH] = {0};
	char newDir[MAX_PATH] = {0};
	int res = 0;
	char side = 'a';
	char newDirName[MAX_PATH] = {0};
	int type = QR_TYPE_NONE;
	int isMiddleFound = TRUE;

	sprintf(fullPath , "%s/%s", path, fileList[0]);
	if(!readQR(fullPath, val))
	{
		return 0;
	}

	for (int  i = 0; i < listLen; ++i)
	{
		printf("QR process: %d / %d\r", i + 1, listLen);
		sprintf(fullPath , "%s/%s", path, fileList[i]);
		if(readQR(fullPath, val))
		{
			type = getType(val);
		}else
		{
			type = QR_TYPE_NONE;
		}
		switch (type){
		case QR_TYPE_T:
			side = 0;
			strcpy(newDirName, &(val[2]));
			sprintf(newDir, "%s/%s", path, newDirName);
			res += mkdir(newDir);
			if (res != 0)
			{
				printf("ERROR 3 !!!!!!!!!!!!!!!!");
				exit(1);
			}
			remove(fullPath); // delete QR
			break;
		case QR_TYPE_AD_M:
			isMiddleFound = TRUE;
			side = 'b';
			remove(fullPath); // delete QR
			break;
		case QR_TYPE_AD:
			if (!isMiddleFound)
			{
				printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				printf("WARRNING - middle not found for album %s.", newDirName);
				printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			}
			isMiddleFound = FALSE;
			strcpy(newDirName, &(val[3]));
			sprintf(newDir, "%s/%s", path, newDirName);
			res += mkdir(newDir);
			sprintf(newDir, "%s/%s/%s", path, newDirName, "_a");
			res += mkdir(newDir);
			sprintf(newDir, "%s/%s/%s", path, newDirName, "_b");
			res += mkdir(newDir);
			if (res != 0)
			{
				printf("ERROR 3.5 !!!!!!!!!!!!!!!!");
				exit(1);
			}
			side = 'a';
			remove(fullPath); // delete QR
			break;
		case QR_TYPE_AD_E:
		case QR_TYPE_NONE:
		default:
			if (newDirName == NULL)
			{
				printf("ERROR 4 !!!!!!!!!!!!!!!!");
				exit(1);
			}
			if (side != 0)
			{
				sprintf(newFullPath, "%s/%s/_%c/%s", path, newDirName, side, fileList[i]);
			}else
			{
				sprintf(newFullPath, "%s/%s/%s", path, newDirName, fileList[i]);
			}
			if (rename(fullPath, newFullPath) == -1)
			{
				printf("ERROR 5 !!!!!!!!!!!!!!!!");
				exit(1);
			}
			break;
		}
	}
	return 1;
}
