#pragma once
#include "driv.h"
#include "sqlite64/sqlite3.h"
#include <iostream>

SQLRETURN SQL_API connect(SQLHENV EnvironmentHandle, _Out_ SQLHDBC* ConnectionHandle);
SQLRETURN SQL_API disconnect(SQLHDBC ConnectionHandle);
SQLRETURN execute(STMT stmt, char* StatementText);