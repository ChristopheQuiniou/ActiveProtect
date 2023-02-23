#include "pch.h"
#include "modules_scanner.h"

std::vector<std::wstring> authorizedModules;

DWORD processID;

void initializeModuleScanner() {
    authorizedModules = {
    L"ac_client.exe",
    L"ntdll.dll",
    L"KERNEL32.DLL",
    L"KERNELBASE.dll",
    L"WS2_32.dll",
    L"RPCRT4.dll",
    L"USER32.dll",
    L"win32u.dll",
    L"GDI32.dll",
    L"libvorbisfile.dll",
    L"gdi32full.dll",
    L"msvcp_win.dll",
    L"ucrtbase.dll",
    L"zlib1.dll",
    L"ADVAPI32.dll",
    L"msvcrt.dll",
    L"sechost.dll",
    L"SHELL32.dll",
    L"OPENGL32.dll",
    L"combase.dll",
    L"SDL2_image.dll",
    L"SDL2.dll",
    L"dbghelp.dll",
    L"IMM32.DLL",
    L"ole32.dll",
    L"OLEAUT32.dll",
    L"WINMM.dll",
    L"SETUPAPI.dll",
    L"GLU32.dll",
    L"VERSION.dll",
    L"dxcore.dll",
    L"OpenAL32.dll",
    L"libvorbis.dll",
    L"ogg.dll",
    L"shcore.dll",
    L"uxtheme.dll",
    L"MSCTF.dll",
    L"directxdatabasehelper.dll",
    L"kernel.appcore.dll",
    L"bcryptPrimitives.dll",
    L"clbcatq.dll",
    L"igxelpicd32.dll",
    L"SHLWAPI.dll",
    L"dwmapi.dll",
    L"dxgi.dll",
    L"igdml32.dll",
    L"igdgmm32.dll",
    L"DEVOBJ.dll",
    L"cfgmgr32.dll",
    L"WINTRUST.dll",
    L"CRYPT32.dll",
    L"MSASN1.dll",
    L"igc32.dll",
    L"powrprof.dll",
    L"UMPDC.dll",
    L"textinputframework.dll",
    L"CoreMessaging.dll",
    L"CoreUIComponents.dll",
    L"wintypes.dll",
    L"CRYPTBASE.DLL",
    L"libpng16 - 16.dll",
    L"libjpeg - 9.dll",
    L"winmmbase.dll",
    L"MMDevAPI.DLL",
    L"wdmaud.drv",
    L"ksuser.dll",
    L"AVRT.dll",
    L"AUDIOSES.DLL",
    L"msacm32.drv",
    L"MSACM32.dll",
    L"midimap.dll",
    L"dsound.dll",
    L"ResampleDmo.DLL",
    L"msdmo.dll",
    L"resourcepolicyclient.dll",
    L"wrap_oal.dll",
    L"Windows.UI.dll",
    L"ActiveProtect.dll",
    L"VCRUNTIME140.dll",
    L"MSVCP140.dll",
    L"TextShaping.dll",
    L"libpng16-16.dll",
    L"libjpeg-9.dll"
    };

    processID = GetCurrentProcessId();
}

bool isUnauthorizedModulePresent() {
    
    std::vector<std::wstring> modulesFound;
    getProcessModules(processID,&modulesFound);

    for (std::vector<std::wstring>::iterator itModuleFound = modulesFound.begin(); itModuleFound != modulesFound.end(); itModuleFound++)
        if (std::find(authorizedModules.begin(), authorizedModules.end(), *itModuleFound) == authorizedModules.end()) {
            std::wcout << *itModuleFound << " was not found in the authorized list of modules !" << std::endl;
            return true;
        }

    return false;
}

void getProcessModules(const DWORD processID,std::vector<std::wstring>* modulesFound) {
    
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    

    if (hsnap == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();
        std::cout << "Error while trying to get modules " << error << std::endl;
        return;
    }

    MODULEENTRY32W moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32W);
    BOOL moduleStatus = Module32FirstW(hsnap,&moduleEntry); 

    if (moduleStatus) {
        //std::wcout << "First module name : " << moduleEntry.szModule << std::endl;
        modulesFound->push_back(std::wstring(moduleEntry.szModule));
        do {
            moduleStatus = Module32NextW(hsnap, &moduleEntry);
            if (moduleStatus) {
                //std::wcout << "Next module name : " << moduleEntry.szModule << std::endl;
                modulesFound->push_back(std::wstring(moduleEntry.szModule));
            }
        } while (moduleStatus);
    } else {
        std::cout << "Error while trying to get the first module !" << std::endl;
    }

    CloseHandle(hsnap);
}

