#include "pch.h"
#include "hacking_process_scanner.h"

std::vector<std::wstring> forbiddenWords;

void initializeForbiddenWords() {
	forbiddenWords = {
		L"cheat",
		L"cheat engine",
		L"debugger",
		L"disassembler",
		L"cheats",
		L"unkowncheats",
		L"aimbot",
		L"wallhack",
		L"hack",
		//L"injector",
		L"ida",
		L"reclass",
		L"x64dbg",
		L"x32dbg",
		L"x86dbg"
	};
}

bool isHackingProcessPresent() {
	std::vector<std::wstring> process;
	getActiveProcess(process);

	for (std::vector<std::wstring>::iterator iteratorProcessFounds = process.begin(); iteratorProcessFounds < process.end(); iteratorProcessFounds++) {
		for (std::vector<std::wstring>::iterator iteratorForbiddenWords = forbiddenWords.begin(); iteratorForbiddenWords < forbiddenWords.end(); iteratorForbiddenWords++) {
			if (iteratorProcessFounds->find(*iteratorForbiddenWords) != std::string::npos) {
				std::wcout << *iteratorProcessFounds << " is unauthorized " << std::endl;
				return true;
			}
		}
	}

	return false;
}

void toLower(std::wstring& str) {
	for (int i = 0; i < str.length(); i++)
		str.at(i) = std::tolower(str.at(i));
}

void getActiveProcess(std::vector<std::wstring> &processNames) {
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		std::cout << "Error while scanning the process" << std::endl;
		return;
	}
		

	PROCESSENTRY32W processEntry32W;
	ZeroMemory(&processEntry32W, sizeof(PROCESSENTRY32W));
	processEntry32W.dwSize = sizeof(PROCESSENTRY32W);
	std::wstring processName;

	if (Process32FirstW(handle, &processEntry32W)) {
		processName = processEntry32W.szExeFile;
		toLower(processName);
		
		processNames.push_back(processName);

		while (Process32NextW(handle, &processEntry32W)) {
			std::wstring processName = processEntry32W.szExeFile;
			toLower(processName);
			
			processNames.push_back(processName);
		}
		
	}
	else {
		std::cout << GetLastError() << std::endl;
	}

	CloseHandle(handle);
}
