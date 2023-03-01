#pragma once
#include <vector>
#include <tlhelp32.h>
#include <string>
#include <iterator>
#include <iostream>


void initializeForbiddenWords();

bool isHackingProcessPresent();

void toLower(std::wstring& str);

void getActiveProcess(std::vector<std::wstring> & processNames);