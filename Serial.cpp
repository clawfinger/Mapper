#include "stdafx.h"
#include "Serial.h"



using namespace std;
Serial::Serial()
{
	connected = false;
};
Serial::~Serial()
{
	if(this->connected)
		this->disconnect();
};

void Serial::connect(const char* pName, int BoudRate)				
{
		com_handle = CreateFile ( L"COM3",								//Creating handle. Opening COM port
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if(com_handle == INVALID_HANDLE_VALUE)
		{
			cout << "Cant connect to device. COM port open failure" << endl;
			return;

		}
		else
		{
			//cout << "Connection established" << endl;							//Debug line
			this->connected = true;
		}
		
		DCB dcbParam;

		if(!GetCommState(com_handle, &dcbParam))
		{
			cout << "GetCommState failure" << endl;								//Debug line
			return;
		}
		else 
			cout << "GetComState success" << endl;								//Setting DCB options
		dcbParam.BaudRate=BoudRate;										
		dcbParam.ByteSize=8;
		dcbParam.StopBits=ONESTOPBIT;
		dcbParam.Parity=NOPARITY;

		if(!SetCommState(com_handle, &dcbParam))								//Setting COM properties
		{
			cout << "SetComState failure" << endl;
			return;
		}
		else
			cout << "SetComState success" << endl;

	}
void Serial::disconnect()														//Disconnection. Handle release.
{
	if(this->connected)
	{
		CloseHandle(com_handle);
		connected = false;
	}
}
int Serial::writeLine(char* buff)												//Sending bytes to port
{
	DWORD BytesSend;
	if(!WriteFile(this->com_handle , (void*)buff , sizeof(buff) , &BytesSend , 0))
	{
		cout<< "Write failure";
	}
	return BytesSend;
	
}
int Serial::readLine(int* buff)													//Reading Int from port
{
	
	DWORD BytesRead = 0;
	do
	{
		ClearCommError(this->com_handle, &this->errors, &this->status);
		
	}
	while(status.cbInQue == 0);
	ReadFile(com_handle , (void*)buff , 2 , &BytesRead, 0);
	return BytesRead;

}

int Serial::readLine(float* buff)													//Reading float from port
{

	DWORD BytesRead = 0;
	do
	{
		ClearCommError(this->com_handle, &this->errors, &this->status);

	}
	while(status.cbInQue == 0);
	ReadFile(com_handle , (void*)buff , 4 , &BytesRead, 0);
	return BytesRead;

}

void Serial::gatherData()															//Starting scan and reading port for new data
{
	int angle = 0;
	float range = 0;
	float x_coord = 0;
	float y_coord = 0;
	char start = 's';
	float dergeesToRadians = 3.14159265 / 180;
	this->writeLine(&start);														//Sending 's' to start scanning sequence
	for(int i = 0; i < 170; i++)
	{
		this->readLine(&angle);														//Reading Int for angle
		this->readLine(&range);														//Reading float for range
		if(range > 1000)
		{
			x_coord = 0;
			y_coord = 0;
		}
		else
		{
			x_coord = cos(angle*dergeesToRadians)*range;							//Converting range and angle to coordinates
			y_coord = -sin(angle*dergeesToRadians)*range;
		}
		
		
		array.push_back(pair<float, float>(x_coord, y_coord));						//Filling array
	}

}

pointList Serial::getData()
{
	return array;
}


