/*******************************************************************************
 SPIInterface.h : Communications interface using FTDI's USB-SPI bridge / MPSSE engine.

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

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

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
#define	SPI_USB_LATENCY				3							// USB latency timer (ms)
#define	SPI_FREQ_DEFAULT			1000000						// default SPI bus frequency (Hz)
#define	SPI_READ_TO_MIN				50							// minimum read timeout (ms) (0 = block)
#define	SPI_WRITE_TO				5000						// write timeout (ms) (0 = block)
#define	SPI_TO_FACTOR				10							// read timeout multiplication factor
#define	SPI_BYTE_DELAY_DEFAULT		0							// default approximate per-byte delay (s)

// PCB pins: ADBUS
#define	SPI_PCB_PIN_MASK			0x0F						// SPI pins in ADBUS
#define	SPI_PCB_OUT_MASK			0x0B						// SPI output pins in ADBUS
#define	SPI_PCB_CS_MASK				0x08						// SPI chip select pin in ADBUS
#define	SPI_PCB_DI_MASK				0x04						// I2C/SPI data in pin in ADBUS
#define	SPI_PCB_DO_MASK				0x02						// I2C/SPI data out pin in ADBUS
#define	SPI_PCB_SK_MASK				0x01						// I2C/SPI clock pin in ADBUS


/******************************************************************************/
class SPIInterface
/******************************************************************************/
{
// constructor / destructor
public:
	SPIInterface(void);
	~SPIInterface(void);

// class support functions
public:
	// setup
	bool			Initialize(unsigned int FTDIDevNum, FT_HANDLE *ppHandle);
	bool			SetFreq(float ReqFreq, float *pActualFreq, bool ThreePhase);
	void			SetByteDelay(float ReqDelay);

	// Centeye communications interface
	bool            CEyeWrite(unsigned char Addr, unsigned char *Data, unsigned int DataSize);
	bool            CEyeRead(unsigned char Addr, unsigned char DSID, DynArray<unsigned char> *pDevData, CommDS *pDSHdr);

	// SPI basics
	bool			SPISetCS(bool Assert);
	bool			SPIWrite(bool UseCS, unsigned char *Data, unsigned long Size);
	bool			SPIWrite16(bool UseCS, unsigned short *Data, unsigned long Size);
	bool			SPIRead(bool UseCS, unsigned char *Data, unsigned long Size);
	bool			SPIRead16(bool UseCS, unsigned short *Data, unsigned long Size);
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

	// timing and formatting
	float						m_BusFreq;						// bus frequency (Hz)
	float						m_ClkPeriod;					// clock period (s)
	float						m_ByteDelayTime;				// approximate per-byte delay (s)
	unsigned long				m_ByteDelayCycles;				// cycles of delay between each byte TX/RX (about 200ns each)

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

#endif	// SPI_INTERFACE_H
