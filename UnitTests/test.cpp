#include "pch.h"
#include "..\Remote-DLL-Injection\Injection\Injection.h"

//  *************************************
//   Testing edge cases for the injector
//  *************************************

// Correct path to file?
TEST(DllPath, Invalid)
{
    char* path = "myDLL.dll";
    struct stat buffer;
    ASSERT_NE(stat(path, &buffer), 0);
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