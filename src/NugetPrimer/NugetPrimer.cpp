#include "pch.h"
#include "NugetPrimer.h"
#include "Util.h"
using namespace std;

void NugetPrimer::Prime(wstring const &username, wstring const &domain, wstring const &password)
{	
	HANDLE phToken;
	
	int result = LogonUser(username.c_str(), domain.empty() ? NULL : domain.c_str(), password.c_str(), LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &phToken);

	if (result == 0)
	{
		wstring errorMessage = Util::GetLastErrorMessage();

		wcerr << errorMessage.c_str() << endl;

		return;
	}


}

NugetPrimer::NugetPrimer()
{
}


NugetPrimer::~NugetPrimer()
{
}
