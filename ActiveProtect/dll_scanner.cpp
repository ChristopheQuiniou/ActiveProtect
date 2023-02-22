#include "pch.h"
#include "dll_scanner.h"

void detectUnAllowedDll() {
    getDlls();
}

void getDlls() {
    DWORD pID = GetCurrentProcessId();
    std::cout << "Process id : " << std::hex << pID << std::endl;
    /*
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, );
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
             
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    */
}

