// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <thread>
#include <chrono> 
#include "modules_scanner.h"
#include "hacking_process_scanner.h"
#include "debuggin.h"


DWORD WINAPI run(HMODULE hModule) {
    //MessageBox(NULL, TEXT("This game is protected by Active Protect"),TEXT("Active Protect"), MB_OK);
#ifdef _DEBUG
    allocateDebugConsole();//TODO : removed for release
#endif

    initializeModuleScanner();
    initializeForbiddenWords();

    bool suspiciousActivity = false;
    while (!suspiciousActivity) {
#ifdef _DEBUG
        std::cout << "Active protect is scanning the game" << std::endl;
#endif

        if (isUnauthorizedModulePresent()) {
#ifdef _DEBUG
            MessageBox(NULL, TEXT("Active Protect : unauthorized module found in the game. Quitting."), TEXT("Active Protect"), MB_OK);
#endif
            exit(0);
        }
        
        if (IsDebuggerPresent()) {
#ifdef _DEBUG
            MessageBox(NULL, TEXT("Active Protect : a debugger was found on the game. Quitting."), TEXT("Active Protect"), MB_OK);
#endif
            exit(0);
        }

        if (isHackingProcessPresent()) {
#ifdef _DEBUG
            MessageBox(NULL, TEXT("Active Protect : unauthorized process is currently running. Quitting."), TEXT("Active Protect"), MB_OK);
#endif
            exit(0);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    FreeLibraryAndExitThread(hModule, 0);
    CloseHandle(hModule);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);
            HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run, NULL, 0, NULL);
            if (thread) {
                CloseHandle(thread);
            }
        }  
        case DLL_THREAD_ATTACH:

        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

