#include "Injection.h"

bool InjectDLL(const char* fullDllPath, DWORD processID)
{
    // Step 0: Check if file exists
    struct stat buffer;
    if (stat(fullDllPath, &buffer) != 0) 
    {
        std::cout << "\nERROR MSG: Could not find DLL file." << std::endl;
        return false;
    }

    // Step 1: Get the address of kernel32.dll's exported function: LoadLibraryA
    LPVOID loadLibrary = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    if (!loadLibrary)
    {
        std::cout << "\nERROR MSG: Could not get address kernel32.dll's LoadLibraryA." << std::endl;
        return false;
    }

    // Step 2: Get process handle from the target process
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
    if (!pHandle)
    {
        std::cout << "\nERROR MSG: Could not obtain handle from 'OpenProcess'" << std::endl;
        std::cout << "           - Is the target process running?" << std::endl;
        return false;
    }

    // Step 3: Allocate space to write the dll location
    LPVOID dllParamAddr = VirtualAllocEx(pHandle, 0, strlen(fullDllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!dllParamAddr)
    {
        CloseHandle(pHandle);
        std::cout << "\nERROR MSG: Could not write DLL location using 'VirtualAllocEx'" << std::endl;
        return false;

        return 1;
    }

    // Step 4: Write the dll location to the space we allocated in step 3
    BOOL writeMem = WriteProcessMemory(pHandle, dllParamAddr, fullDllPath, strlen(fullDllPath), NULL);
    if (!writeMem)
    {
        CloseHandle(pHandle);
        std::cout << "\nERROR MSG: Could not write to process memory using 'WPM'" << std::endl;
        return false;
    }

    // Step 5: Load the dll using LoadLibraryA from step 1
    HANDLE dllThreadHandle = CreateRemoteThread(pHandle, 0, 0, (LPTHREAD_START_ROUTINE)loadLibrary, dllParamAddr, 0, 0);
    if (!dllThreadHandle)
    {
        CloseHandle(pHandle);
        std::cout << "\nERROR MSG: Could not create a remote thread using 'CreateRemoteThread'" << std::endl;
        return false;
    }

    // Step 6: Close handles
    CloseHandle(dllThreadHandle);
    CloseHandle(pHandle);
    return true;
}