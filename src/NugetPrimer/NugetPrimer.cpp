#include "pch.h"
#include "NugetPrimer.h"
#include "Util.h"
using namespace std;

void NugetPrimer::Prime(wstring const &username, wstring const &domain, wstring const &password, wstring const &currentDir)
{	
	HANDLE hToken;
	
	BOOL result = LogonUser(username.c_str(), domain.empty() ? NULL : domain.c_str(), password.c_str(), LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken);

	if (hToken != NULL)
		CloseHandle(hToken);

	if (!result)
	{
		wstring errorMessage = Util::GetLastErrorMessage();

		wcerr << errorMessage.c_str() << endl;

		return;
	}

	wchar_t restorePkgCmd[] = L"nuget.exe restore -PackagesDirectory tmp";

	bool cmdResult = Util::ExeCmd(username, domain, password, currentDir, restorePkgCmd);

	if (cmdResult)
	{
		cout << "nuget packages restored" << endl << endl;
	}

	wchar_t pushPkgCmd[] = L"nuget.exe push *.nupkg -Source dti";

	cmdResult = Util::ExeCmd(username, domain, password, currentDir, restorePkgCmd);

	if (cmdResult)
	{
		cout << "dummy nuget package pushed" << endl << endl;
	}
}

NugetPrimer::NugetPrimer()
{
}


NugetPrimer::~NugetPrimer()
{
}
