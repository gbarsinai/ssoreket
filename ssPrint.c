/*
 * ssPrint.c
 *
 *  Created on: Feb 2, 2018
 *      Author: W7
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char scanfDup[100];

static int choiceToInt(int choice)
{
	switch (choice) {
	case '0':
		exit(0);
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		break;
	default:
		printf("\nInvalid choice.\n");
		return 0;
		break;
	}
	return 1;
}

int getChoice()
{
	char c = 0;

	do
	{
		printf("\n========================\n");
		printf(" 1 - Prepare for crop AD.\n");
		printf(" 2 - Rename.\n");
		printf(" 3 - Fix improved into folders.\n");
		printf(" 4 - Make _a _b folders only.\n");
		printf(" 5 - Remove empty.\n");
		printf(" 0 - Exit.\n");
		printf("========================\n");
		printf("Enter your choice: ");
		scanf("%c%c", &c, scanfDup);
	}while(!choiceToInt(c));
	return c - '0';
}


