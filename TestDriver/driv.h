#pragma once

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sqlucode.h>

//#include <msdasql.h>

//#include <msdadc.h>

//#include <odbcinst.h>

struct ENV {
	int temp;
} ;


struct DBC {
	ENV* env;
	void* handle;
	int temp;
	SQLCHAR* serverName;
	SQLSMALLINT serverLength;
	SQLCHAR* userName;
	SQLSMALLINT userLength;
	SQLCHAR* auth;
	SQLSMALLINT authLength;
} ;


struct STMT{
	DBC* dbc;
	int temp;
	int argc; //the number of columns in the result
	char** argv; //an array of pointers to strings obtained
	char** colName; // an array of pointers to strings where each entry represents the name of corresponding result column as obtained
} ;
