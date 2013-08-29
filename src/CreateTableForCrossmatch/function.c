
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "libpq-fe.h"
#include "function.h"


char *configFile = NULL;
char *host = NULL;
char *port = NULL;
char *dbname = NULL;
char *user = NULL;
char *password = NULL;
char *options = NULL;
char *tty = NULL;

/*table prefix*/
char *catfile_table = NULL;
char *match_table = NULL;
char *ot_table = NULL;
char *ot_flux_table = NULL;
/*table structure file name*/
char *catfile_table_filename = NULL;
char *match_table_filename = NULL;
char *ot_table_filename = NULL;
char *ot_flux_table_filename = NULL;

char *out_config_filename = NULL;

//for table inherit
int tableNumber = 0;
int fileNumber = 0;

void initDBInfo(){
    
    configFile = (char*)malloc(128);
    sprintf(configFile, "%s", "create_table_database_config.txt");
    host = (char*)malloc(128);
    port = (char*)malloc(128);
    dbname = (char*)malloc(128);
    user = (char*)malloc(128);
    password = (char*)malloc(128);
    options = (char*)malloc(128);
    tty = (char*)malloc(128);
    
    catfile_table = (char*)malloc(128);
    match_table = (char*)malloc(128);
    ot_table = (char*)malloc(128);
    ot_flux_table = (char*)malloc(128);
    
    catfile_table_filename = (char*)malloc(128);
    match_table_filename = (char*)malloc(128);
    ot_table_filename = (char*)malloc(128);
    ot_flux_table_filename = (char*)malloc(128);
    
    out_config_filename = (char*)malloc(128);
    sprintf(out_config_filename, "database_config.txt");
}


void freeDBInfo(){
    
    free(configFile);
    free(host);
    free(port);
    free(dbname);
    free(user);
    free(password);
    free(options);
    free(tty);
    
    free(catfile_table);
    free(match_table);
    free(ot_table);
    free(ot_flux_table);
    
    free(catfile_table_filename);
    free(match_table_filename);
    free(ot_table_filename);
    free(ot_flux_table_filename);
    
    free(out_config_filename);
}

void getDatabaseInfo(char *configFile){
    
    FILE *fp = NULL;
	char *line = NULL;
    if(strlen(configFile)==0){
        strcpy(configFile, "create_table_database_config.txt");
    }
    
	if ((fp=fopen(configFile, "r"))==NULL) {
		printf("open file %s error!\n", configFile);
		return;
	}

    initDBInfo();
    
	char *delim = "=";
	char *tmpStr = NULL;
	char *buf = (char*)malloc(LINE*sizeof(char));
	while(line=fgets(buf, LINE, fp)) {

		if((*line=='\n') || (strlen(line)==0)) continue;

		tmpStr = strtok(line, "\n");
		tmpStr = strtok(tmpStr, delim);
		if((tmpStr==NULL)||(strlen(tmpStr)==0)) continue;
        if(strcmp(tmpStr,"host")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(host, tmpStr);
            else
                strcpy(host, "localhost");
        }else if(strcmp(tmpStr,"port")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(port, tmpStr);
            else
                strcpy(port, "5432");
        }else if(strcmp(tmpStr,"dbname")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(dbname, tmpStr);
            else
                strcpy(dbname, "svomdb");
        }else if(strcmp(tmpStr,"user")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(user, tmpStr);
            else
                strcpy(user, "wanmeng");
        }else if(strcmp(tmpStr,"password")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(password, tmpStr);
            else
                strcpy(password, "");
        }else if(strcmp(tmpStr,"options")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(options, tmpStr);
            else
                strcpy(options, "");
        }else if(strcmp(tmpStr,"tty")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(tty, tmpStr);
            else
                strcpy(tty, "");
        }else if(strcmp(tmpStr,"catfile_table_prefix")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(catfile_table, tmpStr);
            else
                strcpy(catfile_table, "catfile_");
        }else if(strcmp(tmpStr,"match_table_prefix")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(match_table, tmpStr);
            else
                strcpy(match_table, "crossmatch_");
        }else if(strcmp(tmpStr,"ot_flux_table_prefix")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(ot_flux_table, tmpStr);
            else
                strcpy(ot_flux_table, "ot_flux_");
        }else if(strcmp(tmpStr,"ot_table_prefix")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(ot_table, tmpStr);
            else
                strcpy(ot_table, "ot_");
        }else if(strcmp(tmpStr,"catfile_table_filename")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(catfile_table_filename, tmpStr);
            else
                strcpy(catfile_table_filename, "table_struct/catfile.txt");
        }else if(strcmp(tmpStr,"match_table_filename")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(match_table_filename, tmpStr);
            else
                strcpy(match_table_filename, "table_struct/crossmatch.txt");
        }else if(strcmp(tmpStr,"ot_flux_table_filename")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(ot_flux_table_filename, tmpStr);
            else
                strcpy(ot_flux_table_filename, "table_struct/ot_flux.txt");
        }else if(strcmp(tmpStr,"ot_table_filename")==0){
            tmpStr = strtok(NULL, delim);
            if(tmpStr!=NULL)
                strcpy(ot_table_filename, tmpStr);
            else
                strcpy(ot_table_filename, "table_struct/ot.txt");
        }
	}
	free(buf);
	fclose(fp);
}

void getTodayDateTime(char *dateTimeStr){
    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo= localtime ( &rawtime ); 
    //"%Y%m%d%I%M%S"
    strftime (dateTimeStr,80,"%Y%m%d",timeinfo); 
}

void getTableInfo(char *fileName, char *tlbInfo){
    
    FILE *fp = NULL;
	char *line = NULL;
    if(strlen(fileName)==0){
        return;
    }
    
	if ((fp=fopen(fileName, "r"))==NULL) {
		printf("open file %s error!\n", fileName);
		return;
	}
    
	char *buf = (char*)malloc(LINE*sizeof(char));
	while(line=fgets(buf, LINE, fp)) {
        sprintf(tlbInfo, "%s%s", tlbInfo, buf);
    }
}

char * strReplace(char *src, const char *oldstr, const char *newstr) {
    char *needle;
    char *tmp;
    if (strlen(oldstr) == strlen(newstr) && strcmp(oldstr, newstr) == 0) {
        return 0;
    }

    while ((needle = strstr(src, oldstr))) {// && (needle - src <= len)
        tmp = (char*) malloc(strlen(src) + (strlen(newstr) - strlen(oldstr)) + 1);
        strncpy(tmp, src, needle - src);
        tmp[needle - src] = '\0';
        strcat(tmp, newstr);
        strcat(tmp, needle + strlen(oldstr));
        src = strdup(tmp);
        free(tmp);
    }
    return src;
}

void generateCrossMatchDBConfigFile(char *fileName, char *dateTime){
    
    FILE *fp = NULL;
    if(strlen(fileName)==0){
        return;
    }
    
	if ((fp=fopen(fileName, "w"))==NULL) {
		printf("open file %s error!\n", fileName);
		return;
	}
    //char *dateTime = (char*)malloc(128);
    //getTodayDateTime(dateTime);
    
    fprintf(fp, "host=%s\n", host);
    fprintf(fp, "port=%s\n", port);
    fprintf(fp, "dbname=%s\n", dbname);
    fprintf(fp, "user=%s\n", user);
    fprintf(fp, "password=%s\n", password);
    fprintf(fp, "catfile_table=%s%s\n", catfile_table, dateTime);
    fprintf(fp, "match_table=%s%s\n", match_table, dateTime);
    fprintf(fp, "ot_table=%s%s\n", ot_table, dateTime);
    fprintf(fp, "ot_flux_table=%s%s\n", ot_flux_table, dateTime);
    
    printf("config file \"%s\" generate success!\n\n", fileName);
    
    //free(dateTime);
    fclose(fp);
}

/**/
void createTable(char *tableFileName, char *tablePrefix, char *dateTime, int flag) {

    PGconn *conn = NULL;
    PGresult *pgrst = NULL;

    conn = PQsetdbLogin(host, port, options, tty, dbname, user, password);
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "connect db failed! %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return;
    }
    
    //char *dateTime = (char*)malloc(128);
    char *tableName = (char*)malloc(128);
    char *oldTableName = (char*)malloc(128);
    char *catfileTableName = (char*)malloc(128);
    //memset(dateTime, 0, 128);
    memset(tableName, 0, 128);
    memset(oldTableName, 0, 128);
    memset(catfileTableName, 0, 128);
    
    //getTodayDateTime(dateTime);
    sprintf(tableName, "%s%s", tablePrefix, dateTime);
    sprintf(oldTableName, "%stable", tablePrefix);
    sprintf(catfileTableName, "catfile_%s", dateTime);
    
    char *sqlBuf = (char*) malloc(MAX_BUFFER * sizeof (char));
    char *tlbInf = (char*) malloc(MAX_BUFFER * sizeof (char));
    memset(sqlBuf, 0, MAX_BUFFER * sizeof (char));
    memset(tlbInf, 0, MAX_BUFFER * sizeof (char));
    
    getTableInfo(tableFileName, tlbInf);
    tlbInf = strReplace(tlbInf, "catfile_table", catfileTableName);
    tlbInf = strReplace(tlbInf, oldTableName, tableName);
    sprintf(sqlBuf, "create table %s%s", tableName, tlbInf);
    //printf("%s\n",sqlBuf);
    
    pgrst = PQexec(conn, sqlBuf);
    
    if (PQresultStatus(pgrst) != PGRES_COMMAND_OK) {
        PQclear(pgrst);
        printf("create table %s failure!\n", tableName);
        printf("sql = %s\n", sqlBuf);
    }else{
        printf("create table %s success!\n\n",tableName);
    }
    //flag
    if(0)
    {
    strcpy(oldTableName, tableName);
    int i; //tableNumber
    for(i=0; i<tableNumber; i++){
        sprintf(tableName, "%s_%d", oldTableName, i+1);
        sprintf(sqlBuf, "create table %s(check(catid>=%d::bigint and catid<%d::bigint))inherits(%s);", 
                tableName, i*fileNumber+1, (i+1)*fileNumber+1, oldTableName);
        printf("sqlBuf=%s\n\n",sqlBuf);
        /*
        pgrst = PQexec(conn, sqlBuf);

        if (PQresultStatus(pgrst) != PGRES_COMMAND_OK) {
            PQclear(pgrst);
            printf("create table %s failure!\n", tableName);
            printf("sql = %s\n", sqlBuf);
        }else{
            printf("create table %s success!\n\n",tableName);
        }
        */
        sprintf(sqlBuf, "create rule insert_%s as "
                "on insert to %s "
                "where (catid>=%d::bigint and catid<%d::bigint) "
                "do instead "
                "insert into %s "
                "(starid, crossid, ra, dec, catid, background, "
                "classstar, ellipticity, flags, mag, mage, magnorm, "
                "fwhm, magcalib, magcalibe, pixx, pixy, thetaimage, "
                "vignet, pixx1, pixy1) values "
                "(new.starid, new.crossid, new.ra, new.dec, new.catid, new.background,"
                "new.classstar, new.ellipticity, new.flags, new.mag, new.mage, new.magnorm,"
                "new.fwhm, new.magcalib, new.magcalibe, new.pixx, new.pixy, new.thetaimage,"
                "new.vignet, new.pixx1, new.pixy1);", 
                tableName, oldTableName, i*fileNumber+1, (i+1)*fileNumber+1, tableName);
        
        printf("sqlBuf=%s\n\n",sqlBuf);
        /*
        pgrst = PQexec(conn, sqlBuf);

        if (PQresultStatus(pgrst) != PGRES_COMMAND_OK) {
            PQclear(pgrst);
            printf("create rule %s failure!\n", tableName);
            printf("sql = %s\n", sqlBuf);
        }else{
            printf("create rule %s success!\n\n",tableName);
        }*/
    }
    }
    
    //free(dateTime);
    free(tableName);
    free(oldTableName);
    free(catfileTableName);
    free(sqlBuf);
    free(tlbInf);
    PQfinish(conn);
}

void deleteTable(char *tablePrefix, char *dateTime){
    
    PGconn *conn = NULL;
    PGresult *pgrst = NULL;

    conn = PQsetdbLogin(host, port, options, tty, dbname, user, password);
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "connect db failed! %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return;
    }
    
    //char dateTime[80];
    //getTodayDateTime(dateTime);

    char *sqlBuf = (char*) malloc(MAX_BUFFER * sizeof (char));
    sprintf(sqlBuf, "drop table %s%s cascade;", tablePrefix, dateTime);
    //printf("%s\n",sqlBuf);
    pgrst = PQexec(conn, sqlBuf);
    
    if (PQresultStatus(pgrst) != PGRES_COMMAND_OK) {
        PQclear(pgrst);
        printf("delete table failure!\n");
        printf("sql = %s\n", sqlBuf);
        return;
    }else{
        printf("delete table %s%s success!\n\n",tablePrefix, dateTime);
    }
    
    free(sqlBuf);
    PQfinish(conn);
}

void createMain(int flag, char *commandConfigFile, char *outFile, char *tableDate){
    
    //char *tableFileName = "table_struct/catfile.txt";
    char dateTime[80];
    memset(dateTime, 0, 80);
    
    if(tableDate==NULL || strlen(tableDate)==0 || strcmp(tableDate,"today")==0){
        getTodayDateTime(dateTime);
    }else if(strlen(tableDate)>0){
        sprintf(dateTime, "%s", tableDate);
    }
    
    initDBInfo();
    if(commandConfigFile!=NULL && strlen(commandConfigFile)!=0)
        getDatabaseInfo(commandConfigFile);
    else{
        getDatabaseInfo(configFile);
    }
    if(flag == CREATE_TABLE){
        createTable(catfile_table_filename, catfile_table, dateTime, 0);
        createTable(match_table_filename, match_table, dateTime, 1);
        createTable(ot_table_filename, ot_table, dateTime, 0);
        createTable(ot_flux_table_filename, ot_flux_table, dateTime, 0);
        
        if (outFile != NULL && strlen(outFile) != 0)
            generateCrossMatchDBConfigFile(outFile, dateTime);
        else {
            generateCrossMatchDBConfigFile(out_config_filename, dateTime);
        }
        
    }else{
        deleteTable(match_table, dateTime);
        deleteTable(ot_table, dateTime);
        deleteTable(ot_flux_table, dateTime);
        deleteTable(catfile_table, dateTime);
    }
    freeDBInfo();
}
