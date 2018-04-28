/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifdef _WIN32

#include <windows.h>
#include "main.h"
#include <malloc.h>

#define ALLOC_WIDE(src, len) src == NULL ? NULL : alloca (2 * (len == SQL_NTS ? strlen(src)+1 : len + 1) )

SQLRETURN SQL_API SQLDriverConnect(SQLHDBC hDbc,SQLHWND hWnd,SQLCHAR* pStmt,
        SQLSMALLINT wStmt, SQLCHAR* pOut, SQLSMALLINT wOut, SQLSMALLINT* wOutLen, SQLUSMALLINT wPrompt)

{
    SQLWCHAR *pwStmt = ALLOC_WIDE(pStmt, wStmt);
    SQLWCHAR *pwOut = ALLOC_WIDE(pOut, wOut);
    
    if ( pwStmt ) {
        MultiByteToWideChar(CP_UTF8, 0, pStmt, wStmt == SQL_NTS?-1:wStmt, 
                pwStmt, wStmt == SQL_NTS?strlen(pStmt)+1:wStmt);
    }
    
    SQLRETURN result = SQLDriverConnectW(hDbc, hWnd, pwStmt, wStmt, pwOut, wOut, wOutLen, wPrompt);
    
    if ( pwOut ) {
        WideCharToMultiByte(CP_UTF8, 0, pwOut, (*wOutLen)+1, pOut, (*wOutLen)+1, NULL, NULL);
    }
    
    return result;
}

SQLRETURN SQL_API SQLExecDirect(SQLHSTMT hStmt, SQLCHAR* pStmt, SQLINTEGER wStmt)

{
    SQLWCHAR *pwStmt = ALLOC_WIDE(pStmt, wStmt);
    
    if ( pwStmt ) {
        MultiByteToWideChar(CP_UTF8, 0, pStmt, wStmt==SQL_NTS?-1:wStmt, 
                pwStmt, wStmt == SQL_NTS?strlen(pStmt)+1:wStmt);
    }
    
    return SQLExecDirectW(hStmt, pwStmt, wStmt);
}

SQLRETURN SQL_API SQLError(SQLHENV hEnv, SQLHDBC hDbc, SQLHSTMT hStmt,
        SQLCHAR* pState, SQLINTEGER* pError,SQLCHAR *pMessage,
        SQLSMALLINT wMesgBufLen, SQLSMALLINT *wMesgLen)

{
    SQLWCHAR wState[6];
    SQLWCHAR *pwMessage = ALLOC_WIDE(pMessage, wMesgBufLen);
    SQLRETURN result = SQLErrorW(hEnv, hDbc, hStmt, wState, pError, pwMessage, wMesgBufLen, wMesgLen);
    if ( pwMessage ) {
        WideCharToMultiByte(CP_UTF8, 0, pwMessage, *wMesgLen, pMessage, *wMesgLen, NULL, NULL);
    }
    WideCharToMultiByte(CP_UTF8, 0, wState, sizeof(wState), pState, sizeof(wState), NULL, NULL);
    return result;
}

#endif
