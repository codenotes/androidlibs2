/*******************************************************************************
 I2CInterface.h : Communications interface using FTDI's USB-I2C bridge / MPSSE engine.

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

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#pragma once

#include    <stdio.h>
#include    <stdlib.h>

#include	"ftd2xx.h"
#include	"CommDefines.h"
#include	"DynArray.h"


/*******************************************************************************
Constants
*******************************************************************************/
// timing defaults
#define	I2C_USB_LATENCY				3							// USB latency timer (ms)
#define	I2C_FREQ_DEFAULT			400000          			// default I2C bus frequency (Hz)
#define	I2C_READ_TO_MIN				100							// minimum read timeout (ms) (0 = block)
#define	I2C_WRITE_TO				5000						// write timeout (ms) (0 = block)
#define	I2C_TO_FACTOR				10							// read timeout multiplication factor

// PCB pins: ADBUS
#define	I2C_PCB_PIN_MASK			0x07						// I2C pins in ADBUS
#define	I2C_PCB_OUT_MASK			0x03						// I2C output pins in ADBUS
#define	I2C_PCB_DI_MASK				0x04						// I2C/SPI data in pin in ADBUS
#define	I2C_PCB_DO_MASK				0x02						// I2C/SPI data out pin in ADBUS
#define	I2C_PCB_SK_MASK				0x01						// I2C/SPI clock pin in ADBUS


/******************************************************************************/
class I2CInterface
/******************************************************************************/
{
// constructor / destructor
public:
	I2CInterface(void);
	~I2CInterface(void);

// class support functions
public:
	// setup
	bool			Initialize(unsigned int FTDIDevNum, FT_HANDLE *ppHandle);
	bool			SetFreq(float ReqFreq, float *pActualFreq, bool ThreePhase);

	// Centeye communications interface
	bool            CEyeWrite(unsigned char Addr, unsigned char *Data, unsigned int DataSize);
	bool            CEyeRead(unsigned char Addr, unsigned char DSID, DynArray<unsigned char> *pDevData, CommDS *pDSHdr);

	// I2C basics
	bool			I2CStart(void);
	bool			I2CStop(void);
	bool			I2CWrite(unsigned char *Data, unsigned long Size, bool *pNACK);
	bool			I2CRead(unsigned char *Data, unsigned long Size);
	bool			GetRXQueue(unsigned long *pBytesAvail);

	// GPIO
	bool			SetGPIODBus(unsigned char DBusDir, unsigned char DBusVal);
	bool			SetGPIOCBus(unsigned char CBusDir, unsigned char CBusVal);
	bool			GetGPIOVal(unsigned char *pDBusVal, unsigned char *pCBusVal);

private:
	// setup
	bool			PurgeFTDI(bool PurgeRX, bool PurgeTX);
	bool			SetTimeoutByMsgSize(unsigned long RxBytes, unsigned long Factor);

	// FTDI library wrappers
	bool			FTWrite(unsigned char *Data, unsigned long Size);
	bool			FTRead(unsigned char *Data, unsigned long Size);

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

	// GPIO
	unsigned char				*m_pDBusDir;					// ADBUS pin directions (0: input, 1: output)
	unsigned char				*m_pDBusDrv;					// ADBUS pin drivers (0: push-pull, 1: tri-state)
	unsigned char				*m_pDBusOut;					// ADBUS output pin values
	unsigned char				*m_pCBusDir;					// ACBUS pin directions (0: input, 1: output)
	unsigned char				*m_pCBusDrv;					// ACBUS pin drivers (0: push-pull, 1: tri-state)
	unsigned char				*m_pCBusOut;					// ACBUS output pin values
};

#endif	// I2C_INTERFACE_H
