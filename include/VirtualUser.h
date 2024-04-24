#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class VirtualUser
{
private:

	int id;
	string username;
	string password;
	string displayName;
	string phoneNumber;
	string email;


public:

	VirtualUser
	(
		int id,
		const string& name,
		const string& password,
		const string& displayName,
		const string& phoneNumber,
		const string& email
	);

	int getID() const;
	string getUsername() const;
	string getPassword() const;
	string getPhoneNumber() const;
	string getEmail() const;
	string getDisplayName() const;
	virtual string getUserType() const;

	void setName(string& name);
	void setPassword(string& password);
	void setPhoneNumber(string& phonenumber);
	void setEmail(string& email);
	void setDisplayName(string& name);

	virtual vector<string> toStringArray() const = 0;
};

