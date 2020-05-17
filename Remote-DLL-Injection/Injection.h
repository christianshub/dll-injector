#pragma once
#include <Windows.h>
#include <TlHelp32.h>

DWORD InjectDLL(const char* fullDllpath, DWORD processID);
