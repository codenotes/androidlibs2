/*******************************************************************************
 UARTInterface.h : Communications interface using FTDI's USB-UART bridge.

 Created by Craig Neely, 2013

 ===============================================================================
 Copyright (c) 2015, Centeye, Inc.
 All rights reserved.
 PROPRIETARY: PROVIDED UNDER NDA WITH INFUSION

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
 * Redistributions in any form must be used with hardware sold by Centeye, Inc.

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

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#pragma once

#include    <stdio.h>
#include    <stdlib.h>
//windows h was here
#include	"ftd2xx.h"
#include	"CommDefines.h"
#include	"DynArray.h"
#include	"MathExt.h"


/*******************************************************************************
Constants
*******************************************************************************/
// timing defaults
#define	UART_USB_LATENCY			4						// UART latency timer (ms)
#define	UART_FREQ_DEFAULT			5250000					// default UART bus frequency (Hz) (NOTE 7, 9, 10, 11 Mbaud not supported)
#define	UART_READ_TO_LONG			5000					// long read timeout (ms) (0 = block)
#define	UART_READ_TO_MIN			15						// minimum read timeout (ms) (0 = block)
#define	UART_WRITE_TO				5000					// write timeout (ms) (0 = block)
#define	UART_TO_FACTOR				10						// read timeout multiplication factor


/******************************************************************************/
class UARTInterface
/******************************************************************************/
{
// constructor / destructor
public:
	UARTInterface(void);
	~UARTInterface(void);

// class support functions
public:
	// setup
	bool			Initialize(unsigned int FTDIDevNum, FT_HANDLE *ppHandle);
	bool			SetFreq(float ReqFreq, float *pActualFreq);

	// Centeye communications interface
	bool			CEyeWrite(unsigned char Addr, unsigned char *Data, unsigned int DataSize);
	bool			CEyeRead(unsigned char Addr, bool DevFound, unsigned char DSID, DynArray<unsigned char> *pDevData, CommDS *pDSHdr);
	bool			SendSimpleFlowCmd(unsigned char Addr, unsigned char FlowCmd);
	bool			SendIAPPage(unsigned char Addr, unsigned char *Data, unsigned int DataSize);

	// UART basics
	bool			UARTWrite(unsigned char *Data, unsigned int Size);
	bool			UARTRead(unsigned char *Data, unsigned int Size, bool DevFound);
	bool			GetRXQueue(unsigned long *pBytesAvail);

private:
	// setup
	bool			PurgeFTDI(bool PurgeRX, bool PurgeTX);
	bool			SetTimeoutByMsgSize(unsigned long RxBytes, unsigned long Factor);

	// FTDI library wrappers
	bool			FTWrite(unsigned char *Data, unsigned long Size);
	bool			FTRead(unsigned char *Data, unsigned long Size, bool DevFound);

    // class member variables
public:
	// adapter
	BOOL						m_FTDIAttached;					// FTDI USB adapter attached and selected flag
	FT_HANDLE					*m_ppFTDIHandle;				// pointer to the handle to the FTDI communications interface

	// timing
	float						m_BusFreq;						// bus frequency (Hz)
	float						m_ClkPeriod;					// clock period (s)

	// buffers
	DynArray<unsigned char>		m_TxBuf;						// transmit buffer to FTDI chip

	// helpers
	MathExt						m_Math;							// math extensions
};

#endif	// UART_INTERFACE_H
