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
	string name;
	string password;
	string phoneNumber;
	string email;

public:

	User(const int id, double& balance, const string& name, string& password, string& phoneNumber, const string& email);

	int getID() const;
	double getBalance() const;
	string getName() const;
	string getPassword() const;
	string getPhoneNumber() const;
	string getEmail() const;
	vector<string> toStringArray() const;

	//double setBalance(); Admin ?

	void setName(string& name);
	void setPassword(string& password);
	void setPhoneNumber(string& phonenumber);
	void setEmail(string& email);
};