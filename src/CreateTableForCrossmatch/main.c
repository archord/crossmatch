/* 
 * File:   main.cpp
 * Author: xy
 *
 * Created on November 14, 2012, 10:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "function.h"


extern int fileNumber;
extern int tableNumber;

void showHelp() {
    printf("createtableforcrossmatch (2012 Nov 15)\n\n");
    printf("usage: createtableforcrossmatch (defalut create today's tables use default config files)\n");
    printf("   or: createtableforcrossmatch [-c YYYYMMDD(today) | -d YYYYMMDD(today)] [-f configfile ] [-o outfile]\n");

    printf("--help       or -h:                   print help information\n");
    printf("--fNumber    or -fn <number>          table inherit, the number of file each table contained, must combine with --tNumber\n");
    printf("--tNumber    or -tn <number>          table inherit, the total number of table to be created, must combine with --fNumber\n");
    printf("--create     or -c  <date>            <date> can be \"YYYYMMDD\" or \"today\", default \"today\"\n");
    printf("                                      create four tables with name \"prefix<date>\"\n");
    printf("                                      \"prefix\" read from configfile: \"catfile_\", \"crossmatch_\", \"ot_\", \"ot_flux_\"\n");
    printf("--delete     or -d  <date>            <date> can be \"YYYYMMDD\" or \"today\", default \"today\"\n");
    printf("                                      delete four tables with name \"prefix<date>\"\n");
    printf("                                      \"prefix\" read from configfile: \"catfile_\", \"crossmatch_\", \"ot_\", \"ot_flux\"\n");
    printf("--configfile or -f  <file name>       database config file name, default \"create_table_database_config.txt\"\n");
    printf("--outfile    or -o  <file name>       config file for crossmatch program, default \"database_config.txt\"\n");
    printf("\nexample:\n");
    printf("\t\"createtableforcrossmatch -c today -f create_table_database_config.txt -o database_config.txt\"\n");

}

int main(int argc, char** argv) {
    int flag = CREATE_TABLE;
    char *configFileName = (char *) malloc(LINE);
    char *outFileName = (char *) malloc(LINE);
    char *tableDate = (char *) malloc(LINE);
    memset(configFileName, 0, LINE);
    memset(outFileName, 0, LINE);
    memset(tableDate, 0, LINE);

    if (argc > 1) {
        int i = 0;
        for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-configfile") == 0 || strcmp(argv[i], "-f") == 0) {
                if (i + 1 >= argc || strlen(argv[i + 1]) == 0) {
                    printf("-configfile must follow file name\n");
                    return 0;
                }
                sprintf(configFileName, "%s", argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-fNumber") == 0 || strcmp(argv[i], "-fn") == 0) {
                if (i + 1 >= argc || strlen(argv[i + 1]) == 0) {
                    printf("-fNumber must follow number\n");
                    return 0;
                }
                fileNumber = atoi(argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-tNumber") == 0 || strcmp(argv[i], "-tn") == 0) {
                if (i + 1 >= argc || strlen(argv[i + 1]) == 0) {
                    printf("-tNumber must follow number\n");
                    return 0;
                }
                tableNumber = atoi(argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-create") == 0 || strcmp(argv[i], "-c") == 0) {
                if (i + 1 >= argc || strlen(argv[i + 1]) == 0) {
                    printf("-create must follow date \"YYYY-MM-dd\"\n");
                    return 0;
                }
                sprintf(tableDate, "%s", argv[i + 1]);
                flag = CREATE_TABLE;
                i++;
            } else if (strcmp(argv[i], "-delete") == 0 || strcmp(argv[i], "-d") == 0) {
                if (i + 1 >= argc || strlen(argv[i + 1]) == 0) {
                    printf("-delete must follow date \"YYYY-MM-dd\"\n");
                    return 0;
                }
                sprintf(tableDate, "%s", argv[i + 1]);
                flag = DELETE_TABLE;
                i++;
            } else if (strcmp(argv[i], "-outfile") == 0 || strcmp(argv[i], "-o") == 0) {
                if (i + 1 >= argc || strlen(argv[i + 1]) == 0) {
                    printf("-outfile must follow outfile name\n");
                    return 0;
                }
                sprintf(outFileName, "%s", argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "-h") == 0) {
                showHelp();
                return 0;
            }
        }

        createMain(flag, configFileName, outFileName, tableDate);
    }else{
        showHelp();
    }
    
    free(outFileName);
    free(configFileName);
    free(tableDate);
    return 0;
}

