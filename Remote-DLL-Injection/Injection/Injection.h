#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <sys/stat.h>
#include <iostream>

/// <summary>
/// Injects a DLL into a target process
/// </summary>
/// <returns>true upon successful injection</returns>
bool InjectDLL(const char* fullDllpath, DWORD processID);
