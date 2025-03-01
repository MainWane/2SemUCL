#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) 
{
    int i;
    for( i = 0; i < argc; i++ ) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main( int argc, char* argv[] ) 
{
    char *dbname = "sensordb.db"; 
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open(dbname, &db);
    
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    /* Create SQL statement */
    sql = "INSERT INTO PROCESSDATA (UNITID,PORT,PROCNAME) "  \
            "VALUES (1, 1883, 'mosquitto' ); " \
            "INSERT INTO PROCESSDATA (UNITID,PORT,PROCNAME) "  \
            "VALUES (1, 22, 'openssh' ); ";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}