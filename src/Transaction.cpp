#include "Transaction.h"


Transaction::Transaction(User* sender, User* recipient, double amount, time_point<system_clock> time, TransactionState flag)
{
	this->sender = sender;
	this->recipient = recipient;
	this->amount = amount;
	this->time = time;
	this->flag = flag;
}

void Transaction::setSender(User* sender)
{
	this->sender = sender;
}

void Transaction::setRecipient(User* recipient)
{
	this->recipient = recipient;
}

void Transaction::setAmount(double amount)
{
	this->amount = amount;
}

void Transaction::setTime(time_point<system_clock> time)
{
	this->time = time;
}

void Transaction::setState(TransactionState flag)
{
	this->flag = flag;
}

User* Transaction::getSender()
{
	return sender;
}

User* Transaction::getRecipient()
{
	return recipient;
}

double Transaction::getAmount()
{
	return amount;
}

long Transaction::getEpochTime()
{
	return static_cast<long> (system_clock::to_time_t(time));
}
string Transaction::getDisplayTime()
{
	return format("{:%Y-%m-%d %X}", time);
}

TransactionState Transaction::getState()
{
	return flag;
}

vector<string> Transaction::toStringArray()
{
	return {
		to_string(getEpochTime()),
		(*sender).getUsername(),
		(*recipient).getUsername(),
		to_string(amount),
		to_string(flag)
	};
}