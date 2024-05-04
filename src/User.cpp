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
	bool accountState
)
	: VirtualUser(id, name, password, displayName, phoneNumber, email)
{
	this->balance = balance;
	this->accountState = accountState;
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

bool User::getAccountState() const { return accountState; }

string User::getUserType() const { return "user"; }



//TransactionStructure* User::getTransactions() {
//	return &transactions;
//}

void User::setBalance(double balance) {	this->balance = balance; }

void User::setAccountState(bool state) {	this->accountState = state; }

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
		(getAccountState() ? "true" : "false"),
		getUserType()
	};
}
