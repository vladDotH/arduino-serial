#include "Connecter.h"



Connecter::Connecter()
{
}


Connecter::~Connecter()
{
}

void Connecter::connect(int portNum)
{
	stringstream sstr;
	string strPortNum;

	sstr << portNum;
	sstr >> strPortNum;

	string portName = "\\\\.\\COM";
	portName += strPortNum;

	port = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(port, &dcbSerialParams))
	{
		cout << "getting state error\n";
		return;
	}

	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(port, &dcbSerialParams))
	{
		cout << "error setting serial port state\n";
		return;
	}

	Sleep(1000);

	cout << "connected to port " << strPortNum;
}

void Connecter::write(string msg)
{
	DWORD iSize = 0;

	if (!WriteFile(port, msg.c_str(), msg.size(), &iSize, 0))
		cout << "Write error\n";

	FlushFileBuffers(port);
}

void Connecter::close()
{
	CloseHandle(port);
}
