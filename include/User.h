#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User
{
private:

	int id;
	double balance;
	string username;
	string displayName;
	string password;
	string phoneNumber;
	string email;
	string userType;
	string accountState;

public:

	User(const int id, const string& name, string& displayName, double& balance, string& password, string& phoneNumber, const string& email, const string& userType, string& accountState);

	int getID() const;
	double getBalance() const;
	string getUsername() const;
	string getPassword() const;
	string getPhoneNumber() const;
	string getEmail() const;
	string getDisplayName() const;
	string getAccountState() const;
	string getUserType() const;
	vector<string> toStringArray() const;

	//double setBalance(); Admin ?

	void setName(string& name);
	void setPassword(string& password);
	void setPhoneNumber(string& phonenumber);
	void setEmail(string& email);
	void setDisplayName(string& name);
	void setAccountState(string& state);

};