#pragma once
#include <string>
#include "Bank.h"

using namespace std;

class Validation
{
public:
	static bool usernameValid(string name);
	static bool usernameAvailable(string name);
	static bool usernameValidLength(string name);
	static bool usernameValidCharacterSet(string name);

	static bool userExists(string name);
	static bool adminExists(string name);

	static bool passwordValid(string password);
	static bool passwordValidLength(string password);
	static bool passwordValidCharacterSet(string password);
	static bool passwordValidCase(string password);
	static bool passwordContainsNumbers(string password);
	static bool passwordContainsSpecialCharacters(string password);

	static bool displayNameValid(string name);

	static bool emailValidFormat(string email);

	static bool phoneNumberValidFormat(string phoneNumber);

	static bool initialBalanceValid(string balance);
	static bool balanceValid(string balance);

	static bool sentAmountValid(string balance, User* user);
	static bool sentAmountTypeValid(string balance);
	static bool sentAmountInRangeValid(string balance);
	static bool sentAmountEnoughFundsValid(string balance, User* user);

	static bool requestedAmountValid(string balance);
	static bool requestedAmountTypeValid(string balance);
	static bool requestedAmountInRangeValid(string balance);

	static bool cardNumberValid(string cardNumber);
	static bool cvvValid(string cvv);
	static bool rechargeAmountValid(string balance);
};
