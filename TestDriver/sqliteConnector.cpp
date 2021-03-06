#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include "connector.h"

static int callback(void* unused, int argc, char** argv, char** colName);

//SQLHSTMT StatementHandle, SQLCHAR* StatementText, SQLINTEGER   TextLength


SQLRETURN execute(STMT stmt, char* StatementText) {

	OutputDebugString(L"connector execute\n");


	DBC* dbc = stmt.dbc;
	sqlite3* db = (sqlite3*) dbc->handle;

	char* err = 0;
	int rc;
	rc = sqlite3_exec(db, StatementText, callback, 0, &err);

	if (rc != SQLITE_OK) {
		return SQL_ERROR;
	}

	return SQL_SUCCESS;
}



static int callback(void* unused, int argc, char** argv, char** colName) {

	OutputDebugString(L"connector callback\n");


	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

SQLRETURN connect(SQLHENV EnvironmentHandle, SQLHDBC* ConnectionHandle) {

	OutputDebugString(L"connector connect\n");

	//SQLHDBC* dbc = (SQLHDBC*)calloc(1, sizeof(SQLHDBC));

	//if (dbc == NULL) return SQL_ERROR;

	DBC* dbc = (DBC*)ConnectionHandle;


	sqlite3* db;
	char* err = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);

	if (rc) {
		sqlite3_close(db);
		OutputDebugString(L"connector SQL_ERROR\n");

		return SQL_ERROR;
	}

	//*dbc = db;

	//*ConnectionHandle = &dbc;

	dbc->handle = db;
	dbc->env = (ENV*) EnvironmentHandle;

	OutputDebugString(L"connector SQL_SUCCESS\n");

	return SQL_SUCCESS;
}

SQLRETURN disconnect(SQLHDBC ConnectionHandle) {

	OutputDebugString(L"connector disconnect\n");


	DBC* dbc = (DBC*)ConnectionHandle;

	sqlite3* db = (sqlite3*)dbc->handle;

	sqlite3_close(db);

	return SQL_SUCCESS;

}