/*******************************************************************************
 CommDefines.h : Communications interface definitions.

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

#ifndef COMM_DEFINES_H
#define COMM_DEFINES_H

#pragma once

#ifndef _NO_FTDI
#include	"ftd2xx.h"
#endif


/*******************************************************************************
Constants
*******************************************************************************/
// dataset header special characters
#define	COMM_SOH					0xAA						// start-of-header byte
#define	COMM_EOH					0xAB						// end-of-header byte

// standard device commands and datasets
#define	COMM_CMD_DATASET			0							// change dataset-to-TX
#define	COMM_DS_ID_STRING			0							// device ID string

// dataset dimensions
#define	COMM_DEV_ID_STR_SIZE		4							// length of the device ID string dataset
#define	COMM_DS_HDR_ARGS_MAX		8							// maximum supported header arguments
#define	COMM_DS_HDR_SIZE			16							// standard dataset header size
#define	COMM_DS_PACKET_SIZE			63472						// maximum TX between 'MISO proceed' commands (this is 64kB*(62/64) - COMM_DS_HDR_SIZE)

// transmission flow control
#define	COMM_ESCAPE					0xFF						// escape character
#define	COMM_FLOW_MOSI				1							// master-out slave-in (MOSI)
#define	COMM_FLOW_MISO				2							// master-in slave-out (MISO)
#define	COMM_FLOW_MISO_PROCEED		3							// master-in slave-out (MISO) proceed
#define	COMM_FLOW_FLASH_BEGIN		4							// begin flash programming
#define	COMM_FLOW_FLASH_PAGE		5							// flash programming page
#define	COMM_FLOW_FLASH_END			6							// end flash programming
#define	COMM_FLOW_STOP				0xFE						// end flow control packet

// GUI display types
#define	COMM_DISP_U8				0							// unsigned chars (8-bit words)
#define	COMM_DISP_S8				1							// signed chars (8-bit words)
#define	COMM_DISP_U16				2							// unsigned shorts (16-bit words)
#define	COMM_DISP_S16				3							// short ints (16-bit words)
#define	COMM_DISP_U32				4							// unsigned ints (32-bit words)
#define	COMM_DISP_S32				5							// signed ints (32-bit words)
#define	COMM_DISP_FLOAT				6							// floating points (32-bit words)
#define	COMM_DISP_AXIS_ARRAY_S16	7							// X/Y vectors along axes array (16-bit words)
#define	COMM_DISP_VECTOR_ARRAY_S8	8							// vector array (8-bit words, 8-bit dimensions)
#define	COMM_DISP_IMAGE_U8			9							// image (8-bit words, 8-bit dimensions)
#define	COMM_DISP_IMAGE_LARGE_U8	10							// image (8-bit words, 16-bit dimensions)
#define	COMM_DISP_IMAGE_U16			11							// image (16-bit words, 8-bit dimensions)
#define	COMM_DISP_IMAGE_LARGE_U16	12							// image (16-bit words, 16-bit dimensions)
#define	COMM_DISP_IMAGE_ARRAY_U8	13							// array of images (8-bit words, 8-bit dimensions)
#define COMM_DISP_COORD_LIST		14							// coordinate list (16-bit words)
#define	COMM_DISP_COORD_LIST_FLT	15							// coordinate list (32-bit floats)
#define	COMM_DISP_POS_POSE			16							// position/pose (32-bit floats)
#define	COMM_DISP_FILE_U16			17							// file download: unsigned shorts (16-bit words)
#define	COMM_DISP_VN_LIST_FLT		18							// visual node list (32-bit floats)

// in-application programming
#define COMM_IAP_PAGE_MAX_SIZE		1024						// IAP page maximum size


/*******************************************************************************
CommDS
Communications dataset definition. Received over a communications link.

Format:
 [0]   [1]     [2:5]          [6]         [7:14]          [15]  [16]       [16+(N-1)]
 [SOH] [DS ID] [DS SIZE[3:0]] [DISP TYPE] [HDR ARGS[7:0]] [EOH] [D(0)] ... [D(SIZE-1)]
*******************************************************************************/
struct	CommDS
/******************************************************************************/
{
	// status and type
	bool			Valid;							// dataset received and parsed OK flag
	unsigned int	ID;								// dataset ID
	unsigned int	Size;							// dataset size
	unsigned int	DispType;						// GUI display type

	// header
	unsigned int	NumArgs;						// number of header arguments used (in bytes)
	unsigned int	Args[COMM_DS_HDR_ARGS_MAX];		// header arguments (or pointers to arguments)


	CommDS(void)
	{
		// flag not valid
		Valid = false;
	}

	bool ParseIncoming(unsigned char *DataRX, unsigned int SizeRX)
	{
		unsigned int	i;						// loop index


		// validate received size and start/end header bytes
		if ((SizeRX < COMM_DS_HDR_SIZE) || (DataRX[0] != COMM_SOH) || (DataRX[15] != COMM_EOH))
			return (Valid = false);

		// parse header type
		ID = DataRX[1];
		Size = (unsigned int)(DataRX[2] << 24) + (unsigned int)(DataRX[3] << 16) + (unsigned int)(DataRX[4] << 8) + (unsigned int)DataRX[5];
		DispType = DataRX[6];

		// get number of expected arguments based on display type
		switch (DispType)
		{
			case COMM_DISP_IMAGE_LARGE_U8:
			case COMM_DISP_IMAGE_LARGE_U16:
			case COMM_DISP_IMAGE_ARRAY_U8:
			case COMM_DISP_COORD_LIST:
			case COMM_DISP_COORD_LIST_FLT:
			case COMM_DISP_VN_LIST_FLT:
				NumArgs = 4;
				break;
			case COMM_DISP_AXIS_ARRAY_S16:
			case COMM_DISP_VECTOR_ARRAY_S8:
			case COMM_DISP_IMAGE_U8:
			case COMM_DISP_IMAGE_U16:
				NumArgs = 2;
				break;
			case COMM_DISP_U8:
			case COMM_DISP_S8:
			case COMM_DISP_U16:
			case COMM_DISP_S16:
			case COMM_DISP_U32:
			case COMM_DISP_S32:
			case COMM_DISP_FLOAT:
			case COMM_DISP_POS_POSE:
			case COMM_DISP_FILE_U16:
			default:
				NumArgs = 0;
				break;
		}

		// copy arguments
		for (i = 0; i < COMM_DS_HDR_ARGS_MAX; i++)
			Args[i] = DataRX[7 + i];

		// all checks passed, return OK
		return (Valid = true);
	}
};


#endif	// COMM_DEFINES_H
