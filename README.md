## Introduction 

Remote DLL injection works by injecting a DLL (the payload) on disk into a remote process that calls LoadLibrary (or the native LdrLoadDll), thereby forcing a DLL to be loaded in the context of that process. Once the remote process loads the DLL, the OS automatically calls the DLL’s DllMain function, which is defined by the creator of the DLL. This function contains the hack and has as much access to the system as theprocess in which it is running. 

## Step-by-step approach

- Step 1: Get the functionLoadLibraryA
- Step 2: Open the target process specified by the user of the injector
- Step 3: Allocate space for the DLL
- Step 4: Write the DLL location to the space we allocated in step 3
- Step 5: Launch the DLL usingLoadLibraryAfrom step 1
- Step 6: Close handles
