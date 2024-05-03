#pragma once
#include "User.h"
#include <iostream>
#include<queue>
#include<map>
#include <chrono>
#include <format>
using namespace std;
using namespace std::chrono;

// sender user , receiver user, amount , date , enum -1,0,1 , rejected, pending , accepted 
enum TransactionState
{
	rejected = -1,
	pending = 0,
	accepted = 1
};

enum TransactionType
{
	transaction,
	request
};

class Transaction
{
	static int CountID;
	string sender;
	string receiver;
	int id;
	double amount;
	time_point<system_clock> time;
	TransactionState state;
	TransactionType type;
	inline const static double tax = 0.05;

public:

	Transaction();
	Transaction(string sender_username, string receiver_username, double amount, time_point<system_clock> time, TransactionState state, TransactionType type);

	string getSender();
	string getreceiver();
	int getID();
	double getAmount();
	long int getEpochTime();
	string getDisplayTime();
	TransactionState getstate();
	TransactionType getType();
	double get_tax();

	void setSender(string sender_username);
	void setreceiver(string receiver_username);
	void setAmount(double amount);
	void setTime(time_point<system_clock> time);
	void setstate(TransactionState state);
	void setType(TransactionType type);

	static void manage_transaction(Transaction* trans, TransactionState state, queue<Transaction>& all_transactions, map<string, User>& users);
};
