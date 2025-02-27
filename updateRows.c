#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   fprintf( stderr, "%s: ", (const char*)data );
   
   for( i = 0; i < argc; i++ ) {
      printf( "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL" );
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
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open(dbname, &db);
    
    if( rc ) {
        fprintf( stderr, "Can't open database: %s\n", sqlite3_errmsg(db) );
        return(0);
    } else {
        fprintf( stderr, "Opened database successfully\n" );
    }

    /* Create merged SQL statement */
    sql = "UPDATE PROCESSDATA set PROCNAME='mqtt' where PORT=1883;" \
            "SELECT * from PROCESSDATA";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    return 0;
}
