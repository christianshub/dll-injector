#include "Utility.h"
#include <iostream>

DWORD getProcessID(LPCSTR processName) 
{
	DWORD processID;
	HWND windowHandle = FindWindowA(nullptr, processName);
	GetWindowThreadProcessId(windowHandle, &processID);

	return processID;
}