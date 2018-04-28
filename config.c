/*
 * config.c
 *
 *  Created on: Feb 10, 2018
 *      Author: W7
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define CONFIG_FILE_PATH "C:/SSQR/ssqr_config.txt"
#define VERSION "2.0.4"

int config()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(CONFIG_FILE_PATH, "r");
    if (fp == NULL){
    	printf("= No Configuration file was found. (%s).\n", CONFIG_FILE_PATH);
        return 1;
    }
    printf("Version: %s\n\n", VERSION);
    printf("Configuration:\n");
    while ((read = getline(&line, &len, fp)) != -1) {
    	  char *key;
    	  char *val;
    	  key = strtok (line, "=");
    	  val = strtok (NULL, "=");
    	  val[strlen(val) - 1] = '\0';
    	  printf("%s = %s\n", key, val);

    	  //DEFAULTS
    	  g_config_max_qrSize = 1024*100;
    	  g_config_min_qrSize = 0;
    	  g_config_max_scand_qrSize = 1024*100;
    	  g_config_min_scand_qrSize = 0;

    	  if (!strcmp(key, "max_qr_size")){
    		  g_config_max_qrSize = atoi(val) * 1024;
    	  }else if (!strcmp(key, "min_qr_size")){
    		  g_config_min_qrSize = atoi(val) * 1024;
    	  }else if (!strcmp(key, "max_scand_qr_size")){
    		  g_config_max_scand_qrSize = atoi(val) * 1024;
    	  }else if (!strcmp(key, "min_scand_qr_size")){
    		  g_config_min_scand_qrSize = atoi(val) * 1024;
    	  }else {
			printf("Invalid Config %s.\n", key);
			return 0;
		}
    }
    printf("\n");

    fclose(fp);
    if (line){
        free(line);
    }

//    printf("g_config_max_qrSize: %d\n", g_config_max_qrSize);
//    printf("g_config_min_qrSize: %d\n", g_config_min_qrSize);
//    printf("g_config_max_scand_qrSize: %d\n", g_config_max_scand_qrSize);
//    printf("g_config_min_scand_qrSize: %d\n", g_config_min_scand_qrSize);

	return 1;
}
