
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MPSKTURBO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MPSKTURBO_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MPSKTURBO_EXPORTS
#define MPSKTURBO_API __declspec(dllexport)
#else
#define MPSKTURBO_API __declspec(dllimport)
#endif

// This class is exported from the MPSKTurbo.dll
class MPSKTURBO_API CMPSKTurbo {
public:
	CMPSKTurbo(void);
	// TODO: add your methods here.
	TurboCodeQPSK(int *input,int *output);
	TurboCode8PSK(int *input,int *output);

};

extern MPSKTURBO_API int nMPSKTurbo;

MPSKTURBO_API int fnMPSKTurbo(void);

