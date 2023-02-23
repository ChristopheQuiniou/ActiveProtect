#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

void initializeModuleScanner();
bool isUnauthorizedModulePresent();
void getProcessModules(DWORD processID, std::vector<std::wstring>* modulesFound);

