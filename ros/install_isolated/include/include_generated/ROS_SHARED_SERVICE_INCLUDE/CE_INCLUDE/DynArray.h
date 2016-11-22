/*******************************************************************************
 DynArray.h : Dynamic array management.

 Created by Craig Neely, 2013

 ===============================================================================
 Copyright (c) 2013, Centeye, Inc.
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

#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#pragma once


/*******************************************************************************
Constants
*******************************************************************************/
// array organization
#define	DYN_ARRAY_ORG_1D		0						// 1D
#define	DYN_ARRAY_ORG_2D		1						// 2D
#define	DYN_ARRAY_ORG_3D		2						// 3D


/******************************************************************************/
template <typename TData> class DynArray
/******************************************************************************/
{
// constructor / destructor
public:
	DynArray(void);
	~DynArray(void);

// class support functions
public:
	// creation / setup
	bool			Create(unsigned long Size);
	bool			Create(unsigned long Size, TData InitVal);
	bool			Create2D(unsigned int Dim1, unsigned int Dim2);
	bool			Create2D(unsigned int Dim1, unsigned int Dim2, TData InitVal);
	bool			Create3D(unsigned int Dim1, unsigned int Dim2, unsigned int Dim3);
	bool			Create3D(unsigned int Dim1, unsigned int Dim2, unsigned int Dim3, TData InitVal);
	template <typename TDataIn> bool	CreateCopy(TDataIn *pDynIn);
	bool			InitializeArray(TData InitVal);
	void			Delete(void);
	bool			IsValid(void);

	// runtime allocation
	bool			AllocateAsNeeded(unsigned long Size);

	// basic processing
	template <typename TDataOut> bool	DRC(TDataOut *OutArray, bool Invert, TDataOut MaxOut);

	// data access
	bool			Set2D(unsigned int D1Idx, unsigned int D2Idx, TData Val);
	TData			Get2D(unsigned int D1Idx, unsigned int D2Idx);

	// data import / export
	bool			Import(TData *pArray, unsigned long Size);
	template <typename TDataIn> bool	ImportChangeType(TDataIn *pArray, unsigned long Size);
	bool			Export(TData *pArray, unsigned long Size);

// class member variables
public:
	// data
	TData			*m_Array;						// managed data array

	// array dimensions
	unsigned long	m_Size;							// current array size (entries)
	unsigned long	m_ByteSize;						// allocated array size (bytes)
	unsigned int	m_Org;							// array organization type code
	unsigned int	m_Dim1;							// dimension 1 length (most significant, first indexed)
	unsigned int	m_Dim2;							// dimension 2 length (if used)
	unsigned int	m_Dim3;							// dimension 3 length (if used) (least significant, last indexed)
};


/*******************************************************************************
Constructor
*******************************************************************************/
template <typename TData>
DynArray<TData>::DynArray(void)
/******************************************************************************/
{
	// clear members
	m_Array = 0;
	m_Size = m_ByteSize = 0;
	m_Org = DYN_ARRAY_ORG_1D;
	m_Dim1 = m_Dim2 = m_Dim3 = 0;
}


/*******************************************************************************
Destructor
*******************************************************************************/
template <typename TData>
DynArray<TData>::~DynArray(void)
/******************************************************************************/
{
	// delete array
	Delete();
}


/*******************************************************************************
Create
Deletes any previous array and allocates a new one according to the input size.

Input:	Size:		size of the array (entries)
Return:	true if array allocated successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Create(unsigned long Size)
/******************************************************************************/
{
	// delete previous array
	Delete();

	// check if size is valid
	if (!(Size > 0))
		return (false);

	// allocate space
	m_Org = DYN_ARRAY_ORG_1D;
	m_Dim1 = (unsigned int)Size;
	m_Size = Size;
	m_ByteSize = m_Size * sizeof(TData);
	m_Array = new TData [m_Size];

	// report true if memory was allocated
	return (m_Array != 0);
}


/*******************************************************************************
Create
Deletes any previous array and allocates a new one according to the input size.

This variant initializes array to user-set value.

Input:	Size:		size of the array (entries)
		InitVal:	value to initialize each entry in the array to
Return:	true if array allocated successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Create(unsigned long Size, TData InitVal)
/******************************************************************************/
{
	// call base function and report any error
	if (!Create(Size))
		return (false);

	// initialize array after creation
	return (InitializeArray(InitVal));
}


/*******************************************************************************
Create2D
Deletes any previous array and allocates a new 2D array according to the input size.

Input:	Dim1:		array entries along dimension 1 (entries)
		Dim2:		array entries along dimension 2 (entries)
Return:	true if array allocated successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Create2D(unsigned int Dim1, unsigned int Dim2)
/******************************************************************************/
{
	// delete previous array
	Delete();

	// check if size is valid
	if (!(Dim1 > 0) || !(Dim2 > 0))
		return (false);

	// allocate space
	m_Org = DYN_ARRAY_ORG_2D;
	m_Dim1 = Dim1;
	m_Dim2 = Dim2;
	m_Size = m_Dim1 * m_Dim2;
	m_ByteSize = m_Size * sizeof(TData);
	m_Array = new TData [m_Size];

	// report true if memory was allocated
	return (m_Array != 0);
}


/*******************************************************************************
Create2D
Deletes any previous array and allocates a new 2D array according to the input size.

This variant initializes array to user-set value.

Input:	Dim1:		array entries along dimension 1 (entries)
		Dim2:		array entries along dimension 2 (entries)
		InitVal:	value to initialize each entry in the array to
Return:	true if array allocated successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Create2D(unsigned int Dim1, unsigned int Dim2, TData InitVal)
/******************************************************************************/
{
	// call base function and report any error
	if (!Create2D(Dim1, Dim2))
		return (false);

	// initialize array after creation
	return (InitializeArray(InitVal));
}


/*******************************************************************************
Create3D
Deletes any previous array and allocates a new 3D array according to the input size.

Input:	Dim1:		array entries along dimension 1 (entries)
		Dim2:		array entries along dimension 2 (entries)
		Dim3:		array entries along dimension 3 (entries)
Return:	true if array allocated successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Create3D(unsigned int Dim1, unsigned int Dim2, unsigned int Dim3)
/******************************************************************************/
{
	// delete previous array
	Delete();

	// check if size is valid
	if (!(Dim1 > 0) || !(Dim2 > 0) || !(Dim3 > 0))
		return (false);

	// allocate space
	m_Org = DYN_ARRAY_ORG_3D;
	m_Dim1 = Dim1;
	m_Dim2 = Dim2;
	m_Dim3 = Dim3;
	m_Size = m_Dim1 * m_Dim2 * m_Dim3;
	m_ByteSize = m_Size * sizeof(TData);
	m_Array = new TData [m_Size];

	// report true if memory was allocated
	return (m_Array != 0);
}


/*******************************************************************************
Create3D
Deletes any previous array and allocates a new 3D array according to the input size.

This variant initializes array to user-set value.

Input:	Dim1:		array entries along dimension 1 (entries)
		Dim2:		array entries along dimension 2 (entries)
		Dim3:		array entries along dimension 3 (entries)
		InitVal:	value to initialize each entry in the array to
Return:	true if array allocated successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Create3D(unsigned int Dim1, unsigned int Dim2, unsigned int Dim3, TData InitVal)
/******************************************************************************/
{
	// call base function and report any error
	if (!Create3D(Dim1, Dim2, Dim3))
		return (false);

	// initialize array after creation
	return (InitializeArray(InitVal));
}


/*******************************************************************************
CreateCopy
Creates a copy of a passed dynamic array.

Input:	pDynIn:		pointer to the array to be copied
Return:	true if array copied successfully,
		else, false
*******************************************************************************/
template <typename TData>
template <typename TDataIn> bool DynArray<TData>::CreateCopy(TDataIn *pDynIn)
/******************************************************************************/
{
	bool	CreateOK;					// created OK flag


	// exit if input array is invalid
	if (!(pDynIn->IsValid()))
		return (false);

	// check input organization code and call proper creation routine
	if (pDynIn->m_Org == DYN_ARRAY_ORG_1D)
		CreateOK = Create(pDynIn->m_Dim1);
	else if (pDynIn->m_Org == DYN_ARRAY_ORG_2D)
		CreateOK = Create2D(pDynIn->m_Dim1, pDynIn->m_Dim2);
	else if (pDynIn->m_Org == DYN_ARRAY_ORG_3D)
		CreateOK = Create3D(pDynIn->m_Dim1, pDynIn->m_Dim2, pDynIn->m_Dim3);

	// check creation
	if (!CreateOK)
		return (false);

	// copy data
	return (ImportChangeType(pDynIn->m_Array, pDynIn->m_Size));
}


/*******************************************************************************
InitializeArray
Initializes the array to a specified value.

Input:	InitVal:	value to initialize each entry in the array to
Return:	true if array initialized successfully,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::InitializeArray(TData InitVal)
/******************************************************************************/
{
	unsigned long	Idx;				// array index


	// check member array validity
	if (!IsValid())
		return (false);

	// initialize members
	for (Idx = 0; Idx < m_Size; Idx++)
		m_Array[Idx] = InitVal;

	// report success
	return (true);
}


/*******************************************************************************
Delete
Deallocates memory for the member data array and clears member variables.
*******************************************************************************/
template <typename TData>
void DynArray<TData>::Delete(void)
/******************************************************************************/
{
	// if array is allocated
	if (m_Array != 0)
	{
		// delete it
		delete [] m_Array;

		// clear members
		m_Array = 0;
		m_Size = m_ByteSize = 0;
		m_Org = DYN_ARRAY_ORG_1D;
		m_Dim1 = m_Dim2 = m_Dim3 = 0;
	}
}


/*******************************************************************************
IsValid
Reports if the member data array is valid.

Return:	true if array is valid,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::IsValid(void)
/******************************************************************************/
{
	// return array allocation status
	return ((m_Array != 0) && (m_Size > 0));
}


/*******************************************************************************
AllocateAsNeeded
Checks to see if a desired size is supported by the array. If not, it allocates
more space as needed.

Input:	Size:		size of the array needed (entries)
Return:	true if operation successful,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::AllocateAsNeeded(unsigned long Size)
/******************************************************************************/
{
	// re-create if requested size is larger than currently allocated
	if (!(IsValid()) || (Size > m_Size))
		return (Create(Size));

	// if more space is not needed, return status
	return (IsValid());
}


/*******************************************************************************
DRC
Implements dynamic range compensation on the array.

This will only work with numerical array data types.

Input:	OutArray:	pointer to output array (pass m_Array to scale this)
		Invert:		invert image values flag
		MaxOut:		maximum output value
Return:	true if operation successful,
		else, false
*******************************************************************************/
template <typename TData>
template <typename TDataOut> bool DynArray<TData>::DRC(TDataOut *OutArray, bool Invert, TDataOut MaxOut)
/******************************************************************************/
{
	TData			Min, Max;				// minimum, maximum values in the array
	unsigned long	Idx;					// array index
	TData			Range;					// range of values
	float			Scale;					// DRC scale


	// check validity
	if (!(IsValid()))
		return (false);

	// determine array statistics
	Min = Max = m_Array[0];
	for (Idx = 0; Idx < m_Size; Idx++)
	{
		// store best
		if (m_Array[Idx] < Min)
			Min = m_Array[Idx];
		if (m_Array[Idx] > Max)
			Max = m_Array[Idx];
	}

	// recalc range
	Range = Max - Min;

	// if range is non-zero, calculate scaling factor
	Scale = Range ? ((float)MaxOut / (float)Range) : 1.0;

	// scale image
	if (Invert)
		for (Idx = 0; Idx < m_Size; Idx++)
			OutArray[Idx] = (TDataOut)((float)MaxOut - (float)((float)(m_Array[Idx] - Min) * Scale));
	else
		for (Idx = 0; Idx < m_Size; Idx++)
			OutArray[Idx] = (TDataOut)((float)((float)(m_Array[Idx] - Min) * Scale));

	// return OK
	return (true);
}


/*******************************************************************************
Set2D
Sets an indexed location in the array to an input value.

Not recommended for quick access.

Input:	D1Idx:		dimension 1 index of entry to be set
		D2Idx:		dimension 2 index of entry to be set
		Val:		value to be set
Return:	true if operation successful,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Set2D(unsigned int D1Idx, unsigned int D2Idx, TData Val)
/******************************************************************************/
{
	// exit if input array is invalid
	if (!IsValid())
		return (false);

	// set array location
	m_Array[D1Idx*m_Dim2 + D2Idx] = Val;

	// return OK
	return (true);
}


/*******************************************************************************
Get2D
Returns the value of an indexed location in the array.

Not recommended for quick access.

Input:	D1Idx:		dimension 1 index of entry to be set
		D2Idx:		dimension 2 index of entry to be set
Return:	array value
*******************************************************************************/
template <typename TData>
TData DynArray<TData>::Get2D(unsigned int D1Idx, unsigned int D2Idx)
/******************************************************************************/
{
	// return array location
	return (m_Array[D1Idx*m_Dim2 + D2Idx]);
}


/*******************************************************************************
Import
Copies data from an input array location.

Input:	pArray:		pointer to the input array to be imported
		Size:		size of the input array (entries)
Return:	true if operation successful,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Import(TData *pArray, unsigned long Size)
/******************************************************************************/
{
	unsigned long	Idx;				// array index


	// validate input arguments & member array status
	if (!(IsValid() && pArray && (Size <= m_Size)))
		return (false);

	// copy array
	for (Idx = 0; Idx < m_Size; Idx++)
		m_Array[Idx] = pArray[Idx];

	// report success
	return (true);
}


/*******************************************************************************
ImportChangeType
Copies data from an input array location. Changes data type.

Input:	pArray:		pointer to the input array to be imported
		Size:		size of the input array (entries)
Return:	true if operation successful,
		else, false
*******************************************************************************/
template <typename TData>
template <typename TDataIn> bool DynArray<TData>::ImportChangeType(TDataIn *pArray, unsigned long Size)
/******************************************************************************/
{
	unsigned long	Idx;				// array index


	// validate input arguments & member array status
	if (!(IsValid() && pArray && (Size <= m_Size)))
		return (false);

	// copy array
	for (Idx = 0; Idx < m_Size; Idx++)
		m_Array[Idx] = (TData)pArray[Idx];

	// report success
	return (true);
}


/*******************************************************************************
Export
Writes data to an output array location.

Input:	pArray:		pointer to the array to output to
		Size:		size of the output array (entries)
Return:	true if operation successful,
		else, false
*******************************************************************************/
template <typename TData>
bool DynArray<TData>::Export(TData *pArray, unsigned long Size)
/******************************************************************************/
{
	unsigned long	Idx;				// array index


	// validate input arguments & member array status
	if (!(IsValid() && pArray && (Size >= m_Size)))
		return (false);

	// copy array
	for (Idx = 0; Idx < m_Size; Idx++)
		pArray[Idx] = m_Array[Idx];

	// report success
	return (true);
}

#endif	// DYN_ARRAY_H
