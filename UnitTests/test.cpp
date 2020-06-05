#include "..\Remote-DLL-Injection\Injection\Injection.h"
#include "gtest/gtest.h"

//  ***********************************
//  Testing edge cases for the injector
//  ***********************************

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                std::cout << modEntry.szModule << std::endl;
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

// Correct path to file?
TEST(DllPath, Invalid)
{
    DWORD procId = GetCurrentProcessId();
    GetModuleBaseAddress(procId, L"");
    std::cout << procId << std::endl;
    
    std::cout << std::hex << procId << std::endl;

    char* path = "myDLL.dll";
    struct stat buffer;
    ASSERT_NE(stat(path, &buffer), 0);

    Sleep(5000);
    procId = GetCurrentProcessId();
    GetModuleBaseAddress(procId, L"");
    std::cout << procId << std::endl;
}
TEST(DllPath, Valid)
{
    char* path = "C:\\Windows"; // navigate to windows folder
    struct stat buffer;
    ASSERT_EQ(stat(path, &buffer), 0);
}

// Does LoadLibraryA retrieve a valid address?
TEST(LoadLib, NotZero)
{
    ASSERT_NE((int) GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"), 0);
}

// Catch invalid PIDs?
TEST(Handle, Invalid)
{
    DWORD processID = -1;
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);

    ASSERT_EQ((int) pHandle, 0);
  
    EXPECT_TRUE(true);
}