#include "User.h"

User::User(const int id, double& balance, const string& name, string& password, string& phoneNumber, const string& email)
{
	this->id = id;
	this->balance = balance;
	this->name = name;
	this->password = password;
	this->phoneNumber = phoneNumber;
	this->email = email;
}

int User::getID() const { return id; }

double User::getBalance() const { return balance; }

string User::getName() const { return name; }

string User::getPassword() const { return password; }

string User::getPhoneNumber() const { return phoneNumber; }

string User::getEmail() const { return email; }


void User::setName(string& name) { this->name = name; }

void User::setPassword(string& password) { this->password = password; }

void User::setPhoneNumber(string& phonenumber) { this->phoneNumber = phoneNumber; }

void User::setEmail(string& email) { this->email = email; }

vector<string> User::toStringArray() const
{
	return
	{
		to_string(getID()),
		to_string(getBalance()),
		getName(),
		getPassword(),
		getPhoneNumber(),
		getEmail()
	};
}