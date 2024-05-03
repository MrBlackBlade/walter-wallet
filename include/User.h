#pragma once

#include "VirtualUser.h"
//#include "Transaction.h"
//#include "TransactionStructure.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User : public VirtualUser
{
private:

	double balance;
	string accountState;
	//TransactionStructure transactions;

public:

	User
	(
		int id,
		const string& name,
		const string& password,
		const string& displayName,
		double balance,
		const string& phoneNumber,
		const string& email,
		const string& accountState
	);

	double getBalance() const;
	string getAccountState() const;
	string getUserType() const;
	//TransactionStructure* getTransactions();

	void setBalance(double balance);
	void setAccountState(string& state);
	//void insertTransacton(Transaction* transaction);

	vector<string> toStringArray() const;

};