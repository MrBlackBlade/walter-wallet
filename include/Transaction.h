#pragma once
#include "User.h"
#include <iostream>
#include <chrono>
#include <format>
using namespace std;
using namespace std::chrono;

// sender user , reciever user, amount , date , enum -1,0,1 , rejected, pending , accepted 
enum TransactionState
{
	rejected = -1,
	pending = 0,
	accepted = 1
};

class Transaction
{
	static int CountID;
	User* sender;
	User* reciever;
	double amount;
	time_point<system_clock> time;
	TransactionState flag;

	public:

	Transaction(User* sender, User* reciever, double amount, time_point<system_clock> time, TransactionState flag );

	void setSender(User* sender);
	void setReciever(User* reciever);
	void setAmount(double amount);
	void setTime(time_point<system_clock> time);
	void setFlag(TransactionState flag);

	User* getSender();
	User* getReciever();
	double getAmount();
	long int getEpochTime();
	string getDisplayTime();
	TransactionState getFlag();
};
