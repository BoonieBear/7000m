
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IMAGEPROC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IMAGEPROC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef IMAGEPROC_EXPORTS
#define IMAGEPROC_API __declspec(dllexport)
#else
#define IMAGEPROC_API __declspec(dllimport)
#endif

// This class is exported from the ImageProc.dll
class IMAGEPROC_API CImageProc {
private:
	int rack;
	unsigned char mask;
	void OutputBits(unsigned char *array, unsigned long code, int bit_count,BOOL *flag);
	unsigned long InputBits(unsigned char *array,int bit_count,BOOL *flag);
	

public:
	BOOL GrayDecode(BYTE *mybuffer, BYTE *CompressValue, int nTitle);
	BOOL GrayCode(BYTE *mybuffer, BYTE *CompressValue, int nTitle);
	BOOL ColorDecode(BYTE *mybuffer, BYTE *CompressValue, int nTitle);
	BOOL ColorCode(BYTE *mybuffer,BYTE *CompressValue,int nTitle);
	CImageProc(void);
	// TODO: add your methods here.
	
};

extern IMAGEPROC_API int nImageProc;

IMAGEPROC_API int fnImageProc(void);

