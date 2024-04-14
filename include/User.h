#pragma once

#include "VirtualUser.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User : public VirtualUser
{
private:

	double balance;
	string accountState;

public:

	User
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

	double getBalance() const;
	string getAccountState() const;
	string getUserType() const;

	void setBalance(double balance);
	void setAccountState(string& state);

	vector<string> toStringArray() const;

};