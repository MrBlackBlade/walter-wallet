#include "Transaction.h"
int Transaction::CountID = 0;

Transaction::Transaction(User* sender, User* reciever, double amount, time_point<system_clock> time, TransactionState flag)
{
	this->sender = sender;
	this->reciever = reciever;
	this->amount = amount;
	this->time = time;
	this->flag = flag;
	CountID++;
}

void Transaction::setSender(User* sender)
{
	this->sender = sender;
}

void Transaction::setReciever(User* reciever)
{
	this->reciever = reciever;
}

void Transaction::setAmount(double amount)
{
	this->amount = amount;
}

void Transaction::setTime(time_point<system_clock> time)
{
	this->time = time;
}

void Transaction::setFlag(TransactionState flag)
{
	this->flag = flag;
}

User* Transaction::getSender()
{
	return sender;
}

User* Transaction::getReciever()
{
	return reciever;
}

double Transaction::getAmount()
{
	return amount;
}

long int Transaction::getEpochTime()
{
	return static_cast<long int>(system_clock::to_time_t(time));
}
string Transaction::getDisplayTime()
{
	return format("{:%Y-%m-%d %X}", time);
}

TransactionState Transaction::getFlag()
{
	return flag;
}