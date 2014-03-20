
/********************************************************************** 
  FFT.h 

  Dominic Mazzoni 

  This file contains a few FFT routines, including a real-FFT 
  routine that is almost twice as fast as a normal complex FFT, 
  and a power spectrum routine which is more convenient when 
  you know you don't care about phase information.  It now also 
  contains a few basic windowing functions. 
  
  Some of this code was based on a free implementation of an FFT 
  by Don Cross, available on the web at: 
  

  The basic algorithm for his code was based on Numerical Recipes 
  in Fortran.  I optimized his code further by reducing array 
  accesses, caching the bit reversal table, and eliminating 
  double-to-double conversions, and I added the routines to 
  calculate a real FFT and a real power spectrum. 
  
**********************************************************************/ 
#include "math.h"
#ifndef M_PI 
	#define M_PI        3.14159265358979323846  /* pi */ 
#endif 
/* 
 * This is the function you will use the most often. 
 * Given an array of doubles, this will compute the power 
 * spectrum by doing a Real FFT and then computing the 
 * sum of the squares of the real and imaginary parts. 
 * Note that the output array is half the length of the 
 * input array, and that NumSamples must be a power of two. 
 */ 
  
void PowerSpectrum(int NumSamples, double *In, double *Out); 
/* 
 * Computes an FFT when the input data is real but you still 
 * want complex data as output.  The output arrays are half 
 * the length of the input, and NumSamples must be a power of 
 * two. 
 */ 

void RealFFT(int NumSamples,double *RealIn, double *RealOut, double *ImagOut); 

/* 
 * Computes a FFT of complex input and returns complex output. 
 * Currently this is the only function here that supports the 
 * inverse transform as well. 
 */ 

void FFT(int NumSamples,bool InverseTransform, 
         double *RealIn, double *ImagIn, double *RealOut, double *ImagOut); 
void FIR(double *pIn,int length,double *pFilter,int lenFilter,double *pOut);
double Pow10(int index);
long nextPow2(long inputN);
//void FIR(double *pIn,int length,double *pFilter,int lenFilter,double *pOut);
double getMeanAbs(double *pIn,int length);
double Getstd(double*pIn,int length,double *pmean);
void Convolve(double *aIn,int aN,double *bIn,int bN,double *pout);
int sign(double input);
double FindMax(double *pIn,int Length,int *MaxIndex);

