/*******************************************************************************
 USBI2Cv2Config.h : Configuration GUI for the USB-I2C V2 PCB.

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

#ifndef USB_I2C_V2_CONFIG_H
#define USB_I2C_V2_CONFIG_H

#include <QtWidgets/QDialog>
#include "ui_USBI2Cv2Config.h"
#include "USBI2Cv2.h"
#include "ftd2xx.h"


/******************************************************************************/
namespace Ui
{
	class USBI2Cv2Config;
}
class USBI2Cv2Config : public QDialog
/******************************************************************************/
{
	Q_OBJECT

// class support functions
public:
	// constructor / destructor
	explicit USBI2Cv2Config(QWidget *parent = 0);
	~USBI2Cv2Config(void);

	// communications setup
	void	SetAdaptor(USBI2Cv2 *pUSBPCB);

	// runtime parameter sheet update
	bool	RuntimeUpdate(void);

// class UI event handlers
private slots:
	void	showEvent(QShowEvent *pEvent);
	void	closeEvent(QCloseEvent *pEvent);
	void	on_DevPwrHoldCheck_clicked(bool Checked);
	void	on_LED2Check_clicked(bool Checked);
	void	on_LED1Check_clicked(bool Checked);
	void	on_UARTC9OutCheck_clicked(bool Checked);
	void	on_UARTC9ValCheck_clicked(bool Checked);
	void	on_UARTD4ValCheck_clicked(bool Checked);
	void	on_UARTD2ValCheck_clicked(bool Checked);
	void	MPSSEC012Clicked(void);
	void	MPSSED4567Clicked(void);
	void	on_BusFreqButton_clicked(void);
	void	on_SPIDelayButton_clicked(void);

// class support functions
private:
	void	CheckBoxReport(bool CommOK, QString CBName, QCheckBox *pCB, bool OldVal);

// class member variables
public:
	// system status
	bool				m_UILaunched;				// dialog launched flag

// class member variables
private:
	// GUI
	Ui::USBI2Cv2Config	*ui;						// user interface

	// communications
	USBI2Cv2			*m_pUSBPCB;					// pointer to the communications adaptor class

	// helpers
	QString				m_S;						// generic string
};

#endif	// USB_I2C_V2_CONFIG_H
