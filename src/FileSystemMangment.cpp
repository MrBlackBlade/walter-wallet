#include "FileSystemMangment.h"
const string FileSystemMangment::userFile = "user.txt";
const string FileSystemMangment::transactionFile = "transaction.txt";


void FileSystemMangment::init()
{
	
}
vector<vector<string>> FileSystemMangment::readFile(string fileName)
{
	vector<vector<string>> table;
	string readLine;
	file.open(fileName,ios::in); 
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
void FileSystemMangment::writeRow(string fileName, vector<string> row)
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
	file.open(fileName,ios::app);
	file << outputRow;


}
