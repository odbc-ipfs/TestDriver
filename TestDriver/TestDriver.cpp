// TestDriver.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "TestDriver.h"


// This is an example of an exported variable
TESTDRIVER_API int nTestDriver=0;

// This is an example of an exported function.
TESTDRIVER_API int fnTestDriver(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CTestDriver::CTestDriver()
{
    return;
}
