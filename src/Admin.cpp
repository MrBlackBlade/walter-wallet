#include "Admin.h"
#include "Bank.h"
#include<map>

Admin::Admin
(
	const string& name,
	const string& password,
	const string& displayName,
	const string& phoneNumber,
	const string& email
)
	: VirtualUser(name, password, displayName, phoneNumber, email)
{

}

string Admin::getUserType() const { return "admin"; }

void Admin::addUser
(
	const string& name,
	const string& password,
	const string& displayName,
	double balance,
	const string& phoneNumber,
	const string& email,
	bool isSuspended
)
{
	User user = User(name, password, displayName, balance, phoneNumber, email, isSuspended);
	Bank::getUsers()->insert(make_pair(user.getUsername(), user));
}

void Admin::deleteUser(User* user)
{
	for (Transaction* transaction : Bank::getTransactions()->get(user)) {
		if (transaction->getRecipient() == user) {
			transaction->setRecipient(&Bank::getUsers()->at("deleteduser"));
		}
		else if (transaction->getSender() == user) {
			transaction->setSender(&Bank::getUsers()->at("deleteduser"));
		}
	}
	Bank::getUsers()->erase(user->getUsername());
}

void Admin::editUser(
	User* user,
	const string& newUsername,
	const string& newPassword,
	const string& newDisplayName,
	double newBalance,
	const string& newPhoneNumber,
	const string& newEmail
)
{
	auto new_key = Bank::getUsers()->extract(user->getUsername());
	new_key.key() = newUsername;
	user->editProfile(newDisplayName, newPassword, newPhoneNumber, newEmail);
	user->setBalance(newBalance);

}

void Admin::suspendUser(User* user, bool isSuspended)
{
	user->setSuspended(isSuspended);
}

vector<string> Admin::toStringArray() const
{
	return
	{
		getUserType(),
		getUsername(),
		getPassword(),
		getDisplayName(),
		getPhoneNumber(),
		getEmail()
	};
}
