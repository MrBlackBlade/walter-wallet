#pragma once
#include<iostream>
#include"User.h"
#include"VirtualUser.h"
#include<map>
using namespace std;

class User;
class Transaction;
class TransactionStructure;
class UserStructure;
class Bank;

class Admin : public VirtualUser
{
public:

	Admin
	(
		const string& name,
		const string& password,
		const string& displayName,
		const string& phoneNumber,
		const string& email
	);

	string getUserType() const;

	void addUser
	(
		const string& name,
		const string& password,
		const string& displayName,
		double balance,
		const string& phoneNumber,
		const string& email,
		bool isSuspended
	);

	void deleteUser(User* user);

	void editUser(
		User* user,
		const string& newUsername,
		const string& newPassword,
		const string& newDisplayName,
		double newBalance,
		const string& newPhoneNumber,
		const string& newEmail,
		bool isSuspended
	);

	void suspendUser(User* user, bool isSuspended);

	vector<string> toStringArray() const;

};