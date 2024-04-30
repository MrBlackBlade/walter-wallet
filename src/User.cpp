#include "User.h"

User::User
(
	int id,
	const string& name,
	const string& displayName,
	double balance,
	const string& password,
	const string& phoneNumber,
	const string& email,
	const string& accountState
)
	: VirtualUser(id, name, displayName, password, phoneNumber, email)
{
	this->balance = balance;
	this->accountState = accountState;
}

double User::getBalance() const { return balance; }

string User::getAccountState() const { return accountState; }

string User::getUserType() const { return "user"; }

void User::setBalance(double balance) {	this->balance = balance; }

void User::setAccountState(const string& state) {	this->accountState = state; }

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
