#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class FileSystemManagement
{
	static fstream file;

public:

	static const string userFile;
	static const string transactionFile;

	static void init();

	static vector<vector<string>> readFile(string fileName);

	static void writeRow(string fileName, vector<string> row);

};

