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
	return !(userExists(name) or adminExists(name));
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

bool Validation::userExists(string name)
{
	bool userExists = false;

	if (Bank::getUsers()->getUser(name) != 0) {
		userExists = true;
	}

	return userExists;
}

bool Validation::adminExists(string name)
{
	bool userExists = false;

	if (Bank::getUsers()->getAdmin(name) != 0) {
		userExists = true;
	}

	return userExists;
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

bool Validation::sentAmountValid(string balance, User* user)
{
	if (sentAmountTypeValid(balance)) {
		if
			(
				sentAmountInRangeValid(balance)
				&& sentAmountEnoughFundsValid(balance, user)
			)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Validation::sentAmountTypeValid(string balance)
{
	double sentAmount;

	try
	{
		sentAmount = stod(balance);
		return true;
	}
	catch (const exception&)
	{
		return false;
	}
}

bool Validation::sentAmountInRangeValid(string balance)
{
	double sentAmount;

	try
	{
		sentAmount = stod(balance);
		if (stod(balance) > 0 and stod(balance) < 999999) {
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

bool Validation::sentAmountEnoughFundsValid(string balance, User* user)
{
	double sentAmount;

	try
	{
		sentAmount = stod(balance);
		if (stod(balance) <= user->getBalance()) {
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

bool Validation::requestedAmountValid(string balance)
{
	if (requestedAmountTypeValid(balance)) {
		if
			(
				requestedAmountInRangeValid(balance)
			)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Validation::requestedAmountTypeValid(string balance)
{
	double requestedAmount;

	try
	{
		requestedAmount = stod(balance);
		return true;
	}
	catch (const exception&)
	{
		return false;
	}
}

bool Validation::requestedAmountInRangeValid(string balance)
{
	double requestedAmount;

	try
	{
		requestedAmount = stod(balance);
		if (stod(balance) > 0 and stod(balance) < 100000) {
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

bool Validation::cardNumberValid(string cardNumber)
{
	if (regex_match(cardNumber, regex(R"(^(\d{16})$)")))
		return true;
	else
		return false;
}

bool Validation::cvvValid(string cvv)
{
	if (regex_match(cvv, regex(R"(^(\d{3})$)")))
		return true;
	else
		return false;
}

bool Validation::rechargeAmountValid(string balance)
{
	double rechargeAmount;

	try
	{
		rechargeAmount = stod(balance);
		if (stod(balance) > 0 and stod(balance) < 10000) {
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
