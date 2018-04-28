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
#define NAME_LEN 20
#define BDAY_LEN 12

SQLHENV env = {0};
SQLHDBC dbc = {0};
SQLHSTMT stmt = {0};
SQLHSTMT stmt2 = {0};
SQLCHAR vorname[VNAME_LEN];
SQLCHAR vornameAlt[VNAME_LEN];
SQLCHAR name[NAME_LEN];
SQLCHAR nameAlt[NAME_LEN];
SQLCHAR bday[BDAY_LEN];
SQLLEN cbVorname = SQL_NTS, cbName = SQL_NTS, cbBday = SQL_NTS, cbVornameAlt = SQL_NTS, cbNameAlt = SQL_NTS;


void CheckResult(const char *, SQLRETURN);

/*
 * 
 */
int main(int argc, char *argv[]) {

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
    if (strcmp(argv[1], "admin") == 0) {
        SQLExecDirect(stmt, argv[2], SQL_NTS);
    }
    if (strcmp(argv[1], "create") == 0) {
        strcpy(name, argv[2]);
        strcpy(vorname, argv[3]);
        strcpy(bday, argv[4]);
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, NAME_LEN, 0, name, 255, &cbName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vorname, 255, &cbVorname);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, BDAY_LEN, 0, bday, 255, &cbBday);
        SQLPrepare(stmt, (SQLCHAR*) "INSERT INTO Tperson(Cfname, Cvname, Cbirthday) Values(?, ?, ?)", SQL_NTS);
        SQLExecute(stmt);
    }
    if (strcmp(argv[1], "delete") == 0) {
        strcpy(name, argv[2]);
        strcpy(vorname, argv[3]);
        int i = 0;
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, NAME_LEN, 0, name, 255, &cbName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vorname, 255, &cbVorname);
        SQLExecDirect(stmt, "SELECT * FROM Tperson WHERE Cfname = ? AND Cvname = ?", SQL_NTS); //("SELECT * FROM Tperson WHERE Cfname = '%s' AND Cvname = '%s'",name,vorname)
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            i++;
        }
        printf("%d gelöscht\n", i);
        SQLCancel(stmt);
        CheckResult("AllocHandle",
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt));

        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, NAME_LEN, 0, name, 255, &cbName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vorname, 255, &cbVorname);
        SQLPrepare(stmt, (SQLCHAR*) "DELETE FROM tPerson WHERE Cfname = ? AND Cvname = ?", SQL_NTS);
        SQLExecute(stmt);
    }
    if (strcmp(argv[1], "update") == 0) {
        strcpy(nameAlt, argv[2]);
        strcpy(vornameAlt, argv[3]);
        strcpy(name, argv[4]);
        strcpy(vorname, argv[5]);
        strcpy(bday, argv[6]);

        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, NAME_LEN, 0, name, 255, &cbName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vorname, 255, &cbVorname);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, BDAY_LEN, 0, bday, 255, &cbBday);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, NAME_LEN, 0, nameAlt, 255, &cbNameAlt);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vornameAlt, 255, &cbVornameAlt);


        SQLPrepare(stmt, (SQLCHAR*) "UPDATE Tperson SET Cfname = ?, Cvname = ?, Cbirthday = ? WHERE Cfname = ? AND Cvname = ?", SQL_NTS);
        SQLExecute(stmt);

        int i = 0;
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, NAME_LEN, 0, name, 255, &cbName);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, VNAME_LEN, 0, vorname, 255, &cbVorname);


        SQLExecDirect(stmt, "SELECT * FROM Tperson WHERE Cfname = ? AND Cvname = ?", SQL_NTS);
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            i++;
        }
        printf("%d\n", i);
    }
    if (strcmp(argv[1], "read") == 0) {
        SQLBindCol(stmt, 1, SQL_C_CHAR, name, NAME_LEN, &cbName);
        SQLBindCol(stmt, 2, SQL_C_CHAR, vorname, VNAME_LEN, &cbVorname);
        SQLBindCol(stmt, 3, SQL_C_CHAR, bday, BDAY_LEN, &cbBday);

        SQLExecDirect(stmt, "SELECT * FROM Tperson", SQL_NTS);
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            printf("%s %s %s \n", name, vorname, bday);
        }

    }

    return (EXIT_SUCCESS);
}

void CheckResult(const char *fct, SQLRETURN result) {
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
