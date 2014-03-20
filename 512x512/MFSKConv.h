
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MFSKCONV_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MFSKCONV_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MFSKCONV_EXPORTS
#define MFSKCONV_API __declspec(dllexport)
#else
#define MFSKCONV_API __declspec(dllimport)
#endif

// This class is exported from the MFSKConv.dll
class MFSKCONV_API CMFSKConv {
public:
	CMFSKConv(void);
	// TODO: add your methods here.
	MFSKConv(int *input,int *output);
};

extern MFSKCONV_API int nMFSKConv;

MFSKCONV_API int fnMFSKConv(void);

