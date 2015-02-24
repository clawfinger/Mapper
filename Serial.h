#ifndef SERIAL_H
#define SERIAL_H
#include <windows.h>
#include <iostream>
#include <list>
#include <utility>
#include <cmath>

typedef std::list<std::pair<float, float>> pointList;

class Serial
{
private:
	HANDLE com_handle;
	COMSTAT status;
	DWORD errors;	
	pointList array;
public:
	Serial();
	~Serial();
	bool connected;
	void connect (const char* pName, int BoudRate);
	void disconnect();
	int writeLine(char* buff);
	int readLine(int* buff);
	int readLine(float* buff);
	void gatherData();
	pointList getData();
};

#endif
