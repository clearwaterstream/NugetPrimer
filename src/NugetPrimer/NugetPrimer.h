#pragma once
#include <iostream>
using namespace std;

class NugetPrimer
{
public:
	void Prime(wstring const &username, wstring const &domain, wstring const &password, wstring const &currentDir);
	NugetPrimer();
	~NugetPrimer();
};
