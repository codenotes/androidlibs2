/*******************************************************************************
 MathExt.h : Provides extensions to the math libraries available in C++.

 Created by Craig Neely, 2012

 ===============================================================================
 Copyright (c) 2012, Centeye, Inc.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of Centeye, Inc. nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL CENTEYE, INC. BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef	MATH_EXT_H
#define	MATH_EXT_H

#include "math.h"
#include "float.h"


/*******************************************************************************
Constants
*******************************************************************************/
// geometry
#define	MATHEXT_PI_DIV4			(float)0.78539816339745		// PI/4
#define	MATHEXT_PI_DIV2			(float)1.5707963267949		// PI/2
#define	MATHEXT_PI				(float)3.1415926535898		// PI
#define	MATHEXT_3PI_DIV2		(float)4.7123889803847		// (3*PI)/2
#define	MATHEXT_2PI				(float)6.2831853071796		// 2*PI
#define	MATHEXT_RAD_CONV		(float)0.0174532925199		// conversion to radians (pi/180)
#define	MATHEXT_DEG_CONV		(float)57.295779513082		// conversion to degrees (180/pi)

// sorting
#define	MATHEXT_SORT_ASCEND		0							// sort ascending
#define	MATHEXT_SORT_DESCEND	1							// sort descending


/******************************************************************************/
class MathExt
/******************************************************************************/
{
// constructor / destructor
public:
	MathExt(void);
	~MathExt(void);

// class support functions
public:
	// rounding
	int				Floor(float In);
	int				Ceil(float In);

	// modulus
	float			Mod(float X, float Y);

	// sign
	int				AbsInt(int Val);

	// vector operations
	float			GetVecAngle(float X, float Y);
	float			CompareAngles(float Theta1, float Theta2, float Thresh, unsigned char Units,
								unsigned char Type, unsigned char *pAlign);

	// factorial
	double			Factorial(unsigned int N);

	// bounds
	template <typename TData> TData	Clip(TData Val, TData Min, TData Max, unsigned char *pOOB);

	// averaging
	float			RunAvg(float Val, float Avg, float Rate);
	void			RunAvgArray(unsigned int *pSumA, unsigned int *pCountA, int *pRA, unsigned int Size,
								int BoostVal, int Rate, unsigned char Init);
	void			AvgArray(unsigned int *pSumA, unsigned int *pCountA, int *pAvg, unsigned int Size);
	template <typename TData> float	GetAvg(TData *pA, unsigned int Size);

	// checksums
	unsigned char	ComputeMSChecksum(unsigned char *Data, unsigned int Size);
	bool			ValidateMSChecksum(unsigned char *Data, unsigned int Size, unsigned char Checksum);
};


/*******************************************************************************
Clip
Constrains a variable to a set range.

Input:	Val:		value to be clipped
	Min:		minimum acceptable value (inclusive)
	Max:		maximum acceptable value (inclusive)
	pOOB:		pointer to an out-of-bounds flag to be filled
Return:	clipped value
*******************************************************************************/
template <typename TData>
TData MathExt::Clip(TData Val, TData Min, TData Max, unsigned char *pOOB)
/******************************************************************************/
{
	// clip value against allowable bounds
	// too low
	if (Val < Min)
	{
		if (pOOB)
			*pOOB = 1;
		return (Min);
	}
	// too high
	else if (Val > Max)
	{
		if (pOOB)
			*pOOB = 1;
		return (Max);
	}
	// in bounds
	else
	{
		if (pOOB)
			*pOOB = 0;
		return (Val);
	}
}


/*******************************************************************************
GetAvg
Returns the average value of an array.

Input:	pA:		array to be averaged
	Size:		size of the input array
Return:	average value
*******************************************************************************/
template <typename TData>
float MathExt::GetAvg(TData *pA, unsigned int Size)
/******************************************************************************/
{
	float		Sum = 0;		// summation of array values


	// sum and return average
	for (unsigned int i = 0; i < Size; i++)
		Sum += pA[i];
	return (Sum / (float)Size);
}


#endif	// MATH_EXT_H
