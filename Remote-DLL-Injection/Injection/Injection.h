#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <sys/stat.h>
#include <iostream>

bool InjectDLL(const char* fullDllpath, DWORD processID);
