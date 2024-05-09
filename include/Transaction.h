#pragma once
#include "User.h"
#include <iostream>
#include <chrono>
#include <format>
using namespace std;
using namespace std::chrono;

class User;
class Admin;
class TransactionStructure;
class UserStructure;
class Bank;

// sender user , reciever user, amount , date , enum -1,0,1 , rejected, pending , accepted 
enum TransactionState
{
	pendingRequest = 0,
	rejectedRequest = 1,
	acceptedRequest = 2,
	completedTransaction = 3
};

class Transaction
{
	User* sender;
	User* recipient;
	double amount;
	time_point<system_clock> time;
	TransactionState flag;

	public:

	Transaction(User* sender, User* recipient, double amount, time_point<system_clock> time, TransactionState flag );

	void setSender(User* sender);
	void setRecipient(User* recipient);
	void setAmount(double amount);
	void setTime(time_point<system_clock> time);
	void setState(TransactionState flag);

	User* getSender();
	User* getRecipient();
	double getAmount();
	long getEpochTime();
	string getDisplayTime();
	TransactionState getState();

	vector<string> toStringArray();
};
