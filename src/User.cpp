#include "User.h"

User::User(const int id, const string& name, string& displayName, double& balance, string& password, string& phoneNumber, const string& email, const string& userType, string& accountState)

{
	this->id = id;
	this->balance = balance;
	this->username = name;
	this->password = password;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->displayName = displayName;
	this->userType = userType;
	this->accountState = accountState;
}

int User::getID() const { return id; }

double User::getBalance() const { return balance; }

string User::getUsername() const { return username; }

string User::getPassword() const { return password; }

string User::getPhoneNumber() const { return phoneNumber; }

string User::getEmail() const { return email; }

string User::getDisplayName() const	{ return displayName; }

string User::getAccountState() const { return accountState; }

string User::getUserType() const { return userType; }


void User::setName(string& name) { this->username = name; }

void User::setPassword(string& password) { this->password = password; }

void User::setPhoneNumber(string& phonenumber) { this->phoneNumber = phoneNumber; }

void User::setEmail(string& email) { this->email = email; }

void User::setDisplayName(string& name) { this->displayName = name; }

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