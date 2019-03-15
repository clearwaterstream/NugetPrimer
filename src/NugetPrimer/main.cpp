// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <boost/program_options.hpp>
#include "main.h"
#include "Util.h"
#include "NugetPrimer.h"
using namespace std;
namespace po = boost::program_options;

int wmain(int argc, wchar_t *argv[])
{	
	PrintTitle();

	po::variables_map argMap;
	
	bool parsed = ParseOptions(argMap, argc, argv);

	if (!parsed)
	{
		cout << "Press any key to exit...";

		cin.ignore();

		return 1;
	}

	wstringstream username, domain, password;

	username << argMap["username"].as<string>().c_str();
	
	if (argMap.count("domain"))
	{
		domain << argMap["domain"].as<string>().c_str();
	}
	
	password << argMap["password"].as<string>().c_str();

	wstring currentDir = Util::GetCurrentDir();

	wcout << "current directory is " << currentDir.c_str() << endl << endl;

	NugetPrimer primer;

	primer.Prime(username.str(), domain.str(), password.str(), currentDir);

	if (!argMap.count("silent"))
	{
		cout << "Press any key to exit...";

		cin.ignore();
	}

	return 0;
}

void PrintTitle()
{
	int consoleWidth = 80;
	string border(consoleWidth, '=');

	string title("DTCanada - OS User Profile Loader");

	cout << border << endl;
	cout << setw((consoleWidth / 2) + title.length() / 2) << right << title << endl;
	cout << border << endl << endl;
}

bool ParseOptions(po::variables_map& argMap, int argc, wchar_t *argv[])
{
	po::options_description desc("Options");
	
	try
	{
		desc.add_options()
			("username,u", po::value<std::string>()->required(), "OS Username")
			("domain,d", po::value<std::string>(), "Network domain. If not provided then local account is assumed")
			("password,p", po::value<std::string>()->required(), "OS Password")
			("silent,s", "Assume there is no user interaction involved. Good for using this in Jenkins, etc")
			("help,h", "Show program usage help");
		
		if (argc <= 1)
		{
			cout << desc << endl;
			return false;
		}

		po::store(po::parse_command_line(argc, argv, desc), argMap);
		po::notify(argMap);

		if (argMap.count("help")) {
			cout << desc << endl;
			return false;
		}
	}
	catch (po::required_option& e)
	{
		if (argMap.count("help")) {
			cout << desc << endl;
			return false;
		}

		cerr << e.what() << endl << endl;

		return false;
	}

	return true;
}