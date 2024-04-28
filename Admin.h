#pragma once
#include<iostream>
#include"User.h"
#include"VirtualUser.h"
#include<map>
using namespace std;
class Admin : public VirtualUser
{
	string name;
	int id;

public:
	Admin(int id,
		const string& name,
		const string& displayName,
		double balance,
		const string& password,
		const string& phoneNumber,
		const string& email,
		const string& accountState);

	bool add_user
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
	);

	bool delete_user(string name, map<string, User> accounts);

	bool edit_user(string old_userame, string new_username, string new_password, double new_balancce, map<string, User> accounts);

	bool susbend_user(string name, map<string,User>&accounts);

	bool taxes();

};