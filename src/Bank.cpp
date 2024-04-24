#include "Bank.h"
#include "FileSystemManagement.h"

unordered_map<string, User> Bank::users;

void Bank::init() {
	makeUsers();
}

void Bank::makeUsers() {
	vector<vector<string>> usersTable = FileSystemManagement::readFile(FileSystemManagement::userFile);
	for (vector<string> row : usersTable) {
		User user = User(
			stoi(row[0]),
			row[1],
			row[2],
			row[3],
			stod(row[4]),
			row[5],
			row[6],
			row[7]
		);
		users.insert(make_pair(user.getUsername(), user));
	}

}
unordered_map<string, User> Bank::getUsers() {
	unordered_map<string, User> users;
	return users;
}