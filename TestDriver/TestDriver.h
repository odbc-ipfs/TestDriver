// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the TESTDRIVER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// TESTDRIVER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTDRIVER_EXPORTS
#define TESTDRIVER_API __declspec(dllexport)
#else
#define TESTDRIVER_API __declspec(dllimport)
#endif

// This class is exported from the dll
class TESTDRIVER_API CTestDriver {
public:
	CTestDriver(void);
	// TODO: add your methods here.
};

extern TESTDRIVER_API int nTestDriver;

TESTDRIVER_API int fnTestDriver(void);
