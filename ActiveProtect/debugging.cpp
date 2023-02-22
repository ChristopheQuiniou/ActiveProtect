#include "pch.h"
#include "debuggin.h"

void allocateDebugConsole() {
    FILE* pFile = nullptr;

    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
}
