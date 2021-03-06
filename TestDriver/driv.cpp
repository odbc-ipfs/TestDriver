#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "driv.h"
#include <wchar.h>
//"C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\um\odbcinst.h"

SQLRETURN SQL_API SQLAllocHandle(SQLSMALLINT HandleType,
    SQLHANDLE InputHandle, _Out_ SQLHANDLE* OutputHandle) {

    OutputDebugString(L"SQLAllocHandle called\n"); 

    SQLRETURN error = SQL_ERROR;
    
    wchar_t buff[40];
    ENV* env;
    DBC* dbc;

    switch (HandleType) {
    case SQL_HANDLE_ENV:
        error = SQLAllocEnv(OutputHandle);

        
        env = (ENV*) *OutputHandle;
        wsprintf(buff, L"env->temp: %d\n", env->temp);
        OutputDebugString(buff);

        break;
    case SQL_HANDLE_DBC:
        error = SQLAllocConnect(InputHandle, OutputHandle);

        env = (ENV*)InputHandle;
        wsprintf(buff, L"env->temp: %d\n", env->temp);
        OutputDebugString(buff);

        dbc = (DBC*)*OutputHandle;
        wsprintf(buff, L"dbc->temp: %d\n", dbc->temp);
        OutputDebugString(buff);

        break;
    case SQL_HANDLE_STMT:
        error = SQLAllocStmt(InputHandle, OutputHandle);
        break;
                
    default:
        *OutputHandle = SQL_NULL_HANDLE;
        break;
    }

    if (error != SQL_SUCCESS) {
        OutputDebugString(L"SQLAllocHandle END FAILURE\n");

    }



    return error;

}

/*
allocates ConnectionHandle and links EnvironmentHandle to it then replaces the input pointer to the allocated pointer*/
SQLRETURN SQL_API SQLAllocConnect(SQLHENV EnvironmentHandle, _Out_ SQLHDBC *ConnectionHandle) {

    OutputDebugString(L"SQLAllocConnect called\n");
    
    *ConnectionHandle = SQL_NULL_HDBC;

    DBC* dbc;
    ENV* env;

    if (EnvironmentHandle == NULL) {
        return SQL_INVALID_HANDLE;
    }


    env = (ENV*) EnvironmentHandle;
    dbc = new DBC();

    if (dbc == NULL) {
        OutputDebugString(L"SQLAllocConnect ERROR: dbc == NULL\n");
        *ConnectionHandle = SQL_NULL_HDBC;
        return SQL_ERROR;
    }

    dbc->env = env;
    dbc->temp = 456;
    
    *ConnectionHandle = (SQLHDBC) dbc;
    
    OutputDebugString(L"SQLAllocConnect END\n");


    return SQL_SUCCESS;
}

/*
allocates EnvironmentHandle and replaces input pointer to the allocated pointer*/
SQLRETURN  SQL_API SQLAllocEnv(_Out_ SQLHENV* EnvironmentHandle) {

    OutputDebugString(L"SQLAllocEnv called\n");

    *EnvironmentHandle = SQL_NULL_HENV;

    ENV* e;
    if (EnvironmentHandle == NULL) {
        return SQL_INVALID_HANDLE;
    }

    e = new ENV();
    if (e == NULL) {
        *EnvironmentHandle = SQL_NULL_HENV;
        return SQL_ERROR;
    }

    e->temp = 123;

    *EnvironmentHandle = (SQLHENV) e;

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLAllocStmt(SQLHDBC ConnectionHandle,
    _Out_ SQLHSTMT* StatementHandle) {

    OutputDebugString(L"SQLAllocStmt called\n");

    *StatementHandle = SQL_NULL_HSTMT;


    DBC* dbc;
    STMT* stmt;

    if (ConnectionHandle == NULL) {
        return SQL_INVALID_HANDLE;
    }
    if (StatementHandle == NULL) {
        return SQL_INVALID_HANDLE;
    }

    dbc = (DBC*)ConnectionHandle;

    stmt = (STMT*)malloc(sizeof(STMT));

    if (stmt == NULL) {
        *StatementHandle = SQL_NULL_HSTMT;
        return SQL_ERROR;
    }

    stmt->dbc = dbc;
    *StatementHandle = (SQLHSTMT)stmt;

    return SQL_SUCCESS;
}


SQLRETURN  SQL_API SQLFreeHandle(SQLSMALLINT HandleType, SQLHANDLE Handle) {

    OutputDebugString(L"SQLFreeHandle called\n");



    return SQL_SUCCESS;
}


SQLRETURN  SQL_API SQLFreeStmt(SQLHSTMT StatementHandle,
    SQLUSMALLINT Option) {
    
    OutputDebugString(L"SQLFreeStmt called\n");



    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLBindCol(SQLHSTMT StatementHandle,
    SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType,
    _Inout_updates_opt_(_Inexpressible_(BufferLength)) SQLPOINTER TargetValue,
    SQLLEN BufferLength, _Inout_opt_ SQLLEN* StrLen_or_Ind) {
    OutputDebugString(L"SQLBindCol called\n");
    return SQL_SUCCESS;
}

SQLRETURN SQLBindParameter(
    SQLHSTMT        StatementHandle,
    SQLUSMALLINT    ParameterNumber,
    SQLSMALLINT     InputOutputType,
    SQLSMALLINT     ValueType,
    SQLSMALLINT     ParameterType,
    SQLULEN         ColumnSize,
    SQLSMALLINT     DecimalDigits,
    SQLPOINTER      ParameterValuePtr,
    SQLLEN          BufferLength,
    SQLLEN* StrLen_or_IndPtr) {
    OutputDebugString(L"SQLBindParameter called\n");
    return SQL_SUCCESS;
}

SQLRETURN SQLNumParams(
    SQLHSTMT        StatementHandle,
    SQLSMALLINT* ParameterCountPtr) {
    OutputDebugString(L"SQLNumParams called\n");
    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLParamData(SQLHSTMT StatementHandle,
    _Out_opt_ SQLPOINTER* Value) {
    OutputDebugString(L"SQLParamData called\n");
    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLPutData(SQLHSTMT StatementHandle,
    _In_reads_(_Inexpressible_(StrLen_or_Ind)) SQLPOINTER Data, SQLLEN StrLen_or_Ind) {
    OutputDebugString(L"SQLPutData called\n");
    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLCloseCursor(SQLHSTMT StatementHandle) {
    OutputDebugString(L"SQLCloseCursor called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetCursorName(SQLHSTMT StatementHandle,
    _Out_writes_opt_(BufferLength) SQLCHAR* CursorName,
    SQLSMALLINT BufferLength,
    _Out_opt_
    SQLSMALLINT* NameLengthPtr) {
    OutputDebugString(L"SQLGetCursorName called\n");
    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSetCursorName(SQLHSTMT StatementHandle,
    _In_reads_(NameLength) SQLCHAR* CursorName,
    SQLSMALLINT NameLength) {
    OutputDebugString(L"SQLSetCursorName called\n");
    return SQL_SUCCESS;
}

SQLRETURN SQLColAttribute(
    SQLHSTMT        StatementHandle,
    SQLUSMALLINT    ColumnNumber,
    SQLUSMALLINT    FieldIdentifier,
    SQLPOINTER      CharacterAttributePtr,
    SQLSMALLINT     BufferLength,
    SQLSMALLINT* StringLengthPtr,
    SQLLEN* NumericAttributePtr) {
    OutputDebugString(L"SQLColAttribute called\n");
    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLDescribeCol(SQLHSTMT StatementHandle,
    SQLUSMALLINT ColumnNumber, _Out_writes_opt_(BufferLength) SQLCHAR* ColumnName,
    SQLSMALLINT BufferLength, _Out_opt_ SQLSMALLINT* NameLength,
    _Out_opt_ SQLSMALLINT* DataType, _Out_opt_ SQLULEN* ColumnSize,
    _Out_opt_ SQLSMALLINT* DecimalDigits, _Out_opt_ SQLSMALLINT* Nullable) {
    OutputDebugString(L"SQLDescribeCol called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLNumResultCols(SQLHSTMT StatementHandle,
    _Out_ SQLSMALLINT* ColumnCount) {
    OutputDebugString(L"SQLNumResultCols called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLRowCount(_In_ SQLHSTMT StatementHandle,
    _Out_ SQLLEN* RowCount) {
    OutputDebugString(L"SQLRowCount called\n");
    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLColumns(SQLHSTMT StatementHandle,
    _In_reads_opt_(NameLength1) SQLCHAR* CatalogName, SQLSMALLINT NameLength1,
    _In_reads_opt_(NameLength2) SQLCHAR* SchemaName, SQLSMALLINT NameLength2,
    _In_reads_opt_(NameLength3) SQLCHAR* TableName, SQLSMALLINT NameLength3,
    _In_reads_opt_(NameLength4) SQLCHAR* ColumnName, SQLSMALLINT NameLength4) {
    OutputDebugString(L"SQLColumns called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetTypeInfo(SQLHSTMT StatementHandle,
    SQLSMALLINT DataType) {
    OutputDebugString(L"SQLGetTypeInfo called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLStatistics(SQLHSTMT StatementHandle,
    _In_reads_opt_(NameLength1) SQLCHAR* CatalogName, SQLSMALLINT NameLength1,
    _In_reads_opt_(NameLength2) SQLCHAR* SchemaName, SQLSMALLINT NameLength2,
    _In_reads_opt_(NameLength3) SQLCHAR* TableName, SQLSMALLINT NameLength3,
    SQLUSMALLINT Unique, SQLUSMALLINT Reserved) {
    OutputDebugString(L"SQLStatistics called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLTables(SQLHSTMT StatementHandle,
    _In_reads_opt_(NameLength1) SQLCHAR* CatalogName, SQLSMALLINT NameLength1,
    _In_reads_opt_(NameLength2) SQLCHAR* SchemaName, SQLSMALLINT NameLength2,
    _In_reads_opt_(NameLength3) SQLCHAR* TableName, SQLSMALLINT NameLength3,
    _In_reads_opt_(NameLength4) SQLCHAR* TableType, SQLSMALLINT NameLength4) {
    OutputDebugString(L"SQLTables called\n");

    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLConnect(SQLHDBC ConnectionHandle,
    _In_reads_(NameLength1) SQLCHAR* ServerName, SQLSMALLINT NameLength1,
    _In_reads_(NameLength2) SQLCHAR* UserName, SQLSMALLINT NameLength2,
    _In_reads_(NameLength3) SQLCHAR* Authentication, SQLSMALLINT NameLength3) {

    OutputDebugString(L"SQLConnect called\n"); 

    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLConnectW(SQLHDBC             hdbc,
    _In_reads_(cchDSN) SQLWCHAR* szDSN,
    SQLSMALLINT         cchDSN,
    _In_reads_(cchUID) SQLWCHAR* szUID,
    SQLSMALLINT         cchUID,
    _In_reads_(cchAuthStr) SQLWCHAR* szAuthStr,
    SQLSMALLINT         cchAuthStr
) {
    OutputDebugString(L"SQLConnectW called\n");

    return SQL_SUCCESS;

}


SQLRETURN  SQL_API SQLDataSources(SQLHENV EnvironmentHandle,
    SQLUSMALLINT Direction, _Out_writes_opt_(BufferLength1) SQLCHAR* ServerName,
    SQLSMALLINT BufferLength1, _Out_opt_ SQLSMALLINT* NameLength1Ptr,
    _Out_writes_opt_(BufferLength2) SQLCHAR* Description, SQLSMALLINT BufferLength2,
    _Out_opt_ SQLSMALLINT* NameLength2Ptr) {

    OutputDebugString(L"SQLDataSources called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLDisconnect(SQLHDBC ConnectionHandle) {
    OutputDebugString(L"SQLDisconnect called\n");

    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDriverConnectW
(
    SQLHDBC             hdbc,
    SQLHWND             hwnd,
    _In_reads_(cchConnStrIn) SQLWCHAR* szConnStrIn,
    SQLSMALLINT         cchConnStrIn,
    _Out_writes_opt_(cchConnStrOutMax) SQLWCHAR* szConnStrOut,
    SQLSMALLINT         cchConnStrOutMax,
    _Out_opt_ SQLSMALLINT* pcchConnStrOut,
    SQLUSMALLINT        fDriverCompletion
) {
    OutputDebugString(L"SQLDriverConnect called\n");
    return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLDriverConnect(
    SQLHDBC            hdbc,
    SQLHWND            hwnd,
    _In_reads_(cchConnStrIn)
    SQLCHAR* szConnStrIn,
    SQLSMALLINT        cchConnStrIn,
    _Out_writes_opt_(cchConnStrOutMax)
    SQLCHAR* szConnStrOut,
    SQLSMALLINT        cchConnStrOutMax,
    _Out_opt_
    SQLSMALLINT* pcchConnStrOut,
    SQLUSMALLINT       fDriverCompletion) {
    OutputDebugString(L"SQLDriverConnect called\n");
    return SQL_SUCCESS;

}

SQLRETURN SQL_API SQLDriverConnectA(
    SQLHDBC         hdbc,
    SQLHWND         hwnd,
    _In_reads_(cbConnStrIn)
    SQLCHAR* szConnStrIn,
    SQLSMALLINT     cbConnStrIn,
    _Out_writes_opt_(cbConnStrOutMax)
    SQLCHAR* szConnStrOut,
    SQLSMALLINT     cbConnStrOutMax,
    _Out_opt_
    SQLSMALLINT* pcbConnStrOut,
    SQLUSMALLINT    fDriverCompletion) {
    OutputDebugString(L"SQLDriverConnectA called\n");
    return SQL_SUCCESS;

}

SQLRETURN SQL_API SQLDrivers(
    SQLHENV         EnvironmentHandle,
    SQLUSMALLINT    Direction,
    SQLCHAR* DriverDescription,
    SQLSMALLINT     BufferLength1,
    SQLSMALLINT* DescriptionLengthPtr,
    SQLCHAR* DriverAttributes,
    SQLSMALLINT     BufferLength2,
    SQLSMALLINT* AttributesLengthPtr) {

    OutputDebugString(L"SQLDrivers called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLExecDirect(SQLHSTMT StatementHandle,
    _In_reads_opt_(TextLength) SQLCHAR* StatementText,
    SQLINTEGER TextLength) {
    OutputDebugString(L"SQLExecDirect called\n");
    return SQL_SUCCESS;

}

SQLRETURN  SQL_API SQLExecute(SQLHSTMT StatementHandle) {
    OutputDebugString(L"SQLExecute called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLPrepare(SQLHSTMT StatementHandle,
    _In_reads_(TextLength) SQLCHAR* StatementText,
    SQLINTEGER TextLength) {
    OutputDebugString(L"SQLPrepare called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetData(SQLHSTMT StatementHandle,
    SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType,
    _Out_writes_opt_(_Inexpressible_(BufferLength)) SQLPOINTER TargetValue, SQLLEN BufferLength,
    _Out_opt_ SQLLEN* StrLen_or_IndPtr) {
    OutputDebugString(L"SQLGetData called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetConnectAttr(SQLHDBC ConnectionHandle,
    SQLINTEGER Attribute, _Out_writes_opt_(_Inexpressible_(BufferLength)) SQLPOINTER Value,
    SQLINTEGER BufferLength, _Out_opt_ SQLINTEGER* StringLengthPtr) {
    OutputDebugString(L"SQLGetConnectAttr called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetEnvAttr(SQLHENV EnvironmentHandle,
    SQLINTEGER Attribute, _Out_writes_(_Inexpressible_(BufferLength)) SQLPOINTER Value,
    SQLINTEGER BufferLength, _Out_opt_ SQLINTEGER* StringLength) {
    OutputDebugString(L"SQLGetEnvAttr called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetStmtAttr(SQLHSTMT StatementHandle,
    SQLINTEGER Attribute, _Out_writes_opt_(_Inexpressible_(BufferLength)) SQLPOINTER Value,
    SQLINTEGER BufferLength, _Out_opt_ SQLINTEGER* StringLength) {
    OutputDebugString(L"SQLGetStmtAttr called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSetConnectAttr(SQLHDBC ConnectionHandle,
    SQLINTEGER Attribute, _In_reads_bytes_opt_(StringLength) SQLPOINTER Value,
    SQLINTEGER StringLength) {
    OutputDebugString(L"SQLSetConnectAttr called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSetEnvAttr(SQLHENV EnvironmentHandle,
    SQLINTEGER Attribute, _In_reads_bytes_opt_(StringLength) SQLPOINTER Value,
    SQLINTEGER StringLength) {
    OutputDebugString(L"SQLSetEnvAttr called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSetStmtAttr(SQLHSTMT StatementHandle,
    SQLINTEGER Attribute, _In_reads_(_Inexpressible_(StringLength)) SQLPOINTER Value,
    SQLINTEGER StringLength) {
    OutputDebugString(L"SQLSetStmtAttr called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLCopyDesc(SQLHDESC SourceDescHandle,
    SQLHDESC TargetDescHandle) {
    OutputDebugString(L"SQLCopyDesc called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetDescField(SQLHDESC DescriptorHandle,
    SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
    _Out_writes_opt_(_Inexpressible_(BufferLength)) SQLPOINTER Value, SQLINTEGER BufferLength,
    _Out_opt_ SQLINTEGER* StringLength) {
    OutputDebugString(L"SQLGetDescField called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetDescRec(SQLHDESC DescriptorHandle,
    SQLSMALLINT RecNumber, _Out_writes_opt_(BufferLength) SQLCHAR* Name,
    SQLSMALLINT BufferLength, _Out_opt_ SQLSMALLINT* StringLengthPtr,
    _Out_opt_ SQLSMALLINT* TypePtr, _Out_opt_ SQLSMALLINT* SubTypePtr,
    _Out_opt_ SQLLEN* LengthPtr, _Out_opt_ SQLSMALLINT* PrecisionPtr,
    _Out_opt_ SQLSMALLINT* ScalePtr, _Out_opt_ SQLSMALLINT* NullablePtr) {
    OutputDebugString(L"SQLGetDescRec called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSetDescField(SQLHDESC DescriptorHandle,
    SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
    _In_reads_(_Inexpressible_(BufferLength)) SQLPOINTER Value, SQLINTEGER BufferLength) {
    OutputDebugString(L"SQLSetDescField called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSetDescRec(SQLHDESC DescriptorHandle,
    SQLSMALLINT RecNumber, SQLSMALLINT Type,
    SQLSMALLINT SubType, SQLLEN Length,
    SQLSMALLINT Precision, SQLSMALLINT Scale,
    _Inout_updates_bytes_opt_(Length) SQLPOINTER Data, _Inout_opt_ SQLLEN* StringLength,
    _Inout_opt_ SQLLEN* Indicator) {
    OutputDebugString(L"SQLSetDescRec called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetDiagField(SQLSMALLINT HandleType, SQLHANDLE Handle,
    SQLSMALLINT RecNumber, SQLSMALLINT DiagIdentifier,
    _Out_writes_opt_(_Inexpressible_(BufferLength)) SQLPOINTER DiagInfo, SQLSMALLINT BufferLength,
    _Out_opt_ SQLSMALLINT* StringLength) {
    OutputDebugString(L"SQLGetDiagField called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetDiagRec(SQLSMALLINT HandleType,
    SQLHANDLE Handle,
    SQLSMALLINT RecNumber,
    _Out_writes_opt_(6) SQLCHAR* Sqlstate,
    SQLINTEGER* NativeError,
    _Out_writes_opt_(BufferLength) SQLCHAR* MessageText,
    SQLSMALLINT BufferLength,
    _Out_opt_
    SQLSMALLINT* TextLength) {
    OutputDebugString(L"SQLGetDiagRec called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetFunctions(SQLHDBC ConnectionHandle,
    SQLUSMALLINT FunctionId,
    _Out_writes_opt_(_Inexpressible_("Buffer length pfExists points to depends on fFunction value."))
    SQLUSMALLINT* Supported) {
    OutputDebugString(L"SQLGetFunctions called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLGetInfo(SQLHDBC ConnectionHandle,
    SQLUSMALLINT InfoType, _Out_writes_bytes_opt_(BufferLength) SQLPOINTER InfoValue,
    SQLSMALLINT BufferLength, _Out_opt_ SQLSMALLINT* StringLengthPtr) {
    OutputDebugString(L"SQLGetInfo called\n");

    return SQL_SUCCESS;
}

SQLRETURN SQLNativeSql(SQLHDBC        ConnectionHandle,
    SQLCHAR* InStatementText,
    SQLINTEGER     TextLength1,
    SQLCHAR* OutStatementText,
    SQLINTEGER     BufferLength,
    SQLINTEGER* TextLength2Ptr) {
    OutputDebugString(L"SQLNativeSql called\n");

    return SQL_SUCCESS;

}

SQLRETURN  SQL_API SQLEndTran(SQLSMALLINT HandleType, SQLHANDLE Handle,
    SQLSMALLINT CompletionType) {
    OutputDebugString(L"SQLEndTran called\n");

    return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLCancel(SQLHSTMT StatementHandle) {
    OutputDebugString(L"SQLCancel called\n");

    return SQL_SUCCESS;
}

SQLRETURN  SQL_API SQLSpecialColumns(SQLHSTMT StatementHandle,
    SQLUSMALLINT IdentifierType,
    _In_reads_opt_(NameLength1) SQLCHAR* CatalogName, SQLSMALLINT NameLength1,
    _In_reads_opt_(NameLength2) SQLCHAR* SchemaName, SQLSMALLINT NameLength2,
    _In_reads_opt_(NameLength3) SQLCHAR* TableName, SQLSMALLINT NameLength3,
    SQLUSMALLINT Scope, SQLUSMALLINT Nullable) {
    OutputDebugString(L"SQLSpecialColumns called\n");

    return SQL_SUCCESS;
}




BOOL SQL_API ConfigDriver(
    HWND    hwndParent,
    WORD    fRequest,
    LPCSTR  lpszDriver,
    LPCSTR  lpszArgs,
    LPSTR   lpszMsg,
    WORD    cbMsgMax,
    WORD* pcbMsgOut) {

    OutputDebugString(L"ConfigDriver called\n"); 


    return TRUE;
}

BOOL SQL_API ConfigDSN(
    HWND     hwndParent,
    WORD     fRequest,
    LPCSTR   lpszDriver,
    LPCSTR   lpszAttributes) {
    OutputDebugString(L"ConfigDSN called\n"); 

    return TRUE;

}

BOOL SQL_API ConfigTranslator(
    HWND     hwndParent,
    DWORD* pvOption) {

    OutputDebugString(L"ConfigTranslator called\n"); 


    return TRUE;

}




