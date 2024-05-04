#pragma once

#include "VirtualUser.h"
#include "Bank.h"
//#include "TransactionStructure.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Transaction;

class User : public VirtualUser
{
private:

	double balance;
	bool accountState;
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
		bool accountState
	);

	void editProfile(string displayName, string password, string phoneNumber, string email);

	void sendMoney(User* recipient, double amount);
	void requestMoney(User* sender, double amount);
	void acceptRequest(Transaction* transaction);
	void rejectRequest(Transaction* transaction);

	double getBalance() const;
	bool getAccountState() const;
	string getUserType() const;
	//TransactionStructure* getTransactions();

	void setBalance(double balance);
	void setAccountState(bool state);
	//void insertTransacton(Transaction* transaction);

	vector<string> toStringArray() const;

};