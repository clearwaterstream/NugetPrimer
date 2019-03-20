#include "pch.h"
#include "NugetPrimer.h"
#include "Util.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void NugetPrimer::Prime(wstring const &username, wstring const &domain, wstring const &password, wstring const &currentDir)
{	
	DWORD usernameLength = UNLEN + 1;
	wchar_t usernameBuff[UNLEN + 1] = { 0 };

	BOOL result = GetUserName(usernameBuff, &usernameLength);

	if (result)
	{
		wcout << L"current username is " << usernameBuff << endl;
	}
	
	HANDLE hToken;
	
	result = LogonUser(username.c_str(), domain.empty() ? NULL : domain.c_str(), password.c_str(), LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken);

	if (hToken != NULL)
		CloseHandle(hToken);

	if (!result)
	{
		wstring errorMessage = Util::GetLastErrorMessage();

		wcerr << errorMessage.c_str() << endl;

		return;
	}

	wcout << "user " << username.c_str() << " logged in" << endl;

	wchar_t restorePkgCmd[] = L"nuget.exe restore -PackagesDirectory tmp";

	bool cmdResult = Util::ExeCmd(username, domain, password, currentDir, restorePkgCmd);

	if (cmdResult)
	{
		cout << "nuget packages restored" << endl;
	}

	wchar_t pushPkgCmd[] = L"nuget.exe push *.nupkg -Source dti";

	cmdResult = Util::ExeCmd(username, domain, password, currentDir, pushPkgCmd);

	if (cmdResult)
	{
		cout << "dummy nuget package pushed" << endl;
	}

	cout << endl;
}

NugetPrimer::NugetPrimer()
{
}


NugetPrimer::~NugetPrimer()
{
}
