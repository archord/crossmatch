/* 
 * File:   function.h
 * Author: xy
 *
 * Created on November 14, 2012, 10:24 AM
 */

#ifndef FUNCTION_H
#define	FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#define LINE 1024
#define MAX_BUFFER 2048
#define ONESECOND CLOCKS_PER_SEC
#define CREATE_TABLE 1
#define DELETE_TABLE 0

void createMain(int flag, char *commandConfigFile, char *outFile, char *tableDate);

#endif	/* FUNCTION_H */

