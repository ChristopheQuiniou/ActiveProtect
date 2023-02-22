// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <thread>
#include <chrono> 
#include "dll_scanner.h"
#include "debuggin.h"



void run() {
    MessageBox(NULL, TEXT("This game is protected by Active Protect"),TEXT("Active Protect"), MB_OK);
    allocateDebugConsole();

    while (true) {
        std::cout << "Active protect is scanning the game" << std::endl;

        detectUnAllowedDll();

       

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:

    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

