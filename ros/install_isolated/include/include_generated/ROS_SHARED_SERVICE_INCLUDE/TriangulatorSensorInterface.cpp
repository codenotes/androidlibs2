#include "TriangulatorSensorInterface.h"

//50 25 respectively
#define RDS_SLEEP1 60 
//after readsome
#define RDS_SLEEP2 45 


void dumpbin(unsigned char * data, int size)
{

	for (int i = 0; i < size; i++)
		printf("%x ", data[i]);

	printf("\n");

}


void Triangulator::TriangulatorSensorInterface::toArrayEnv()
{

	QString s;
	index = 1;
	mData2[0] = TriangulatorDSCommands::SET_ENV_LIMITS; //first byte is our command, always

	toFloatArg(QString::number(envXPlus), &mData2[index]);
	index += 4;

	toFloatArg(QString::number(envXMinus), &mData2[index]);
	index += 4;

	toFloatArg(QString::number(envYPlus), &mData2[index]);
	index += 4;

	toFloatArg(QString::number(envYMinus), &mData2[index]);
	index += 4;

	toFloatArg(QString::number(envZPlus), &mData2[index]);
	index += 4;

	toFloatArg(QString::number(envZMinus), &mData2[index]);
	index += 4;
}

void Triangulator::TriangulatorSensorInterface::toArray()
{
	toArrayEnv();
	QString s;
	index = 1;
	int i = 0;

	mData[0] = TriangulatorDSCommands::SET_BEACON_LIST; //first byte is our command, always

	int numFillEmpty = numBeacons - mBeacons.size();

	while (i++ < numFillEmpty)
	{
		addBeacon(0, 0, 0, 0);
	}

	for (std::shared_ptr<beacon> b : mBeacons)
	{
		toFloatArg(QString::number(b->ID), &mData[index]);
		index += 4;

		toFloatArg(QString::number(b->x), &mData[index]);
		index += 4;

		toFloatArg(QString::number(b->y), &mData[index]);
		index += 4;

		toFloatArg(QString::number(b->z), &mData[index]);
		index += 4;
	}
}

bool Triangulator::TriangulatorSensorInterface::readDataSet(unsigned char DSID, DynArray<unsigned char> *pDevData, CommDS *pDSHdr)
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	//unsigned long				BytesAvail;						// RX queue length
	unsigned char				TxMsg[6];						// TX message
	unsigned long				MsgSize;						// message size
	unsigned char				Header[COMM_DS_HDR_SIZE];		// dataset header
	unsigned long				DSReadPos;						// dataset read position
	unsigned long				DSBytesLeft;					// dataset bytes remaining to RX

																//TODO Greg
																//// make sure RX buffer is empty
																//if (!(GetRXQueue(&BytesAvail)))
																//	return (false);

																//// if it is not, clear it
																//if (BytesAvail)
																//	if (!(PurgeFTDI(true, false)))
																//		return (false);

																// form message header for MISO
																//0x06,0xff,0x02,0x20,DISPID,0xff,0xfe

																//return was
																//AA 03 00 00 
																//00 08 06 00
																//00 00 00 00
																//00 00 00 AB
																//E7 06 C4 40
																//9B 24 05 3F 


	if (!pSerialPort->is_open())
	{
		printf("Port not open. No connection to device.");
		return false;
	}


	//see if there is data and if there is purge it, new GREG1
#ifdef WIN32
	PurgeComm(pSerialPort->native_handle(),PURGE_RXCLEAR);
#endif
	//



	MsgSize = 6;
	TxMsg[0] = COMM_ESCAPE;
	TxMsg[1] = COMM_FLOW_MISO;
	TxMsg[2] = 0x20; //was: Addr;
	TxMsg[3] = DSID;
	TxMsg[4] = COMM_ESCAPE;
	TxMsg[5] = COMM_FLOW_STOP;


	//// write the message
	//if (!FTWrite(TxMsg, MsgSize))
	//	return (false);
	if (!pSerialPort->write_some(boost::asio::buffer(TxMsg, MsgSize)))
	{
		
		cout << "fail 1 write\n";
		return false;
	
	}
	//printf("sending:");
	//dumpbin(TxMsg, MsgSize);

	boost::this_thread::sleep(boost::posix_time::milliseconds(RDS_SLEEP1));
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
//// read the header
//if (!(FTRead(Header, COMM_DS_HDR_SIZE, DevFound)))
//	return (false);

	if (!pSerialPort->read_some(boost::asio::buffer(Header, COMM_DS_HDR_SIZE)))// , COMM_DS_HDR_SIZE)))
	{
		
		cout << "fail 2 read\n";
		return (false);
	}
	//printf("header:");
	//dumpbin(Header, COMM_DS_HDR_SIZE);

	boost::this_thread::sleep(boost::posix_time::milliseconds(RDS_SLEEP2));
	// parse header
	if (!(pDSHdr->ParseIncoming(Header, COMM_DS_HDR_SIZE)))
	{
		cout << "fail 3 parse header\n";
		return (false);
	}
	//			boost::this_thread::sleep(boost::posix_time::milliseconds(50));
				// resize data storage array if necessary
	if (!(pDevData->AllocateAsNeeded(pDSHdr->Size)))
	{
		cout << "fail 4 allocate\n";
		return (false);
	}
	// read dataset
	// NOTE: alternate method (read entire dataset)
	//	if (!(FTRead(pDevData->m_Array, pDSHdr->Size, DevFound)))
	//		return (false);

	// read indicated size
	// NOTE: alternate method (read packets until entire dataset is read)
	DSReadPos = 0;
	DSBytesLeft = pDSHdr->Size;
	do
	{
		// request full packets until entire dataset is received
		if (DSBytesLeft >= COMM_DS_PACKET_SIZE)
			MsgSize = COMM_DS_PACKET_SIZE;
		else
			MsgSize = DSBytesLeft;
		//TODO greg
		//		if (!(FTRead(&(pDevData->m_Array[DSReadPos]), MsgSize, DevFound)))
		//			return (false);

		if (!pSerialPort->read_some(boost::asio::buffer(&(pDevData->m_Array[DSReadPos]), MsgSize)))
		{
			printf("Error in reading part of dataset.\n");
			return (false);
		}
		
		
		//	boost::this_thread::sleep(boost::posix_time::milliseconds(SERIAL_DELAY));
			// update indexes
		DSBytesLeft -= MsgSize;
		DSReadPos += MsgSize;

		// if there are bytes remaining, send proceed sequence
		if (DSBytesLeft)
		{
			SendSimpleFlowCmd(0, COMM_FLOW_MISO_PROCEED);

			/*if (!(SendSimpleFlowCmd(Addr, COMM_FLOW_MISO_PROCEED)))
				return (false);*/
		}

	} while (DSBytesLeft);

	//printf("read:");
	//dumpbin(pDevData->m_Array, MsgSize);

	// all checks passed, return OK
	return (true);
}

void Triangulator::TriangulatorSensorInterface::DynArrayToLocalizeMessage(DynArray<unsigned char> &m_DevData, CommDS & DSHdr, LocalizeMessage & lm)
{
	float			*pFlt;								// float casting pointer
	unsigned int	*pU32;								// U32 casting pointer
	float			X, Y, Z, RX, RY, RZ;				// position/pose data (in cm/deg)
	float			LNG[6];								// last known good position/pose data (in cm/deg)
	float			LimXN, LimXP, LimYN, LimYP, LimZN, LimZP;	// limit data (in cm)
	float			EnvNx, EnvNy, EnvNz;				// environment width (in cm)
	float			ErrMag;								// error magnitude (in deg)
	unsigned int	Status;								// status word
	bool			LNGAvail;							// last known good state estimate is available flag
	bool			ConvErr;							// convergence error flag



														// check dataset, report any errors
	if ((DSHdr.DispType != COMM_DISP_POS_POSE) || (DSHdr.Size != 80))
	{
		std::cout << "Dataset header incorrect!\n";
		return;
	}

	// read position/pose/limits/error/status
	pFlt = (float *)(m_DevData.m_Array);
	pU32 = (unsigned int *)(m_DevData.m_Array);
	X = pFlt[0];	Y = pFlt[1];	Z = pFlt[2];
	RX = pFlt[3];	RY = pFlt[4];	RZ = pFlt[5];
	LNG[0] = pFlt[6];	LNG[1] = pFlt[7];	LNG[2] = pFlt[8];
	LNG[3] = pFlt[9];	LNG[4] = pFlt[10];	LNG[5] = pFlt[11];
	LimXN = pFlt[12];	LimXP = pFlt[13];	EnvNx = LimXP - LimXN;
	LimYN = pFlt[14];	LimYP = pFlt[15];	EnvNy = LimYP - LimYN;
	LimZN = pFlt[16];	LimZP = pFlt[17];	EnvNz = LimZP - LimZN;
	ErrMag = pFlt[18];	Status = pU32[19];
	LNGAvail = ((Status & 0x02) != 0);
	ConvErr = ((Status & 0x01) != 0);

	// output data direct to console

	lm.X = X;
	lm.Y = Y;
	lm.Z = Z;
	lm.Rx = RX;
	lm.Ry = RY;
	lm.Rz = RZ;
	lm.LimXMinus = LimXN;
	lm.LimXPlus = LimXP;
	lm.ErrMag = ErrMag;
	lm.LimYMinus = LimYN;
	lm.LimYPlus = LimYP;
	lm.LimZMinus = LimZN;
	lm.LimZPlus = LimZP;
	lm.LKG_Rx = LNG[0];
	lm.LKG_Ry = LNG[1];
	lm.LKG_Rz = LNG[2];
	lm.LKG_X = LNG[3];
	lm.LKG_Y = LNG[4];
	lm.LKG_Z = LNG[5];
	lm.ConvErr = ConvErr;
	lm.LNGAvail = LNGAvail;

//	QThread::msleep(250);
	//			std::cout << "X: " << X << " Y: " << Y << " Z: " << Z;
	//		std::cout << " RX: " << RX << " RY: " << RY << " RZ: " << RZ << "\n";
}

void Triangulator::TriangulatorSensorInterface::printLocalization(DynArray<unsigned char> &m_DevData, CommDS & DSHdr)
{
	float			*pFlt;								// float casting pointer
	unsigned int	*pU32;								// U32 casting pointer
	float			X, Y, Z, RX, RY, RZ;				// position/pose data (in cm/deg)
	float			LNG[6];								// last known good position/pose data (in cm/deg)
	float			LimXN, LimXP, LimYN, LimYP, LimZN, LimZP;	// limit data (in cm)
	float			EnvNx, EnvNy, EnvNz;				// environment width (in cm)
	float			ErrMag;								// error magnitude (in deg)
	unsigned int	Status;								// status word
	bool			LNGAvail;							// last known good state estimate is available flag
	bool			ConvErr;							// convergence error flag



														// check dataset, report any errors
	if ((DSHdr.DispType != COMM_DISP_POS_POSE) || (DSHdr.Size != 80))
	{
		std::cout << "Dataset header incorrect!\n";
		return;
	}

	// read position/pose/limits/error/status
	pFlt = (float *)(m_DevData.m_Array);
	pU32 = (unsigned int *)(m_DevData.m_Array);
	X = pFlt[0];	Y = pFlt[1];	Z = pFlt[2];
	RX = pFlt[3];	RY = pFlt[4];	RZ = pFlt[5];
	LNG[0] = pFlt[6];	LNG[1] = pFlt[7];	LNG[2] = pFlt[8];
	LNG[3] = pFlt[9];	LNG[4] = pFlt[10];	LNG[5] = pFlt[11];
	LimXN = pFlt[12];	LimXP = pFlt[13];	EnvNx = LimXP - LimXN;
	LimYN = pFlt[14];	LimYP = pFlt[15];	EnvNy = LimYP - LimYN;
	LimZN = pFlt[16];	LimZP = pFlt[17];	EnvNz = LimZP - LimZN;
	ErrMag = pFlt[18];	Status = pU32[19];
	LNGAvail = ((Status & 0x02) != 0);
	ConvErr = ((Status & 0x01) != 0);

	// output data direct to console
	std::cout << "X: " << X << " Y: " << Y << " Z: " << Z;
	std::cout << " RX: " << RX << " RY: " << RY << " RZ: " << RZ << "\n";
}

void Triangulator::TriangulatorSensorInterface::convertFloat32ToVector(unsigned char *Data, vector<float> & vFloat, bool flip /*= true*/, int numFloats /*= 1*/)
{
	float		*pFloat = 0;					// float casting pointer
	int size = numFloats * 4;

	union
	{
		unsigned int    Junk;				// force 4-byte alignment for array
		unsigned char   Buf[4];				// word-aligned buffer
	};

	// form floats and add to string for display
	for (int i = 0; i < (size - 1); i += 4)
	{
		if (!flip)
			for (int j = 0; j < 4; j++)
			{
				//printf("%x i:%d ", Data[i + j],i);
				Buf[j] = Data[i + j];
			}
		else
		{
			for (int j = 3; j >= 0; j--)
			{
				//printf("!%x-->i:%d j:%d ", Data[j],i,j);
				Buf[3 - j] = Data[i + j];


			}
		}

		vFloat.push_back(*(float *)Buf);

		//printf("\n");
		//String.append(m_S.setNum(*pFloat, 'f', 3) + " ");

	}
}

bool Triangulator::TriangulatorSensorInterface::ParseCmdArg(QString ArgStr, unsigned char *pCmd, int *pCounter) /******************************************************************************/
{
	char			ArgData;						// argument data byte
	int				ArgVal;							// argument data (integer)
	float			ArgValF;						// argument data (float)
	bool			ValOK;							// argument data OK flag
	unsigned char	*pU8;							// 8-bit casting pointer


		// argument type: char (1-byte)
	if (ArgStr.startsWith("c"))
	{
		// get value
		ArgStr.remove(0, 1);
		ArgVal = ArgStr.toInt(&ValOK, 10);
		if (!ValOK)
		{
			std::cout << " Invalid argument!\n";
			return (false);
		}
		ArgData = static_cast<char>(ArgVal & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
	}
	// argument type: short (2-byte, little-endian)
	else if (ArgStr.startsWith("sl"))
	{
		// get value
		ArgStr.remove(0, 2);
		ArgVal = ArgStr.toInt(&ValOK, 10);
		if (!ValOK)
		{
			std::cout << " Invalid argument!\n";
			return (false);
		}
		ArgData = static_cast<char>(ArgVal & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>((ArgVal >> 8) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
	}
	// argument type: short (2-byte, big-endian)
	else if (ArgStr.startsWith("s"))
	{
		// get value
		ArgStr.remove(0, 1);
		ArgVal = ArgStr.toInt(&ValOK, 10);
		if (!ValOK)
		{
			std::cout << " Invalid argument!\n";
			return (false);
		}
		ArgData = static_cast<char>((ArgVal >> 8) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>(ArgVal & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
	}
	// argument type: int (4-byte, little-endian)
	else if (ArgStr.startsWith("il"))
	{
		// get value
		ArgStr.remove(0, 2);
		ArgVal = ArgStr.toInt(&ValOK, 10);
		if (!ValOK)
		{
			std::cout << " Invalid argument!\n";
			return (false);
		}
		ArgData = static_cast<char>(ArgVal & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>((ArgVal >> 8) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>((ArgVal >> 16) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>((ArgVal >> 24) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
	}
	// argument type: int (4-byte, big-endian)
	else if (ArgStr.startsWith("i"))
	{
		// get value
		ArgStr.remove(0, 1);
		ArgVal = ArgStr.toInt(&ValOK, 10);
		if (!ValOK)
		{
			std::cout << " Invalid argument!\n";
			return (false);
		}
		ArgData = static_cast<char>((ArgVal >> 24) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>((ArgVal >> 16) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>((ArgVal >> 8) & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
		ArgData = static_cast<char>(ArgVal & 0xFF);
		pCmd[*pCounter] = ArgData;	(*pCounter)++;
	}
	// argument type: float (4-byte, little-endian)
	else if (ArgStr.startsWith("f"))
	{
		// get value
		ArgStr.remove(0, 1);
		ArgValF = ArgStr.toFloat(&ValOK);
		if (!ValOK)
		{
			std::cout << " Invalid argument!\n";
			return (false);
		}
		pU8 = (unsigned char *)&ArgValF;
		pCmd[*pCounter] = *pU8;		pU8++;		(*pCounter)++;
		pCmd[*pCounter] = *pU8;		pU8++;		(*pCounter)++;
		pCmd[*pCounter] = *pU8;		pU8++;		(*pCounter)++;
		pCmd[*pCounter] = *pU8;		pU8++;		(*pCounter)++;
	}
	// unrecognized type (not blank)
	else if (ArgStr != "")
	{
		std::cout << " Invalid argument type! Valid types: \n c: char  (1-byte) \n s: short (2-byte) \n i: int (4-byte) \n f: float (4-byte) \n l: load file\n";
		return (false);
	}

	// all checks passed, return OK
	return (true);
}

bool Triangulator::TriangulatorSensorInterface::sendCommandFile(unsigned int CmdID, QString FileName) /******************************************************************************/
{
	

	QFile					InputFile;					// data file
	QString					LineStr;					// line read from file
	QString					Entry;						// file entry string
	int						LineIdx;					// file line index
	QStringList				LineContents;				// file line contents
	unsigned char			TxCmd[SG_CMD_MAX_SIZE];		// TX command
	int						Counter;					// command byte counter


		// open file for reading
	InputFile.setFileName(FileName);
	if (!(InputFile.open(QIODevice::ReadOnly)))
	{
		std::cout << " Invalid file name!\n";
		return (false);
	}
	QTextStream	InStream(&InputFile);

	// search to "/data" indicating start of the data file
	while ((LineStr = InStream.readLine()) != "/data")
	{
		// if at the end of the file, format error, stop search
		if (InStream.atEnd())
		{
			std::cout << " File format error!\n";
			InputFile.close();
			return (false);
		}
	}

	// add command ID to command array
	TxCmd[0] = CmdID;	Counter = 1;

	// parse lines until "/end_sensors" to end list
	while ((LineStr = InStream.readLine()) != "/end_data")
	{
		// process line
		LineContents = LineStr.split(QRegExp("\\s+"));
		for (LineIdx = 0; LineIdx < LineContents.length(); LineIdx++)
		{
			// pass argument to parsing function to add to command array
			Entry = LineContents.at(LineIdx);
			if (!ParseCmdArg(Entry, TxCmd, &Counter))
			{
				InputFile.close();
				return (false);
			}
		}

		// if at the end of the file, format error, stop search
		if (InStream.atEnd())
		{
			std::cout << " File format error!\n";
			InputFile.close();
			return (false);
		}
	}

	// close file
	InputFile.close();

	// write command and report status
	return (sendCommand(CmdID, TxCmd, Counter));
}

void Triangulator::TriangulatorSensorInterface::dump()
{

	printf("dumping bestID is any...\n");

	for (std::shared_ptr<BestIDMessage> & b : mvBestID)
	{
		
		//printf("ID:%.3f\nR:%.3f\nID:%.3f\n"
		//	"C:%.3f\nSS:%.3f\nTheta:%.3f\nPhi:%.3f\n"
		//	"AdjR:%.3f\nAdjC:%.3f\nObsErr:%.3f\n"
		//	"Status:%d\nIsReflect:%d\nIsUsedInEst:%d\nIsOvl:%d\n",
		//	b->R,
		//	b->ID,
		//	b->C,
		//	b->SS,
		//	b->Theta,
		//	b->Phi,
		//	b->AdjR,
		//	b->AdjC,
		//	b->ObsErr,
		//	b->Status,
		//	b->IsReflect,
		//	b->IsUsedInEst,
		//	b->IsOvl);

	}

	printf("------------\n");
}

#ifdef TESTING
bool Triangulator::TriangulatorSensorInterface::sendCommand(unsigned int cmd, unsigned char * data, unsigned int size)
{
	printf("sendCommand:%d\n", cmd);

	switch (cmd)
	{

	case TriangulatorDSCommands::ENABLE_LOCALIZATION:

		printf("enable/disable sensor:%d\n", data[1]);
		printf("%x %x", data[0], data[1]);


		break;


	case TriangulatorDSCommands::SET_BEACON_LIST:


		for (int i = 0; i < size; i++)
		{
			printf("%x ", data[i]);

			if (i % 4 == 0)
			{
				printf("\n");

			}

			if (i % 16 == 0)
			{
				printf("----\n");
			}
		}


		break;


	case TriangulatorDSCommands::SET_ENV_LIMITS:
		for (int i = 0; i < size; i++) //could have used index instead of 24 but whatever. 
		{
			printf("%x ", data[i]);

		}
		printf("\n");

		break;


	}



	return true;
}

#else



bool Triangulator::TriangulatorSensorInterface::sendCommand(unsigned int cmd, unsigned char * data, unsigned int size)
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	//size is comming in as the size of the data set plus the command
	//ignore the command!  It is redundant in this case as it is already in the data.
//			memcpy((void*)(buff+1),data,size-1); //-1 to remove the cmd. THis is a hack. Don't know why I wrote this this way. But am supposed to just send an array to sensor. 

		
	if (pSerialPort->is_open())
	{


		return CEyeWrite(0x20, data, size);

		//if (!pSerialPort->write_some(boost::asio::buffer(data, size))) //-1 because that is how craig does it. size includes the cmd byte. I need to make sure I do the same for consitency
		//{
		//	
		//	boost::this_thread::sleep(boost::posix_time::milliseconds(RDS_SLEEP1));
		//	return false;
		//}
		//else
		//{
		//	dumpbin(data, size);
		//	boost::this_thread::sleep(boost::posix_time::milliseconds(RDS_SLEEP1));
		//	return true;
		//}

	}
}

#endif
void Triangulator::TriangulatorSensorInterface::setConfigFiles(std::string bFile, std::string eFile)
{
	useConfigFile = true;
	beaconFile = bFile;
	envFile = eFile;
	printf("using config files. Env:%s  Beacons:%s\n", envFile.c_str(), beaconFile.c_str());
}

//not really used except by the ros service
bool Triangulator::TriangulatorSensorInterface::getBestID()
{
	int				SizeScale, SizeS;			// drawing scales
	int				NumEntries;					// # of coordinate entries
	float			*pFlt;						// float casting pointer
	unsigned int	*pU32;						// U32 casting pointer
	float			ID, R, C, SS, AdjR, AdjC;	// entry data
	float			Theta, Phi;					// az/el angles (in rad)
	float			ObsErr;						// observation error (in rad)
	unsigned int	Status;						// status word
	bool			IsReflect;					// node is a reflection flag
	bool			IsUsedInEst;				// node is used to produce the state estimate flag
	bool			IsOvl;						// node is in the overlap region flag
	QString			IDStr;						// ID/SS strings
	int				SSHeight;					// SS rect height
//		QRect			SSRect;						// SS rect
	int				i;							// loop index
	int				NumCams;					// number of cameras (for seperator lines)
	int				CamDispNX;					// display columns per camera
	mvBestID.clear();

	bool b = readDataSet(TriangulatorSensorInterface::GET_BEST_BEACON, &m_DevData, &DSHdr);
	if (!b) return b;

	pU32 = (unsigned int *)m_DevData.m_Array;
	pFlt = (float *)m_DevData.m_Array;

	//pU32 = (unsigned int *)m_DevData.m_Array;
	//NumEntries = Size / 40;
	NumEntries = DSHdr.Size / 40; //40 is report size, TODO: turn this into enum


	for (i = 0; i < NumEntries; i++)
	{
		// get ID
		ID = pFlt[i * 10];

		// only print if ID is non-zero
		if (ID)
		{
			// unpack coordinate
			R = pFlt[i * 10 + 1];
			C = pFlt[i * 10 + 2];
			SS = pFlt[i * 10 + 3];
			Theta = pFlt[i * 10 + 4];
			Phi = pFlt[i * 10 + 5];
			AdjR = pFlt[i * 10 + 6];
			AdjC = pFlt[i * 10 + 7];
			ObsErr = pFlt[i * 10 + 8];
			Status = pU32[i * 10 + 9];
			IsReflect = ((Status & 0x04) != 0);
			IsUsedInEst = ((Status & 0x02) != 0);
			IsOvl = ((Status & 0x01) != 0);




#if 0
			printf(

				"1-->ID:%f "
				"AdjC:%f "
				"AdjR:%f "
				"C:%f "
				"IsOvl:%u "
				"IsReflect:%u "
				"IsUsedInEst:%u "
				"ObsErr:%f "
				"Phi:%f "
				"R:%f "
				"SS:%f "
				"Status:%d "
				"Theta:%f\n", //"------------------weq323-324-234------------------234234234-------------->%d",
				ID,
				AdjC,
				AdjR,
				C,
				IsOvl,
				IsReflect,
				IsUsedInEst,
				ObsErr,
				Phi,
				R,
				SS,
				Status,
				Theta);
#endif






			//printf("THETATEST##:%.4f\n");
			std::shared_ptr<BestIDMessage> p(new  BestIDMessage(ID, R, C, SS, Theta, Phi, AdjR, AdjC, ObsErr,
				Status, IsReflect, IsUsedInEst, IsOvl));

			//	 TriangulatorSensorInterface::BestIDMessage::testBestIDMessage(ID, (float)Theta);

		//	BestIDMessage bb(ID, Theta) ;
//cout<<"*1"<<endl;
			mvBestID.push_back(p);
			//cout<<"*2"<<endl;					

								//best.R = R;
								//best.C = C;
								//best.SS = SS;
								//best.Theta = Theta;
								//best.Phi = Phi;
								//best.AdjPtR = AdjR;
								//best.AdjPtC = AdjC;
								//best.ID = ID;
								//best.Status = Status;
		}

		//					ROSPubBestDetect->publish(best);

	}
	return true;
}

bool Triangulator::TriangulatorSensorInterface::getVoltage(float & mainPwr, float & usbPwr)
{
	vector <float> v;
	bool b = readDataSet(TriangulatorSensorInterface::GET_VOLTAGE, &m_DevData, &DSHdr);

	if (!b) return b;

	convertFloat32ToVector(m_DevData.m_Array, v, false, TriangulatorDSSizes::SIZE_VOLTAGE);
	mainPwr = v[0];
	usbPwr = v[1];
	//printf("v1:%.2f v2:%.2f\n", v[0], v[1]);

	return true;
}

void Triangulator::TriangulatorSensorInterface::startLocalizer()
{
	unsigned char			TxCmd[SG_CMD_MAX_SIZE];		// TX command
	TxCmd[0] = 20; //LSYS_CMD_USE_STATE_EST;
	TxCmd[1] = 1; //enables it

	CEyeWrite(0x20, TxCmd, 2);
	//sendCommand(TriangulatorDSCommands::ENABLE_LOCALIZATION, TxCmd, 2); //was 2 but changed to 3 since craig does this and I need to compensate for it in sendCOmmand
}

void Triangulator::TriangulatorSensorInterface::stopLocalizer()
{

	unsigned char			TxCmd[SG_CMD_MAX_SIZE];		// TX command
	TxCmd[0] = 20; //LSYS_CMD_USE_STATE_EST;
	TxCmd[1] = 0; //0 disables it
	sendCommand(TriangulatorDSCommands::ENABLE_LOCALIZATION, TxCmd, 2); //was 2 now 3 because craig is +1
}

Triangulator::LocalizeMessage Triangulator::TriangulatorSensorInterface::getLocalization()
{
	LocalizeMessage lm;
	readDataSet(TriangulatorSensorInterface::GET_LOCALIZATION, &m_DevData, &DSHdr);
	DynArrayToLocalizeMessage(m_DevData, DSHdr, lm);
	return lm;
}

unsigned char * Triangulator::TriangulatorSensorInterface::getBeaconSetMessage()
{
	toArrayEnv();
	toArray();
	return mData;
}

unsigned char * Triangulator::TriangulatorSensorInterface::getEnvLimitMessage()
{
	toArray();
	toArrayEnv();
	return mData2;
}

bool Triangulator::TriangulatorSensorInterface::sendBeaconSettings(bool fromFile/*=true*/)
{
	if (fromFile)
	{
		QString qstr = QString::fromStdString(beaconFile);
		return sendCommandFile(TriangulatorDSCommands::SET_BEACON_LIST, qstr);
	}
	else
		return sendCommand(TriangulatorDSCommands::SET_BEACON_LIST, getBeaconSetMessage(), TriangulatorDSSizes::SIZE_BEACON_LIST);
}

bool Triangulator::TriangulatorSensorInterface::sendEnvSettings(bool fromFile/*=false*/)
{
	if (fromFile)
	{
		QString qstr = QString::fromStdString(envFile);
		return sendCommandFile(TriangulatorDSCommands::SET_ENV_LIMITS, qstr);
	}
	else
		return sendCommand(TriangulatorDSCommands::SET_ENV_LIMITS, getEnvLimitMessage(), TriangulatorDSSizes::SIZE_ENV_LIMITS);
}

void Triangulator::TriangulatorSensorInterface::setEnv(float xplus, float xminus, float yplus, float yminus, float zplus, float zminus)
{
	envXPlus = xplus;
	envXMinus = xminus;
	envYMinus = yplus;
	envYMinus = yminus;
	envZPlus = zplus;
	envZMinus = zminus;
}

Triangulator::TriangulatorSensorInterface::~TriangulatorSensorInterface()
{
	if (pSerialPort) delete pSerialPort;
}

Triangulator::TriangulatorSensorInterface::TriangulatorSensorInterface(std::string port)
{
	m_port = port;
}

Triangulator::TriangulatorSensorInterface::TriangulatorSensorInterface()
{
	m_port.clear();
}

void Triangulator::TriangulatorSensorInterface::printArrays()
{
	toArrayEnv();
	printf("ENV:\n");

	for (int i = 0; i < 24; i++) //could have used index instead of 24 but whatever. 
	{
		printf("%x ", mData2[i]);

	}
	printf("\n");


	toArray(); //this will set index

	printf("BEACONS:\n");
	for (int i = 0; i < index; i++)
	{
		printf("%x ", mData[i]);

		if (i % 4 == 0)
		{
			printf("\n");

		}

		if (i % 16 == 0)
		{
			printf("----\n");
		}


	}
	printf("\n");
}

void Triangulator::TriangulatorSensorInterface::reset()
{
	index = 1;
	mBeacons.clear();
}

void Triangulator::TriangulatorSensorInterface::addBeacon(float ID, float x, float y, float z)
{
	std::shared_ptr<beacon> p(new  beacon(ID, x, y, z));
	mBeacons.push_back(p);
}

bool Triangulator::TriangulatorSensorInterface::openUART()
{
	if (m_port.empty())
		return false;

	openUART(m_port);
}

bool Triangulator::TriangulatorSensorInterface::openUART(std::string port)
{
	m_port = port;

	try
	{
		pSerialPort = new boost::asio::serial_port(m_io);

		boost::system::error_code ec;
		pSerialPort->open(port, ec);

		pSerialPort->set_option(boost::asio::serial_port_base::baud_rate(115200));
		pSerialPort->set_option(boost::asio::serial_port_base::character_size(8));
		pSerialPort->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
		pSerialPort->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
		pSerialPort->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

		return true;
	}
	catch (...)
	{

		printf("Serial port opening error. Does COM port exist?\n");
		return false;

	}
}

bool Triangulator::TriangulatorSensorInterface::toFloatArg(QString ArgStr, unsigned char * pCmd)
{
	//QString ArgStr = "3.14";
	float ArgValF;
	//unsigned char pCmd[4];
	int pCounter = 0;
	bool ValOK;

	ArgValF = ArgStr.toFloat(&ValOK);
	if (!ValOK)
	{
		std::cout << " Invalid argument!\n";
		return (false);
	}
	unsigned char * pU8 = (unsigned char *)&ArgValF;
	pCmd[pCounter] = *pU8;		pU8++;		pCounter++;
	pCmd[pCounter] = *pU8;		pU8++;		pCounter++;
	pCmd[pCounter] = *pU8;		pU8++;		pCounter++;
	pCmd[pCounter] = *pU8;		pU8++;		pCounter++;

	return true;
	//printf("%x %x %x %x", pCmd[0], pCmd[1], pCmd[2], pCmd[3]);
}

bool Triangulator::TriangulatorSensorInterface::closeUART()
{
	if (pSerialPort)
	{
		pSerialPort->close();

	}
	return true;
}

bool Triangulator::TriangulatorSensorInterface::SendSimpleFlowCmd(unsigned char Addr, unsigned char FlowCmd)
/******************************************************************************/
{
	unsigned char				TxMsg[5];						// TX message


																// form proceed packet
	TxMsg[0] = COMM_ESCAPE;
	TxMsg[1] = FlowCmd;
	TxMsg[2] = Addr;
	TxMsg[3] = COMM_ESCAPE;
	TxMsg[4] = COMM_FLOW_STOP;

	// write the message
	if (!pSerialPort->write_some(boost::asio::buffer(TxMsg, 5)))
	{

			cout << "fail 11 write\n";
		return false;

	}    //(FTWrite(TxMsg, 5));
	else
		return true;
}

bool Triangulator::TriangulatorSensorInterface::CEyeWrite(unsigned char Addr, unsigned char *Data, unsigned int DataSize)
/******************************************************************************/
{
	unsigned int                EscapeCount;                	// unintended escape character count
	unsigned int                i;              				// data index
	unsigned long				MsgSize;						// message size

	
																// scan message for unintended escape characters
	EscapeCount = 0;
	for (i = 0; i < DataSize; i++)
		if (Data[i] == COMM_ESCAPE)
			EscapeCount++;

	// allocate space for message
	MsgSize = 5 + DataSize + EscapeCount;
	if (!(m_TxBuf.AllocateAsNeeded(MsgSize)))
		return (false);

	// form message header for MOSI
	m_TxBuf.m_Array[0] = COMM_ESCAPE;
	m_TxBuf.m_Array[1] = COMM_FLOW_MOSI;
	m_TxBuf.m_Array[2] = Addr;

	// copy command message
	EscapeCount = 0;
	for (i = 0; i < DataSize; i++)
	{
		m_TxBuf.m_Array[3 + i + EscapeCount] = Data[i];

		// duplicate ESCs
		if (Data[i] == COMM_ESCAPE)
		{
			EscapeCount++;
			m_TxBuf.m_Array[3 + i + EscapeCount] = COMM_ESCAPE;
		}
	}

	// add message footer
	m_TxBuf.m_Array[3 + DataSize + EscapeCount] = COMM_ESCAPE;
	m_TxBuf.m_Array[4 + DataSize + EscapeCount] = COMM_FLOW_STOP;

	// write the message
	//return (FTWrite(m_TxBuf.m_Array, MsgSize)); //GREG1
	return (bool)pSerialPort->write_some(boost::asio::buffer(m_TxBuf.m_Array, MsgSize));


}