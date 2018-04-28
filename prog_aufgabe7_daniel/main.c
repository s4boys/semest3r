/* 
 * File:   main.c
 * Author: Daniel Hirsch 379008
 *         Felix Schick 378732
 *
 * Created on 11. April 2018, 07:17
 */

#ifdef _WIN32
#include <windows.h>
#endif 

#include "main.h"
#define VNAME_LEN 10
#define FNAME_LEN 20
#define BDAY_LEN 12

SQLHENV env = {0};
SQLHDBC dbc = {0};
SQLHSTMT stmt = {0};
SQLCHAR vname[VNAME_LEN];
SQLCHAR fname[FNAME_LEN];
SQLCHAR bday[BDAY_LEN];
SQLLEN cbVName = SQL_NTS, cbFName = SQL_NTS, cbBDay = SQL_NTS;
SQLINTEGER rowcount;
SQLRETURN rc;


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
Test:
    if (strcmp(argv[1], "admin") == 0) {
        //Execute the given statement
        SQLExecDirect(stmt, argv[2], SQL_NTS);
    } else if (strcmp(argv[1], "create") == 0) {
        //bind parameters to variables
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, FNAME_LEN, 0, fname, 255, &cbFName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vname, 255, &cbVName);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, BDAY_LEN, 0, bday, 255, &cbBDay);
        
        //prepare statement
        SQLPrepare(stmt, (SQLCHAR*) "INSERT INTO Tperson(Cfname, Cvname, Cbirthday) Values(?, ?, ?)", SQL_NTS);
        
        //set variables from run command and run statement
        strcpy(fname, argv[2]);
        strcpy(vname, argv[3]);
        strcpy(bday, argv[4]);
        SQLExecute(stmt);
        
        //Show Test Results
        argv[1] = "read";
        goto Test;
    } else if (strcmp(argv[1], "read") == 0) {
        //Select Everything from Tperson
        SQLExecDirect(stmt, "SELECT * FROM Tperson", SQL_NTS);
        
        //binds to Resultset
        SQLBindCol(stmt, 1, SQL_C_CHAR, vname, FNAME_LEN, &cbFName);
        SQLBindCol(stmt, 2, SQL_C_CHAR, vname, VNAME_LEN, &cbVName);
        SQLBindCol(stmt, 3, SQL_C_CHAR, bday, BDAY_LEN, &cbBDay);
        
        //print
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            printf("%s %s %s\n", fname, vname, bday);
        }
    } else if (strcmp(argv[1], "update") == 0) {
        //declare new variables just for update
        SQLCHAR oldVName[VNAME_LEN];
        SQLCHAR oldFName[FNAME_LEN];
        SQLLEN cbOldVName = SQL_NTS, cbOldFName = SQL_NTS;
        
        //Bind Parameter, sorted in ascending order
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, FNAME_LEN, 0, fname, 255, &cbFName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vname, 255, &cbVName);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, BDAY_LEN, 0, bday, 255, &cbBDay);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, FNAME_LEN, 0, oldFName, 255, &cbOldFName);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, oldVName, 255, &cbOldVName);

        //Prepare Statement, define variables and Execute Statement
        SQLPrepare(stmt, (SQLCHAR*) "UPDATE Tperson SET Cfname = ?, Cvname = ?, Cbirthday = ? WHERE Cfname = ? AND Cvname = ?", SQL_NTS);
        strcpy(oldFName, argv[2]);
        strcpy(oldVName, argv[3]);
        strcpy(fname, argv[4]);
        strcpy(vname, argv[5]);
        strcpy(bday, argv[6]);
        SQLExecute(stmt);

        //Count changed rows in rowcount and print
        SQLRowCount(stmt, &rowcount);
        printf("Anzahl an geänderten Zeilen: %i\n", rowcount);
        
        //Test with output
        argv[1] = "read";
        goto Test;
    } else if (strcmp(argv[1], "delete") == 0) {
        //Bind parameter etc.
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, FNAME_LEN, 0, fname, 255, &cbFName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vname, 255, &cbVName);
        SQLPrepare(stmt, (SQLCHAR*) "DELETE FROM Tperson WHERE Cfname=? AND Cvname=?", SQL_NTS); //
        strcpy(fname, argv[2]); 
        strcpy(vname, argv[3]);
        SQLExecute(stmt);
        
        //count deleted rows and print
        SQLRowCount(stmt, &rowcount);
        printf("Anzahl an gelöschten Zeilen: %i\n", rowcount);
        argv[1] = "read";
        goto Test;
    }
    return (EXIT_SUCCESS);
}

void CheckResult(const char *fct, SQLRETURN result)
 {
    if (result != SQL_SUCCESS && result != SQL_NO_DATA) {
        SQLCHAR state[6];
        SQLINTEGER error;
        SQLCHAR message[128];
        SQLSMALLINT mesglen;
        printf("%s %d\n", fct, (int) result);
        SQLError(env, dbc, stmt, state, &error, message, sizeof (message), &mesglen);
        printf("%s\n", message);
        printf("%d\n", SQLFreeHandle(SQL_HANDLE_STMT, stmt));
        printf("%hd\n", SQLDisconnect(dbc));
        printf("%d\n", SQLFreeHandle(SQL_HANDLE_DBC, dbc));
        printf("%d\n", SQLFreeHandle(SQL_HANDLE_ENV, env));
        exit(1);
    }
}