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
	User* user = new User(name, password, displayName, balance, phoneNumber, email, isSuspended);
	Bank::getUsers()->insert(user);
}

void Admin::deleteUser(User* user)
{
	for (Transaction* transaction : Bank::getTransactions()->get(user)) {
		if (transaction->getRecipient() == user) {
			transaction->setRecipient(Bank::getUsers()->getUser("deleteduser"));
		}
		else if (transaction->getSender() == user) {
			transaction->setSender(Bank::getUsers()->getUser("deleteduser"));
		}
	}
	Bank::getUsers()->erase(user);
}

void Admin::editUser(
	User* user,
	const string& newUsername,
	const string& newPassword,
	const string& newDisplayName,
	double newBalance,
	const string& newPhoneNumber,
	const string& newEmail,
	bool isSuspended
)
{
	User newUser = User(newUsername, newPassword, newDisplayName, newBalance, newPhoneNumber, newEmail, isSuspended);
	Bank::getUsers()->modifyUser(user, newUser);
}
void Admin::editUser(
	User* user,
	const string& newUsername,
	const string& newDisplayName,
	double		  newBalance,
	const string& newPhoneNumber,
	const string& newEmail,
	bool isSuspended
)
{
	Bank::getUsers()->modifyUser(user, newUsername, newDisplayName, newBalance, newPhoneNumber, newEmail, isSuspended);
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

bool Admin::operator==(const Admin& admin)
{
	if (this == &admin) {
		return true;
	}
	else {
		return false;
	}
}
