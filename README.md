## Introduction 

Remote DLL injection works by injecting a DLL (the payload) on disk into a remote process that calls `LoadLibrary` (or the native `LdrLoadDll`), thereby forcing a DLL to be loaded in the context of that process. Once the remote process loads the DLL, the OS automatically calls the DLL’s `DllMain` function, which is defined by the creator of the DLL. This function contains the hack and has as much access to the system as the process in which it is running. 

## Operation system, project, etc.

- IDE: Visual Studio 2019 (x86 project).
- OS: Windows 10, version 1909.
- Unit test framework: https://github.com/google/googletest

## Setup

1. Compile the source code
2. Run it one time - a folder and a `config.ini` file should be created on your desktop.
3. Navigate to `Desktop/Injector/config.ini`.
4. Fill in info about your payload path.
5. Fill in info about your target process' window name.
6. Execute Remote-DLL-Injector.exe.

## Snapshots

### Successful injection

<img src="https://github.com/christianshub/DLL-Injector/blob/master/Snapshots/Success.png" height="300" width="600">

### Failed injection: No target process open

<img src="https://github.com/christianshub/DLL-Injector/blob/master/Snapshots/Fail1.png" height="300" width="600">

### Failed injection: No DLL(s) inserted into config.ini:

<img src="https://github.com/christianshub/DLL-Injector/blob/master/Snapshots/Fail2.png" height="300" width="600">



## Creation approach

- Step 1: Get the function, `LoadLibraryA`
- Step 2: Open the target process specified by the user of the injector
- Step 3: Allocate space for the DLL
- Step 4: Write the DLL location to the space we allocated in step 3
- Step 5: Launch the DLL using `LoadLibraryA` from step 1
- Step 6: Close handles

## References


- Practical Malware Analysis, M. Sikorski and A. Honig, 2012, No Starch Press, ISBN: 978-1-59327-290-6, p. 254-257
