#include "User.h"

User::User
(
	int id,
	const string& name,
	const string& password,
	const string& displayName,
	double balance,
	const string& phoneNumber,
	const string& email,
	const string& accountState
)
	: VirtualUser(id, name, password, displayName, phoneNumber, email)
{
	this->balance = balance;
	this->accountState = accountState;
}

double User::getBalance() const { return balance; }

string User::getAccountState() const { return accountState; }

string User::getUserType() const { return "user"; }

//TransactionStructure* User::getTransactions() {
//	return &transactions;
//}

void User::setBalance(double balance) {	this->balance = balance; }

void User::setAccountState(string& state) {	this->accountState = state; }

//void User::insertTransacton(Transaction* transaction) {
//	transactions.insert(transaction);
//}


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
		getAccountState(),
		getUserType()
	};
}
