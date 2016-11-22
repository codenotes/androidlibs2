#pragma once

//#define TESTING
#pragma warning( disable : 4313)
#pragma warning( disable : 4101)

#include <boost/asio/serial_port.hpp> 
//#include <boost/asio.hpp>
#include <vector>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QThread>
#include "DynArray.h"


#include "CommDefines.h"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <boost/thread.hpp>
//#include <chrono>
//#include <thread>

//ms to sleep after initial readDataSet write




#ifdef _MSC_VER //Had to remove because of 64/32 issues...and it won't wont work with epic build system anyway (at least I dont think so)
//#pragma comment(lib, "boost_system-vc140-mt-1_58.lib")
//#pragma comment(lib, "boost_thread-vc140-mt-1_58.lib")
//#pragma comment(lib, "Qt5Guid.lib")
//#pragma comment(lib, "Qt5Cored.lib")
#endif

//below is size of the buffer we use to read from the beacon.
#define MAX_TRIANGULATOR_MESSAGE_SIZE	1024
#define	SG_CMD_MAX_SIZE				1024				// maximum size of a command
#define SERIAL_DELAY 25  //msec

using namespace std;

namespace Triangulator
{
	//what to do on Linux...don't know...

	struct LocalizeMessage
	{

		float X;
		float Y;
		float Z;
		//	"•    System 3D position in centimeters (float 32-bits each).
		float Rx;
		float Ry;
		float Rz;

		//	"•    System 3D pose in degrees (float 32-bits each).
		float LKG_X;
		float LKG_Y;
		float LKG_Z;
		//	"•    “Last Known Good” system 3D position in centimeters
		float LKG_Rx;
		float LKG_Ry;
		float LKG_Rz;
		//	"•    “Last Known Good” system 3D pose in degrees
		float LimXMinus;
		float LimXPlus;
		float  LimYMinus;
		float LimYPlus;
		float LimZMinus;
		float LimZPlus;
		//	"•    Environment limits along each axis in centimeters 
		float ErrMag;
		//	"•    Error magnitude, average angle error in degrees
		unsigned int Status;
		bool ConvErr;
		bool LNGAvail;


	};
	
	


		class TriangulatorSensorInterface
	{
		
		class beacon
		{
		public:
			float ID;
			float x;
			float y;
			float z;
			beacon(float ID, float x, float y, float z)
				: ID(ID)
				, x(x)
				, y(y)
				, z(z)
			{}
		};
		
	public:
		class BestIDMessage
		{
			char tmp[512];
		public:
			float ID;
			float R;
			float C;
			float SS;
			float Theta;
			float Phi;
			float AdjR;
			float AdjC;
			float ObsErr;
			float Status;
		
			bool IsReflect;
			bool IsUsedInEst;
			bool IsOvl;
			
	


			BestIDMessage(
						float ID,
				float R,
				float C,
				float SS,
				float Theta,
				float Phi,
				float AdjR,
				float AdjC,
				float ObsErr,
				float Status,
		
				bool IsReflect,
				bool IsUsedInEst,
				bool IsOvl)
				:
				 R (R)
				, C (C)
				, SS (SS)
				, Theta (Theta)
				, Phi (Phi)
				, AdjR (AdjR)
				, AdjC (AdjC)
				, ObsErr (ObsErr)
				, Status (Status)
				, IsReflect (IsReflect)
				, IsUsedInEst (IsUsedInEst)
				, IsOvl (IsOvl)
				, ID(ID)
			{


		//cout<<
//
				//"2-->ID "<<ID<<
				//"AdjC: "<<AdjC<<
				//"AdjR: "<<AdjR<<
				//"C: "<<C<<
				//"IsOvl: "<<IsOvl<<
				//"IsReflect: "<<IsReflect<<
				//"IsUsedInEst: "<<IsUsedInEst<<
				//"ObsErr: "<<ObsErr<<
				//"Phi: "<<Phi<<
				//"R: "<<R<<
				//"SS: "<<SS<<
				//"Status: "<<Status<<
				//"Theta:\n"<<Theta<<endl;//, //"------------------weq323-324-234------------------234234234-------------->%d",
				//ID,
				//AdjC,
				//AdjR,
				//C,
				//IsOvl,
				//IsReflect,
				//IsUsedInEst,
				//ObsErr,
				//Phi,
				//R,
				//SS,
				//Status,
				//Theta);

			//	cout<<tmp<<endl;


//printf("THETATEST2##:%.4f\n");

				}
		
		};
		
		
	public:
		int numBeacons = 8;

		std::vector<std::shared_ptr<BestIDMessage>> mvBestID;
	private:

		const int commandID = 16;
		std::vector<std::shared_ptr<beacon>> mBeacons;
		
		
		unsigned char mData[MAX_TRIANGULATOR_MESSAGE_SIZE];
		unsigned char mData2[24]; //env
		boost::asio::io_service m_io;
		boost::asio::serial_port * pSerialPort = nullptr;
		CommDS					DSHdr;
		DynArray<unsigned char>		m_DevData;
		std::string m_port;
		std::string beaconFile;
		std::string envFile;

		bool useConfigFile = false;

		int index = 1;
		
		void toArrayEnv();
		void toArray();
	
		
		//can read request and get back any dataset
		bool readDataSet(unsigned char DSID, DynArray<unsigned char> *pDevData, CommDS *pDSHdr);

		//just fills the datastructures, does not do the read
		void DynArrayToLocalizeMessage(DynArray<unsigned char> &m_DevData, CommDS & DSHdr, LocalizeMessage & lm);


		void printLocalization(DynArray<unsigned char> &m_DevData, CommDS & DSHdr);
		

		void convertFloat32ToVector(unsigned char *Data, vector<float> & vFloat, bool flip = true, int numFloats = 1);
		
		
/*******************************************************************************
ParseCmdArg
Parses a command argument string and adds the data to a byte array.
Commands are formatted as: <type><number>
 where <type> may be one of the following supported types:
 * c:	char (1-byte)
 * s:	short (2-byte)
 * i:	int (4-byte)
 * f:	float (4-byte)
 * l:	load file (file may contain arguments formatted with any of the above type codes)

Input:	ArgStr:		argument string
		pCmd:		pointer to the command array being built
		pCounter:	pointer to a byte counter for the command array
Return:	true if command argument was added to the array successfully,
		else false
*******************************************************************************/
		bool ParseCmdArg(QString ArgStr, unsigned char *pCmd, int *pCounter)
		/******************************************************************************/;
		
		
		

		bool sendCommandFile(unsigned int CmdID, QString FileName)
		/******************************************************************************/;


		//TODO, add other data to dump here, right now it is just BestID. 
		void dump();



		/***********PUBLIC***********/
	public:
		enum TriangulatorDSCommands {GET_LOCALIZATION = 6, GET_VOLTAGE = 3, SET_ENV_LIMITS = 15, SET_BEACON_LIST = 16, GET_BEST_BEACON=7, ENABLE_LOCALIZATION=20};
		//be sure to * REPORT_SIZE by number of beacons you have
		enum TriangulatorDSSizes {SIZE_ENV_LIMITS = 24, SIZE_BEACON_LIST = 128, SIZE_VOLTAGE = 2, SIZE_BEST_BEACON_REPORT_SIZE=40}; 

		bool sendCommand(unsigned int cmd, unsigned char * data, unsigned int size);
		//mostly just used for testing/debugging
		void setConfigFiles(std::string bFile, std::string eFile);
		
		bool getBestID();
		
		bool getVoltage(float & mainPwr, float & usbPwr);
		
		void startLocalizer();
		
		void stopLocalizer();

		LocalizeMessage  getLocalization();

		unsigned char * getBeaconSetMessage();
		unsigned char * getEnvLimitMessage();
		
		bool sendBeaconSettings(bool fromFile=true);
		bool sendEnvSettings(bool fromFile=false);

		float envXPlus = 0;
		float envXMinus = 0;
		float envYPlus = 0;
		float envYMinus = 0;
		float envZPlus = 0;
		float envZMinus = 0;

		void setEnv(float xplus, float xminus, float yplus, float  yminus, float zplus, float  zminus); 

		~TriangulatorSensorInterface();
		TriangulatorSensorInterface(std::string port);
		TriangulatorSensorInterface();
		void printArrays();
		void reset();

		void addBeacon(float ID, float x, float y, float z);
		bool openUART();
		bool closeUART();
		bool openUART(std::string port);


	private:
		DynArray<unsigned char>		m_TxBuf;		
		bool toFloatArg(QString ArgStr, unsigned char * pCmd);
		boost::mutex mtx_;
		
		bool SendSimpleFlowCmd(unsigned char Addr, unsigned char FlowCmd);
		bool CEyeWrite(unsigned char Addr, unsigned char *Data, unsigned int DataSize);




	};
}