#include "Injection.h"
#include <iostream>

DWORD InjectDLL(const char* fullDllPath, DWORD processID)
{
    // Step 1: Get the address of kernel32.dll's exported function: LoadLibraryA
    LPVOID loadLibrary = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    if (!loadLibrary)
    {
        return 1;
    }

    // Step 2: Get process handle from the target process
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
    if (!pHandle)
    {
        return 1;
    }

    // Step 3: Allocate space to write the dll location
    LPVOID dllParamAddr = VirtualAllocEx(pHandle, 0, strlen(fullDllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!dllParamAddr)
    {
        CloseHandle(pHandle);
        return 1;
    }

    // Step 4: Write the dll location to the space we allocated in step 3
    BOOL writeMem = WriteProcessMemory(pHandle, dllParamAddr, fullDllPath, strlen(fullDllPath), NULL);
    if (!writeMem)
    {
        CloseHandle(pHandle);
        return 1;
    }

    // Step 5: Load the dll using LoadLibraryA from step 1
    HANDLE dllThreadHandle = CreateRemoteThread(pHandle, 0, 0, (LPTHREAD_START_ROUTINE) loadLibrary, dllParamAddr, 0, 0);
    if (!dllThreadHandle)
    {
        CloseHandle(pHandle);
        return 1;
    }

    // Step 6: Close handles
    CloseHandle(dllThreadHandle);
    CloseHandle(pHandle);
    return 0;
}
