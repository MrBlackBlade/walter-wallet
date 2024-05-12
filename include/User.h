#pragma once

#include "VirtualUser.h"
#include "Bank.h"
//#include "TransactionStructure.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction;
class TransactionStructure;
class Bank;

class User : public VirtualUser
{
private:

	double balance;
	bool isSuspended;
	//TransactionStructure transactions;

public:

	User
	(
		const string& name,
		const string& password,
		const string& displayName,
		double balance,
		const string& phoneNumber,
		const string& email,
		bool isSuspended
	);

	void editProfile(string displayName, string password, string phoneNumber, string email);

	void sendMoney(User* recipient, double amount);
	void requestMoney(User* sender, double amount);
	void acceptRequest(Transaction* transaction);
	void rejectRequest(Transaction* transaction);

	double getBalance() const;
	bool getSuspended() const;
	string getUserType() const;
	//TransactionStructure* getTransactions();

	void setBalance(double balance);
	void setSuspended(bool state);
	//void insertTransacton(Transaction* transaction);

	vector<string> toStringArray() const;

	bool operator==(const User& user);

};