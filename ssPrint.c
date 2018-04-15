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

static int print_are_you_sure(int choice)
{
	char c = 0;
	switch (choice) {
	case '0':
		exit(0);
		break;
	case '1':
	case '2':
	case '3':
	case '4':
		printf("\n===== Are you sure ? ======\n");
		printf("Choice %c (y/n)?\n", choice);
		break;
	default:
		printf("\nInvalid choice.\n");
		return 0;
		break;
	}
	scanf("%c%c", &c, scanfDup);
	if (c == 'y' || c == 'Y')
	{
		return 1;
	}
	return 0;
}

int getChoice()
{
	char c = 0;

	do
	{
		printf("\n========================\n");
		printf(" 1 - Prepare for crop AD.\n");
		printf(" 2 - Rename all.\n");
		printf(" 3 - Fix improved into folders.\n");
		printf(" 4 - Make _a _b folders only.\n");
		printf(" 0 - Exit.\n");
		printf("========================\n");
		printf("Enter your choice: ");
		scanf("%c%c", &c, scanfDup);
	}while(!print_are_you_sure(c));
	return c - '0';
}


