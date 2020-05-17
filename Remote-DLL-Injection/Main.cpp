#include <iostream>
#include <windows.h>
#include "Injection.h"
#include "Utility.h"
#include "ConsoleColors.h"
#include "Config.h"

int main() {

    Config config("\\config.ini");
    ConsoleColors color;

    color.SetColor(White);

    char fullDllPath[MAX_PATH];
    char processName[MAX_PATH];

    config.GetSetting(fullDllPath, "Config", "PayloadPath");
    config.GetSetting(processName, "Config", "TargetProcess");

    std::cout << "--- CONFIG.INI ---\n" << std::endl;
    std::cout << "Config.ini path:  " << config.path << std::endl;
    std::cout << "Payload path:     " << fullDllPath << std::endl;
    std::cout << "Taget process:    " << processName << std::endl;

    DWORD processID = getProcessID(processName);

    std::cout << "\n--- REMOTE DLL INJECTION ---\n" << std::endl;
    if (!InjectDLL(fullDllPath, processID)) {
        color.SetColor(Green);
        std::cout << "[+] DLL injection: SUCCESS\n" << std::endl;
    }
    else {
        color.SetColor(Red);
        std::cout << "[-] DLL injection: FAILED\n" << std::endl;
    }

    color.SetColor(White);

    std::cout << "Exiting in 30 seconds..." << std::endl;
    Sleep(30000);
    return 0;
}
