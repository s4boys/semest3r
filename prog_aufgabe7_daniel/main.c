/* 
 * File:   main.c
 * Author: Peter Heusch
 *
 * Created on 11. April 2018, 07:17
 */

#ifdef _WIN32
#include <windows.h>
#endif 

#include "main.h"
#define VNAME_LEN 10
#define FNAME_LEN 20
#define BDAY_LEN 10

SQLHENV env = {0};
SQLHDBC dbc = {0};
SQLHSTMT stmt = {0};
SQLCHAR vname[VNAME_LEN];
SQLCHAR fname[20];
SQLCHAR bday[10];
SQLLEN namelength;
SQLINTEGER cbVName = SQL_NTS, cbVName = SQL_NTS, cbBDay = 0;

void CheckResult(const char *, SQLRETURN);

/*
 * 
 */
int main(int argc, char *argv[])

{

    CheckResult("AllocHandle",
            SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env));
    CheckResult("SetEnvAttr",
            SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER));
    CheckResult("AllocHandle",
            SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc));
#ifdef _WIN32
    CheckResult("Connect",
            SQLDriverConnect(dbc, NULL, "Driver=SQLite3 ODBC Driver;Database=sample;", SQL_NTS, NULL, 0, NULL, 0));
#else
    CheckResult("Connect",
            SQLDriverConnect(dbc, NULL, "Driver=SQLITE3;Database=sample;", SQL_NTS, NULL, 0, NULL, 0));
#endif
    CheckResult("AllocHandle",
            SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt));
    if(strcmp(argv[2], "create") == 0) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vname, 255, &cbVName);
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, FNAME_LEN, 0, fname, 255, &cbFName);
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, BDAY_LEN, 0, bday, 255, &cbBDay);
        SQLPrepare(stmt, (SQLCHAR*)"INSERT INTO Tperson(Cfname, Cvname, Cbirthday) Values(?, ?, ?)", SQL_NTS);
    }
    return (EXIT_SUCCESS);
}

void CheckResult(const char *fct, SQLRETURN result)

{
    if ( result != SQL_SUCCESS && result != SQL_NO_DATA ) {
        SQLCHAR state[6];
        SQLINTEGER error;
        SQLCHAR message[128];
        SQLSMALLINT mesglen;
        printf("%s %d\n", fct, (int)result);
        SQLError(env, dbc, stmt, state, &error, message, sizeof (message), &mesglen);
        printf("%s\n", message);
        printf("%d\n", SQLFreeHandle(SQL_HANDLE_STMT, stmt));
        printf("%hd\n", SQLDisconnect(dbc));
        printf("%d\n", SQLFreeHandle(SQL_HANDLE_DBC, dbc));
        printf("%d\n", SQLFreeHandle(SQL_HANDLE_ENV, env));
        exit(1);
    }
}
