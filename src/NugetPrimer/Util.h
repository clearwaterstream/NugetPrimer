#pragma once
#include <iostream>

using namespace std;

class Util
{
public:
	static wstring GetLastErrorMessage();
	static bool ExeCmd(wstring const &username, wstring const &domain, wstring const &password, wstring const &currentDir, wchar_t* commandLine);
	Util();
	~Util();
};

