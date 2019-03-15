#include "pch.h"
#include "Util.h"
#include <filesystem>
namespace fs = std::filesystem;

wstring Util::GetLastErrorMessage()
{
	DWORD lastError = GetLastError();

	if (lastError == 0)
		return wstring();

	LPTSTR lpMsgBuf = nullptr;

	DWORD size = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		lastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	wstring errorMsg(lpMsgBuf, size);

	LocalFree(lpMsgBuf);

	return errorMsg;
}

wstring Util::GetCurrentDir()
{
	wchar_t exePathBuffer[MAX_PATH];
	GetModuleFileName(NULL, exePathBuffer, MAX_PATH);

	fs::path exePath(exePathBuffer);
	wstring currentDir = exePath.parent_path();

	return currentDir;
}

bool Util::ExeCmd(wstring const &username, wstring const &domain, wstring const &password, wstring const &currentDir, wchar_t* commandLine)
{
	PROCESS_INFORMATION processInfo = { 0 };
	STARTUPINFO startupInfo = { 0 };

	startupInfo.cb = sizeof(STARTUPINFO);
	
	BOOL result = CreateProcessWithLogonW(
		username.c_str(),
		domain.empty() ? NULL : domain.c_str(),
		password.c_str(),
		LOGON_WITH_PROFILE, // dwLogonFlags
		NULL, // lpApplicationName
		commandLine, // lpCommandLine,
		CREATE_UNICODE_ENVIRONMENT, // dwCreationFlags,
		NULL, // lpEnvironment,
		currentDir.c_str(), // lpCurrentDirectory
		&startupInfo,
		&processInfo);

	if (processInfo.hProcess != NULL)
		CloseHandle(processInfo.hProcess);

	if (processInfo.hThread != NULL)
		CloseHandle(processInfo.hThread);

	if (!result)
	{
		wstring errorMessage = Util::GetLastErrorMessage();

		wcerr << errorMessage.c_str() << endl;

		return false;
	}

	return true;
}

Util::Util()
{
}


Util::~Util()
{
}
