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


void User::editProfile(string displayName, string password, string phoneNumber, string email)
{
	this->setDisplayName(displayName);
	this->setPassword(password);
	this->setPhoneNumber(phoneNumber);
	this->setEmail(email);
}

void User::setBalance(double balance) {	this->balance = balance; }

void User::setAccountState(string& state) {	this->accountState = state; }


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
