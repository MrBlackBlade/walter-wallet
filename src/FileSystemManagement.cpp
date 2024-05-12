#include "FileSystemManagement.h"
#include "Bank.h"
const string FileSystemManagement::userFile = "resources\\users.txt";
const string FileSystemManagement::transactionFile = "resources\\transactions.txt";
fstream FileSystemManagement::file;


void FileSystemManagement::init()
{

}
vector<vector<string>> FileSystemManagement::readFile(string fileName)
{
	vector<vector<string>> table;
	string readLine;
	file.open(fileName, ios::in);
	while (getline(file, readLine))
	{
		vector<string> row;
		stringstream ss(readLine);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			row.push_back(substr);
		}
		table.push_back(row);

	}
	file.close();
	return table;
}
void FileSystemManagement::writeRow(string fileName, vector<string> row)
{
	string outputRow;
	int N = row.size();
	// Iterate over all the elements in arr[]
	for (int i = 0; i < N; i++) {
		outputRow += row[i];
		if (i < N - 1) {
			outputRow += ",";
		}

	}
	outputRow += "\n";
	file.open(fileName, ios::app);
	file << outputRow;
	file.close();
}

void FileSystemManagement::updateData() {
	file.open(userFile, ios::out);
	file.close();
	file.open(transactionFile, ios::out);
	file.close();
	for (User* user : Bank::getUsers()->getUsers())
	{
		FileSystemManagement::writeRow(FileSystemManagement::userFile, user->toStringArray());
	}
	for (Admin* admin : (Bank::getUsers()->getAdmins())) {
		FileSystemManagement::writeRow(FileSystemManagement::userFile, admin->toStringArray());
	}
	for (Transaction* transaction : Bank::getTransactions()->get()) {
		FileSystemManagement::writeRow(FileSystemManagement::transactionFile, transaction->toStringArray());
	}
}
