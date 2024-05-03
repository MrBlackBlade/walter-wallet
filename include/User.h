#pragma once
#include "VirtualUser.h"
#include"Transaction.h"
#include<list>
#include<queue>
#include<map>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum state
{
	done,
	no_user_found = 0,
	too_much_money = 1
};

class User : public VirtualUser
{
private:

	double balance;
	bool isusbended;
	list<Transaction*> transactions;
	//list<Transaction*> sentRequests;
	//list<Transaction*> recievedRequests;
	//string accountState;

public:
	User();

	User
	(
		int id,
		const string& name,
		const string& displayName,
		double balance,
		const string& password,
		const string& phoneNumber,
		const string& email
	);

	double getBalance() const;
	string getUserType() const;
	bool getSuspend();
	list<Transaction*> getTransactions();
	//list<Transaction*> getSentRequests();
	//list<Transaction*> getRecievedRequests();

	//string getAccountState() const;

	void setSuspend(bool state);
	void setBalance(double balance);
	//void setAccountState(string& state);

	state send_money(string receiver_name, double amount, queue<Transaction>& system_transactions, map<std::string, User>& users);
	state request_money(string reciepient_name, double amount, queue<Transaction>& system_transactions, map<std::string, User>& users);
	state accept_request(Transaction* request, queue<Transaction>& system_transactions, map<std::string, User>& users);
	void reject_request(Transaction* request, queue<Transaction>& system_transactions, map<std::string, User>& users);

	vector<string> toStringArray() const;
};