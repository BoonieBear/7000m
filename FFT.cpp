/**********************************************************************
  FFT.cpp 

  Dominic Mazzoni 
  
  This file contains a few FFT routines, including a real-FFT
  routine that is almost twice as fast as a normal complex FFT, 
  and a power spectrum routine when you know you don't care 
  about phase information. 
  The basic algorithm for his code was based on Numerican Recipes 
  in Fortran.  I optimized his code further by reducing array 
  accesses, caching the bit reversal table, and eliminating 
  double-to-double conversions, and I added the routines to
  calculate a real FFT and a real power spectrum. 
**********************************************************************/ 
#include "stdafx.h"
#include <stdlib.h> 
#include <math.h> 
#include "FFT.h"

//int **gFFTBitTable = NULL;
const int MaxFastBits = 16;
int  gFFTBitTable[MaxFastBits][2];

int IsPowerOfTwo(int x) 
{ 

   if (x < 2) 
	  return false;
   if (x & (x - 1))          /*Thanks to 'byang' for this cute trick! */ 
      return false; 
   return true;
} 

//FFT size 
int NumberOfBitsNeeded(int PowerOfTwo)
{ 

   int i; 
   if (PowerOfTwo < 2) 
   { 
      fprintf(stderr, "Error: FFT called with size %d\n", PowerOfTwo); 
      exit(1); 
   } 

   for (i = 0;; i++) 
   {
	  if (PowerOfTwo & (1 << i))  return i;
	  // get the log2(x), 
	  // but it isn't strong enough to avoid the deadth loop possible. 
   }
}

int ReverseBits(int index, int NumBits) 
{ 
	//index = 110 and Numbits =3 ===> rev = 011
   int i, rev; 
   for (i = rev = 0; i < NumBits; i++) 
   { 
	  rev = (rev << 1) | (index & 1);
      index >>= 1; 
   } 

   return rev; 
} 
void InitFFT() 
{
   int len = 2;
   for (int b = 1; b <= MaxFastBits; b++)
   {
	   for (int i = 0; i < len; i++)
	     gFFTBitTable[b - 1][i] = ReverseBits(i, b); 
      len <<= 1; 
   } 
} 

inline int FastReverseBits(int i, int NumBits)
{ 
//   if (NumBits <= MaxFastBits)
//	  return gFFTBitTable[NumBits - 1][i];
//   else
	  return ReverseBits(i, NumBits);
} 

/*  * Complex Fast Fourier Transform  */ 
void FFT(int NumSamples, 
         bool InverseTransform, 
         double *RealIn, double *ImagIn, double *RealOut, double *ImagOut) 
{ 

	if(RealIn==NULL || RealOut==NULL || ImagOut==NULL) return;
   int NumBits;                 /* Number of bits needed to store indices */ 
   int i, j, k, n;
   int BlockSize, BlockEnd; 

   double angle_numerator = 2.0 * M_PI; 
   double tr, ti;                /* temp real, temp imaginary */ 
  
   if (!IsPowerOfTwo(NumSamples)) 
   { 
      fprintf(stderr, "%d is not a power of two\n", NumSamples); 
      exit(1); 
   } 


   if (!gFFTBitTable)
      InitFFT();
   if (InverseTransform) 
      angle_numerator = -angle_numerator; 
   NumBits = NumberOfBitsNeeded(NumSamples); 
   /* 
    **   Do simultaneous data copy and bit-reversal ordering into outputs... 
    */ 
   for (i = 0; i < NumSamples; i++) 
   { 
      j = FastReverseBits(i, NumBits); 
	  RealOut[j] = RealIn[i];
	  ImagOut[j] = (ImagIn == NULL) ? 0.0 : ImagIn[i];
   }

   /*     **   Do the FFT itself...     */
   BlockEnd = 1;
   for (BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1)
   {

	  double delta_angle = angle_numerator / (double) BlockSize;
	  double wr = cos(-delta_angle);
	  double wi = sin(-delta_angle);
	  double ar0, ar1, ai0, ai1;

	  for (i = 0; i < NumSamples; i += BlockSize)
	  {
		  ar0 = 1;		  ai0 = 0;
		  ar1 = 1;        ai1 = 0;
		 for (j = i, n = 0; n < BlockEnd; j++, n++)
		 {
			k = j + BlockEnd;
			tr = ar0 * RealOut[k] - ai0 * ImagOut[k];
			ti = ar0 * ImagOut[k] + ai0 * RealOut[k];

			RealOut[k] = RealOut[j] - tr;
			ImagOut[k] = ImagOut[j] - ti;

			RealOut[j] = RealOut[j]+ tr;
			ImagOut[j] = ImagOut[j]+ ti;

			ar0 = wr*ar1 - wi*ai1;
			ai0 = wr*ai1 + wi*ar1;
			ar1 = ar0;
			ai1 = ai0;

		 }
	  }

	  BlockEnd = BlockSize;
   }

   /*
      **   Need to normalize if inverse transform... 
    */ 
  
   if (InverseTransform) 
   { 
      double denom = (double) NumSamples; 
  
      for (i = 0; i < NumSamples; i++) 
	  { 
         RealOut[i] /= denom; 
         ImagOut[i] /= denom; 
      } 
   } 
} 
  
/* 
 * Real Fast Fourier Transform 
 * 
 * This function was based on the code in Numerical Recipes in C. 
 * In Num. Rec., the inner loop is based on a single 1-based array 
 * of interleaved real and imaginary numbers.  Because we have two 
 * separate zero-based arrays, our indices are quite different. 
 * Here is the correspondence between Num. Rec. indices and our indices: 
 * 
 * i1  <->  real[i] 
 * i2  <->  imag[i] 
 * i3  <->  real[n/2-i] 
 * i4  <->  imag[n/2-i] 
 */ 
  
void RealFFT(int NumSamples, double *RealIn, double *RealOut, double *ImagOut) 
{ 
	int Half = NumSamples / 2; 
	int i; 
	
	double theta = M_PI / Half; 
	
	double *tmpReal = new double[Half]; 
	double *tmpImag = new double[Half]; 
	
	for (i = 0; i < Half; i++) { 
		tmpReal[i] = RealIn[2 * i]; 
		tmpImag[i] = RealIn[2 * i + 1]; 
	} 
	
	FFT(Half, false, tmpReal, tmpImag, RealOut, ImagOut); 
	
	double wtemp = double (sin(0.5 * theta)); 
	
	double wpr = -2.0 * wtemp * wtemp; 
	double wpi = double (sin(theta)); 
	double wr = 1.0 + wpr; //cos(theta)
	double wi = wpi;	   //sin(theta)
	
	int i3; 
	
	RealOut[Half] = RealOut[0] - ImagOut[0]; 
	RealOut[0] = RealOut[0] + ImagOut[0]; 
	ImagOut[0] = 0;
	ImagOut[Half] = 0; 
	
	double h1r, h1i, h2r, h2i; 
	//half array X1 real, image
	//half array X2 real, image
	for (i = 1; i < Half/2+1; i++) 
	{ 
		
		i3 = Half - i; //  (N/2 - k)
		h1r =  0.5 * (RealOut[i] + RealOut[i3]); 
		h1i =  0.5 * (ImagOut[i] - ImagOut[i3]); 
		h2r = 0.5 * (ImagOut[i3] + ImagOut[i]); 
		h2i = 0.5 * (RealOut[i3] - RealOut[i]); 
		
		RealOut[i]  =  -1*(h1i + wr * h2i + wi * h2r); 
		ImagOut[i]  =  -1*(h1r + wr * h2r - wi * h2i); 
		RealOut[i3] = -h1i + wr * h2i + wi * h2r; 
		ImagOut[i3] =  h1r - wr * h2r + wi * h2i; 
		
		wr = (wtemp = wr) * wpr - wi * wpi + wr; 
		wi = wi * wpr + wtemp * wpi + wi; 
		
		if(i%2==0) ImagOut[i]*=-1;
		RealOut[NumSamples-i]  =  RealOut[i]; 
		ImagOut[NumSamples-i]  =  -ImagOut[i]; 
		RealOut[NumSamples-i3]  =  RealOut[i3]; 
		ImagOut[NumSamples-i3]  =  -ImagOut[i3]; 
	} 
	delete[]tmpReal; 
	delete[]tmpImag; 
} 

/* 
 * PowerSpectrum 
 * 
 * This function computes the same as RealFFT, above, but 
 * adds the squares of the real and imaginary part of each 
 * coefficient, extracting the power and throwing away the 
 * phase. 
 * 
 * For speed, it does not call RealFFT, but duplicates some 
 * of its code. 
 */ 
  
void PowerSpectrum(int NumSamples, double *In, double *Out) 
{ 
   int Half = NumSamples / 2; 
   int i; 
  
   double theta = M_PI / Half; 
  
   double *tmpReal = new double[Half]; 
   double *tmpImag = new double[Half]; 
   double *RealOut = new double[Half]; 
   double *ImagOut = new double[Half]; 
  
   for (i = 0; i < Half; i++) 
   { 
      tmpReal[i] = In[2 * i]; 
      tmpImag[i] = In[2 * i + 1]; 
   } 

  
   FFT(Half, 0, tmpReal, tmpImag, RealOut, ImagOut); 
  
   double wtemp = double (sin(0.5 * theta)); 
  
   double wpr = -2.0 * wtemp * wtemp; 
   double wpi = double (sin(theta)); 
   double wr = 1.0 + wpr; 
   double wi = wpi; 
  
   int i3; 
  
   double h1r, h1i, h2r, h2i, rt, it; 
  
   for (i = 1; i < Half / 2; i++) 
   { 
	   i3 = Half - i; 
	   h1r = 0.5 * (RealOut[i] + RealOut[i3]); 
	   h1i = 0.5 * (ImagOut[i] - ImagOut[i3]); 
	   h2r = 0.5 * (ImagOut[i] + ImagOut[i3]); 
	   h2i = -0.5 * (RealOut[i] - RealOut[i3]); 
	   
	   rt = h1r + wr * h2r - wi * h2i; 
	   it = h1i + wr * h2i + wi * h2r; 
	   
	   Out[i] = rt * rt + it * it; 
	   
	   rt = h1r - wr * h2r + wi * h2i; 
	   it = -h1i + wr * h2i + wi * h2r; 
	   
	   Out[i3] = rt * rt + it * it; 
	   
	   wr = (wtemp = wr) * wpr - wi * wpi + wr; 
	   wi = wi * wpr + wtemp * wpi + wi; 
   } 
  
   rt = (h1r = RealOut[0]) + ImagOut[0]; 
   it = h1r - ImagOut[0]; 
   Out[0] = rt * rt + it * it; 
  
   rt = RealOut[Half / 2]; 
   it = ImagOut[Half / 2]; 
   Out[Half / 2] = rt * rt + it * it; 
  
   delete[]tmpReal; 
   delete[]tmpImag; 
   delete[]RealOut; 
   delete[]ImagOut; 
} 
long nextPow2(long inputN)
{
	long result=0;
	if(inputN<=0) return 0;
	result=(long)(log((double)(inputN+0.5))/log(2));
	return (long)(pow(2,result));
}

void FIR(double *pIn,int length,double *pFilter,int lenFilter,double *pOut)
{
	double *pTemp=new double[length+lenFilter-1];
	memcpy(pTemp+lenFilter-1,pIn,(length)*sizeof(double));
	memset(pTemp,0,(lenFilter-1)*sizeof(double));
	pIn = pTemp;
	
	double sum=0;
	for(int i=lenFilter-1;i<length+lenFilter-1;i++)
	{
		sum=0;
		for(int j=0;j<lenFilter;j++)
		{
			sum+=pIn[i-j]*pFilter[j]; 
		}
		pOut[i-lenFilter+1]=sum; 
	}
	delete[] pTemp;
}


double getMeanAbs(double *pIn,int length)
{
	if(length<=0) return 0;
	if(pIn==NULL) return 0;
	double res=0;
	for(int i=0;i<length;i++)
	{
		res += fabs(pIn[i]);
	}
	res /= length;
	return res;
}

double Getstd(double*pIn,int length,double *pmean)
{
	double mean=0,res=0;
	for(int i=0;i<length;i++)	mean += pIn[i];
	mean = mean/length;
	*pmean = mean;
	for (i=0;i<length;i++) 
	{
		res+=(pIn[i]-mean)*(pIn[i]-mean);
	}
	if(length>1)
	{
		res = sqrt(res/(length-1));
	}
	else
	{
		res = sqrt(res);
	}

	return res;
}
double FindMax(double *pIn,int Length,int *MaxIndex)
{
	if(pIn==NULL||Length<=0) return 0; 
	double maxValue=0;
	for(int i=0;i<Length;i++)
	{
		if(maxValue<pIn[i]){
			maxValue=pIn[i];
			if(MaxIndex) *MaxIndex = i;
		}
	}
	return maxValue;
}
double Pow10(int index)
{
	double res=1;
	int i;
	if(index==0) return 1;
	if(index>0)
	{
		for(i=0;i<index;i++)
		{
			res*=10;
		}
	}
	return res;
}