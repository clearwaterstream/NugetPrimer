#include "pch.h"
#include "Util.h"

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


Util::Util()
{
}


Util::~Util()
{
}
