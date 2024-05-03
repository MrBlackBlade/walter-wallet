#pragma once
#include<iostream>
#include"VirtualUser.h"
#include"User.h"
#include<map>
using namespace std;
class Admin : public VirtualUser
{
	/*string name;
	int id;*/

public:

	Admin
	(
		int id,
		const string& name,
		const string& displayName,
		double balance,
		const string& password,
		const string& phoneNumber,
		const string& email,
		const string& accountState
	);

	/*bool addUser
	(
		int id,
		const string& name,
		const string& displayName,
		double balance,
		const string& password,
		const string& phoneNumber,
		const string& email,
		const string& accountState,
		map<string, User>Users
	);*/

	bool deleteUser(string name, map<string, User> accounts);

	//bool editUser(string old_userame, string new_username, string new_password, double new_balancce, map<string, User> accounts);

	bool toggleUserState(User* user);

	bool taxes();

};