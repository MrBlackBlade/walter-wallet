#include "Admin.h"
#include<map>
Admin::Admin(
	int id,
	const string& name,
	const string& displayName,
	double balance,
	const string& password,
	const string& phoneNumber,
	const string& email,
	const string& accountState) : VirtualUser(id, name, displayName, password, phoneNumber, email)
{
	this->name = name;
	this->id = id;
}

bool Admin::deleteUser(string name, map<string, User> accounts)
{
	if (accounts.find(name) == accounts.end())
	{
		return false;
	}

	else 
	{
		accounts.erase(name);
		return true;
	}
}

bool Admin::editUser(string old_username, string new_username, string new_password, double new_balance, map<string, User> accounts)
{
	if (accounts.find(old_username) != accounts.end())
	{
		auto new_key = accounts.extract(old_username);
		new_key.key() = new_username;
		accounts[new_username].setPassword(new_password);
		accounts[new_username].setBalance(new_balance);
	}
	else
		return false;
}

bool Admin::suspendUser(string name, map<string, User>& accounts)
{
	if (accounts.find(name) == accounts.end())
	{
		return false;
	}

	else
	{
		if(accounts[name].getSuspend() == false) {
			accounts[name].setSuspend(1);
			return true;
		}
		else
		{
			accounts[name].setSuspend(0);
			return true;
		}
			
	}
}

bool Admin::taxes()
{

	return false;
}

bool Admin::addUser
(
	int id,
	const string& name,
	const string& displayName,
	double balance,
	const string& password,
	const string& phoneNumber,
	const string& email,
	const string& accountState,
	map<string,User> Users
)
{
	if (Users.find(name) == Users.end())
	{
		User account = User(id, name, displayName, balance, password, phoneNumber, email, accountState);

		Users[name] = account;

		return true;
	}

	else
		return false;
}


