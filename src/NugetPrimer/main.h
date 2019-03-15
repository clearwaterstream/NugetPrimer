#pragma once
namespace po = boost::program_options;

bool ParseOptions(po::variables_map& argMap, int argc, wchar_t *argv[]);
void PrintTitle();
