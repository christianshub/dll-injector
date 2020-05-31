#include <iostream>
#include <windows.h>
#include "Injection/Injection.h"
#include "Utility/Utility.h"
#include "Console/ConsoleColors.h"
#include "Config/Config.h"
#include "ConfigParser/ConfigParser.h"

int main() {

    ConsoleColors color;

    color.SetColor(White);

    std::cout << "\n=======================  REMOTE DLL INJECTION  =======================" << std::endl;

    //Create folder and ini file with content (if it doesn't exist)
    std::string configPath = VerifyINI("Injector", "config.ini", { "[Config]", "DLLs=", "msDelay=", "TargetProcess=" });
    std::cout << "ConfigPath:    " << configPath << std::endl;

    // Read .ini file 
    std::string DLLs = ReadKey("Config", "DLLs", configPath);
    std::string Delay = ReadKey("Config", "msDelay", configPath);
    std::string TargetProcess = ReadKey("Config", "TargetProcess", configPath);

    std::cout << "DLLs:          " << DLLs << std::endl;
    std::cout << "Delay (ms):    " << Delay << " (between each injection)" << std::endl;
    std::cout << "TargetProcess: " << TargetProcess << std::endl;

    std::cout << "======================================================================" << "\n" << std::endl;
    DWORD processID = getProcessID(TargetProcess.c_str());

    unsigned int delay = ParseDelay(Delay);

    // Parse config
    std::vector<std::string> dlls = ParseFileNames(DLLs);

    // Catch if no DLL's are given in the config.ini file:
    if (dlls.size() == 0) 
    {
        std::cout << "\nERROR MSG: No DLL names found in " << configPath << std::endl;

        color.SetColor(Red);
        std::cout << "\n[-] DLL injection: FAILED\n" << std::endl;
        color.SetColor(White);

        std::cout << "Exiting in 15 seconds..." << std::endl;
        Sleep(10000);
    
        return 1;
    }

    for (size_t i = 0; i < dlls.size(); i++) {
        
        if (InjectDLL(dlls[i].c_str(), processID)) {

            color.SetColor(Green);
            std::cout << "\n[+] SUCCESS injecting " << dlls[i] << std::endl;
            color.SetColor(White);
            Sleep(delay);
        }
        else
        {
            color.SetColor(Red);
            std::cout << "\n[+] FAILED injecting " << dlls[i] << std::endl;
            color.SetColor(White);

            std::cout << "Exiting in 15 seconds..." << std::endl;
            Sleep(10000);
        }
    }

   

    Sleep(5000);

    return 0;
}
