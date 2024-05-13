#include "User.h"

User::User
(
	const string& name,
	const string& password,
	const string& displayName,
	double balance,
	const string& phoneNumber,
	const string& email,
	bool isSuspended
)
	: VirtualUser(name, password, displayName, phoneNumber, email)
{
	this->balance = balance;
	this->isSuspended = isSuspended;
}

void User::editProfile(string displayName, string password, string phoneNumber, string email)
{
	this->setDisplayName(displayName);
	this->setPassword(password);
	this->setPhoneNumber(phoneNumber);
	this->setEmail(email);
}

void User::sendMoney(User* recipient, double amount) {
	Bank::makeNewTransaction(this, recipient, amount, TransactionState::completedTransaction);
}

void User::requestMoney(User* sender, double amount) {
	Bank::makeNewTransaction(sender, this, amount, TransactionState::pendingRequest);
}

void User::acceptRequest(Transaction* transaction) {
	Bank::processRequest(transaction, TransactionState::acceptedRequest);
}

void User::rejectRequest(Transaction* transaction) {
	Bank::processRequest(transaction, TransactionState::rejectedRequest);
}
double User::getBalance() const { return balance; }

bool User::getSuspended() const { return isSuspended; }

string User::getUserType() const { return "user"; }

void User::setBalance(double balance) {	this->balance = balance; }

void User::setSuspended(bool state) {	this->isSuspended = state; }

vector<string> User::toStringArray() const
{
	return
	{
		getUserType(),
		getUsername(),
		getPassword(),
		getDisplayName(),
		to_string(getBalance()),
		getPhoneNumber(),
		getEmail(),
		(getSuspended() ? "true" : "false")
	};
}

bool User::operator==(const User& user)
{
	if (this == &user) {
		return true;
	}
	else {
		return false;
	}
}
