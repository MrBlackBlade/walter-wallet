#include "VirtualUser.h"

VirtualUser::VirtualUser
(
	const string& name,
	const string& password,
	const string& displayName,
	const string& phoneNumber,
	const string& email
)

{
	this->username = name;
	this->password = password;
	this->displayName = displayName;
	this->phoneNumber = phoneNumber;
	this->email = email;

}


string VirtualUser::getUsername() const { return username; }

string VirtualUser::getPassword() const { return password; }

string VirtualUser::getPhoneNumber() const { return phoneNumber; }

string VirtualUser::getEmail() const { return email; }

string VirtualUser::getDisplayName() const { return displayName; }

string VirtualUser::getUserType() const { return "virtual"; }


void VirtualUser::setName(string name) { this->username = name; }

void VirtualUser::setPassword(string password) { this->password = password; }

void VirtualUser::setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; }

void VirtualUser::setEmail(string email) { this->email = email; }

void VirtualUser::setDisplayName(string name) { this->displayName = name; }