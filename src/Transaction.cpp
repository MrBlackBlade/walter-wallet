#include "Transaction.h"
int Transaction::CountID = 0;

Transaction::Transaction()
{
}

Transaction::Transaction(string sender, string receiver, double amount, time_point<system_clock> time, TransactionState state, TransactionType type)
{
	this->sender = sender;
	this->receiver = receiver;
	this->id = CountID;
	this->amount = amount;
	this->time = time;
	this->state = state;
	this->type = type;
	CountID++;
}

void Transaction::setSender(string sender)
{
	this->sender = sender;
}

void Transaction::setreceiver(string receiver)
{
	this->receiver = receiver;
}

void Transaction::setAmount(double amount)
{
	this->amount = amount;
}

void Transaction::setTime(time_point<system_clock> time)
{
	this->time = time;
}

void Transaction::setstate(TransactionState state)
{
	this->state = state;
}

void Transaction::setType(TransactionType type)
{
	this->type = type;
}


string Transaction::getSender()
{
	return sender;
}

string Transaction::getreceiver()
{
	return receiver;
}

int Transaction::getID()
{
	return id;
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

TransactionState Transaction::getstate()
{
	return state;
}

TransactionType Transaction::getType()
{
	return type;
}

double Transaction::get_tax()
{
	return tax;
}

void Transaction::manage_transaction(Transaction* trans, TransactionState state, queue<Transaction>& all_transactions, map<string, User>& users)
{
	User* sender = &users[trans->getSender()];
	User* receiver = &users[trans->getreceiver()];

	double amount_before_tax = trans->getAmount();
	double amount_after_tax = amount_before_tax * (1 - tax);

	if (trans->getType() == transaction)
	{
		sender->setBalance(sender->getBalance() - amount_before_tax);
		receiver->setBalance(receiver->getBalance() + amount_after_tax);
		all_transactions.push(*trans);
		sender->getTransactions().push_back(trans);
		receiver->getTransactions().push_back(trans);
	}
	else if (trans->getType() == request && state == pending)
	{
		all_transactions.push(*trans);
		sender->getTransactions().push_back(trans);
		receiver->getTransactions().push_back(trans);
	}
	else if (trans->getType() == request && state == accepted)
	{
		receiver->setBalance(receiver->getBalance() - amount_before_tax);
		sender->setBalance(sender->getBalance() + amount_after_tax);
		trans->setstate(accepted);
	}
	else if (trans->getType() == request && state == rejected)
	{
		trans->setstate(rejected);
	}
}