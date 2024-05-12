#include "Validation.h"
#include <regex>
bool Validation::usernameValid(string name)
{
	if
		(
			usernameValidCharacterSet(name)
			&& usernameValidLength(name)
			&& usernameAvailable(name)
		)
		return true;
	else
		return false;
}
bool Validation::usernameAvailable(string name)
{
	bool userExists = false;

	if (Bank::getUsers()->getUser(name) != 0) {
		userExists = true;
	}
	if (Bank::getUsers()->getAdmin(name) != 0) {
		userExists = true;
	}

	return !userExists;

}
bool Validation::usernameValidLength(string name)
{
	if (regex_match(name, regex(R"(^.{3,16}$)")))
		return true;
	else
		return false;
}
bool Validation::usernameValidCharacterSet(string name)
{
	if (regex_match(name, regex(R"(^[a-zA-Z0-9]+([_\-]?[a-zA-Z0-9]+)*$)")))
		return true;
	else
		return false;
}


bool Validation::passwordValid(string name)
{
	if
		(
			passwordValidLength(name)
			&& passwordValidCase(name)
			&& passwordValidCharacterSet(name)
			&& passwordContainsNumbers(name)
			&& passwordContainsSpecialCharacters(name)
		)
		return true;
	else
		return false;
}
bool Validation::passwordValidLength(string password)
{
	if (regex_match(password, regex(R"(^.{8,32}$)")))
		return true;
	else
		return false;
}
bool Validation::passwordValidCase(string password)
{
	if (regex_match(password, regex(R"(^(?=.*[A-Z])(?=.*[a-z]).*$)")))
		return true;
	else
		return false;
}

bool Validation::passwordValidCharacterSet(string password)
{
	if (regex_match(password, regex(R"(^[a-zA-Z0-9~!@#$%^&*:;()<>_-]+$)")))
		return true;
	else
		return false;
}

bool Validation::passwordContainsNumbers(string password)
{
	if (regex_match(password, regex(R"(^(?=.*\d).*$)")))
		return true;
	else
		return false;
}

bool Validation::passwordContainsSpecialCharacters(string password)
{
	if (regex_match(password, regex(R"(^(?=.*[~!@#$%^&*:;()<>_-]).*$)")))
		return true;
	else
		return false;
}

bool Validation::displayNameValid(string name) {
	if (regex_match(name, regex(R"(^([a-zA-Z])+([ -]?[a-zA-Z]+)*$)")))
		return true;
	else
		return false;
}


bool Validation::emailValidFormat(string email)
{
	// Ensures that email match the format: something@example.com |.net |.edu |.org |.gov |.mil
	if (regex_match(email, regex(R"(^(\w+)(\.\w+)*@(\w+)(\.(asu\.edu\.eg|com|net|edu|gov|mil|org))+$)")))
		return true;
	else
		return false;
}

bool Validation::phoneNumberValidFormat(string phoneNumber)
{
	// Ensures that the phone number
	/*
	* Consists of exactly 11 digit
	* Starts with 010|011|012|015
	*/
	if (regex_match(phoneNumber, regex (R"(^(010|011|012|015)\d{8}$)")))
		return true;
	else
		return false;
}

bool Validation::initialBalanceValid(string balance) {
	double initialBalance;
	
	try
	{
		initialBalance = stod(balance);
		if (initialBalance > 0 && initialBalance <= 50000) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (const exception&)
	{
		return false;
	}
}
bool Validation::balanceValid(string balance) {
	double initialBalance;

	try
	{
		initialBalance = stod(balance);
		if (initialBalance > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (const exception&)
	{
		return false;
	}
}
