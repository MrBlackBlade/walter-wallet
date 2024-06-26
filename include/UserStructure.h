#pragma once

#include <map>
#include <unordered_map>
#include <list>
#include "Transaction.h"
using namespace std;

class Transaction;
class TransactionStructure;
class Bank;
class User;

class UserStructure
{
private:
	list<Admin> admins;
	map<string, Admin*> adminsByNameOrdered;
	unordered_map<string, Admin*> adminsByName;

	list<User> users;
	map<string, User*> usersByNameOrdered;
	unordered_map<string, User*> usersByName;

public:
	void insert(Admin* admin);
	void insert(User* user);

	void erase(Admin* admin);
	void erase(User* user);

	void modifyUser(User* user, User newUser);
	void modifyUser(User* user, const string username, const string displayName, double balance, const string phoneNumber, const string email, bool isSuspend);

	Admin* getAdmin(string username);
	vector<Admin*> getAdmins();

	User* getUser(string username);
	vector<User*> getUsers();
};

