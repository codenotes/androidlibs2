/*******************************************************************************
 I2CInterface.h : Communications interface using the USB-I2C V2 PCB.

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

#ifndef USB_I2C_V2_H
#define USB_I2C_V2_H

#pragma once

#include	"ftd2xx.h"
#include	"CommDefines.h"
#include	"I2CInterface.h"
#include	"SPIInterface.h"
#include	"UARTInterface.h"
#include    "DynArray.h"


/*******************************************************************************
Constants
*******************************************************************************/
// communications interface type codes
#define	USBI2C_COMM_INT_I2C			0							// MPSSE: I2C
#define	USBI2C_COMM_INT_UART		1							// UART
#define	USBI2C_COMM_INT_SPI			2							// MPSSE: SPI
#define	USBI2C_COMM_INT_DEFAULT		USBI2C_COMM_INT_UART
#define	USBI2C_COMM_INT_TTY			4							// tty

// MPSSE (I2C/SPI) PCB pins: ADBUS
#define	USBI2C_SPI_MASK				0x0F						// SPI pins in ADBUS
#define	USBI2C_I2C_MASK				0x07						// I2C pins in ADBUS
#define	USBI2C_I2C_OUT_MASK			0x03						// I2C output pins in ADBUS
#define USBI2C_D4567_MASK			0xF0						// D[7:4] GPIO pins in ADBUS
#define	USBI2C_CS_MASK				0x08						// SPI chip select pin in ADBUS
#define	USBI2C_DI_MASK				0x04						// I2C/SPI data in pin in ADBUS
#define	USBI2C_DO_MASK				0x02						// I2C/SPI data out pin in ADBUS
#define	USBI2C_SK_MASK				0x01						// I2C/SPI clock pin in ADBUS

// MPSSE (I2C/SPI) PCB pins: ACBUS
#define	USBI2C_SPI_DRDY_MASK		0x80						// SPI data ready pin in ACBUS
#define	USBI2C_DI_DO_SW_MASK		0x40						// DI/DO combine !enable pin in ACBUS
#define	USBI2C_VOUT_EN_MASK			0x20						// Vout enable pin in ACBUS
#define	USBI2C_PWREN_MASK			0x10						// USB power !enable in ACBUS
#define	USBI2C_LED1_MASK			0x08						// LED1 !enable pin in ACBUS
#define USBI2C_C012_MASK			0x07						// C[2:0] GPIO pins in ACBUS

// UART PCB pins: CBUS I/O (bit-bang mode)
#define	USBI2C_CBUS_GPIO_C9_MASK	0x08						// GPIO on C9 pin in CBUS bit bang mode
#define	USBI2C_CBUS_LED2_MASK		0x04						// LED2 !enable pin in CBUS bit bang mode
#define	USBI2C_CBUS_DI_DO_SW_MASK	0x02						// DI/DO combine !enable pin in CBUS bit bang mode
#define	USBI2C_CBUS_VOUT_EN_MASK	0x01						// Vout enable pin in CBUS bit bang mode


/******************************************************************************/
class USBI2Cv2
/******************************************************************************/
{
	// constructor / destructor
public:
	USBI2Cv2(void);
	~USBI2Cv2(void);

// class support functions
public:
	// setup
	bool            GetNumDevices(unsigned long *pNumDev);
	bool			Initialize(unsigned int FTDIDevNum, unsigned int CommInt);
	bool			GetRXQueue(unsigned long *pBytesAvail);
	bool			PurgeFTDI(bool PurgeRX, bool PurgeTX);
	bool			SetFreq(float ReqFreq, float *pActualFreq);
	float			GetFreq(void);
	bool			Shutdown(void);
	void			CleanMem(void);

	// Centeye communications interface
	bool			CEyeWrite(unsigned char Addr, unsigned char *Data, unsigned int DataSize);
	bool			CEyeRead(unsigned char Addr, bool DevFound, unsigned char DSID, DynArray<unsigned char> *pDevData, CommDS *pDSHdr);
	bool			SendSimpleFlowCmd(unsigned char Addr, unsigned char FlowCmd);
	bool			SendIAPPage(unsigned char Addr, unsigned char *Data, unsigned int DataSize);

	// PCB control
	bool			InitPCB(void);
	bool			SetDevPower(bool Enable, bool Hold);
	bool            SwitchDevCommInt(unsigned int CommInt);

	// GPIO: MPSSE (I2C/SPI)
	bool			MPSSESetLED1(bool Enable);
	bool			MPSSESetC0C1C2(unsigned char Dir, unsigned char Out);
	bool			MPSSEGetC0C1C2(unsigned char *pInVal);
	bool			MPSSESetD4D5D6D7(unsigned char Dir, unsigned char Out);
	bool			MPSSEGetD4D5D6D7(unsigned char *pInVal);
	bool            MPSSEGetDRDY(bool *pDRDY);

	// GPIO: UART
	bool			UARTSetLED2(bool Enable);
	bool			UARTSetC9(bool Output, bool Enable);
	bool			UARTGetC9(bool *pInVal);
	bool			UARTSetD2(bool Enable);
	bool			UARTSetD4(bool Enable);
	bool			UARTGetD3D5D6D7(unsigned char *pInVal);

private:
	// GPIO: MPSSE (I2C/SPI)
	bool			SetGPIODBus(unsigned char DBusDir, unsigned char DBusVal);
	bool			SetGPIOCBus(unsigned char CBusDir, unsigned char CBusVal);
	bool			GetGPIOVal(unsigned char *pDBusVal, unsigned char *pCBusVal);

	// FTDI library wrappers
	bool			FTWrite(unsigned char *Data, unsigned long Size);
	bool			FTRead(unsigned char *Data, unsigned long Size);

// class member variables
public:
	// communications classes
	unsigned int				m_CommInt;					// current communications interface code
	I2CInterface				m_I2C;						// FTDI-I2C using MPSSE interface class
	SPIInterface                m_SPI;						// FTDI-SPI using MPSSE interface class
	UARTInterface				m_UART;						// FTDI-UART interface class

	// adapter
	BOOL						m_FTDIAttached;				// FTDI USB adapter attached and selected flag
	FT_HANDLE					m_pFTDIHandle;				// handle to the FTDI communications interface
	unsigned int				m_FTDIDevIdx;				// currently selected FTDI device index
	unsigned long				m_FTDINumDevs;				// number of attached FTDI devices / channels
	FT_DEVICE_LIST_INFO_NODE	*m_pDevInfo;				// FTDI device info list

	// PCB control
	bool						m_DevPwr;					// device power output enable
	bool						m_DevPwrHold;				// device power output hold-after-shutdown flag

	// MPSSE (I2C/SPI): GPIO
	unsigned char				m_DBusDir;					// ADBUS pin directions (0: input, 1: output)
	unsigned char				m_DBusDrv;					// ADBUS pin drivers (0: push-pull, 1: tri-state)
	unsigned char				m_DBusOut;					// ADBUS output pin values
	unsigned char				m_CBusDir;					// ACBUS pin directions (0: input, 1: output)
	unsigned char				m_CBusDrv;					// ACBUS pin drivers (0: push-pull, 1: tri-state)
	unsigned char				m_CBusOut;					// ACBUS output pin values
	bool						m_LED1Val;					// LED1 output value (0: on, 1: off);

	// UART: GPIO
	unsigned char				m_CBusIOCmd;				// CBUS pin directions (0: I, 1: O; upper nibble) and output values (lower nibble)
	bool						m_LED2Val;					// LED2 output value (0: on, 1: off);
	bool						m_IsC9Out;					// C9 is configured as an output flag
	bool						m_C9Val;					// C9 output value
	bool						m_D2Out, m_D4Out;			// D2, D4 output value
};

#endif  // USB_I2C_V2_H
