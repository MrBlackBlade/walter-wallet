#include "User.h"

User::User() : VirtualUser(0, "user", "user", "12345678", "xxxxxxxxxxxxxx", "Unknown") 
{ 
	this->balance = 0;
	this->isusbended = 0;
}

User::User
(
	int id,
	const string& name,
	const string& displayName,
	double balance,
	const string& password,
	const string& phoneNumber,
	const string& email
)
	: VirtualUser(id, name, displayName, password, phoneNumber, email)
{
	this->balance = balance;
	this->isusbended = 0;
	//this->accountState = accountState;
}

double User::getBalance() const { return balance; }

//string User::getAccountState() const { return accountState; }

string User::getUserType() const { return "user"; }

bool User::getSuspend()
{
	return isusbended;
}

list<Transaction*> User::getTransactions()
{
	return transactions;
}


void User::setSuspend(bool state)
{
	this->isusbended = state;
}

void User::setBalance(double balance) {	this->balance = balance; }

state User::send_money(string receiver_name, double amount, queue<Transaction>& system_transactions, map<std::string, User>& users)
{
	if (users.find(receiver_name) == users.end())
		return no_user_found;
	else if (amount > this->balance)
		return too_much_money;
	else
	{
		Transaction* newTrans = new Transaction(this->getUsername(), receiver_name, amount, std::chrono::system_clock::now(), accepted, transaction);
		Transaction::manage_transaction(newTrans, accepted, system_transactions, users);
	}
	return done;
}

state User::request_money(string reciepient_name, double amount, queue<Transaction>& system_transactions, map<std::string, User>& users)
{
	if (users.find(reciepient_name) == users.end())
		return no_user_found;
	else
	{
		Transaction* newTrans = new Transaction(this->getUsername(), reciepient_name, amount, std::chrono::system_clock::now(), pending, request);
		Transaction::manage_transaction(newTrans, pending, system_transactions, users);
	}
	return done;
}

state User::accept_request(Transaction* request, queue<Transaction>& system_transactions, map<std::string, User>& users)
{
	if (request->getAmount() > this->balance)
		return too_much_money;
	else
	{
		Transaction::manage_transaction(request, accepted, system_transactions, users);
	}
}

void User::reject_request(Transaction* request, queue<Transaction>& system_transactions, map<std::string, User>& users)
{
	Transaction::manage_transaction(request, accepted, system_transactions, users);
}

//void User::setAccountState(string& state) {	this->accountState = state; }


vector<string> User::toStringArray() const
{
	return
	{
		to_string(getID()),
		getUsername(),
		getPassword(),
		getDisplayName(),
		to_string(getBalance()),
		getPhoneNumber(),
		getEmail(),
		//getAccountState(),
		getUserType()
	};
}
