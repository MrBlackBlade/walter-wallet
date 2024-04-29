#include "validation.h"
#include<regex>
std::string Validation::name(std::string name)
{
	// The name contains charecters, digits, underscores and dashes
	// and it shouldn't start or end with underscore or dash
	std::regex name_pattern(R"(^[a-zA-Z0-9]+([_\- ]?[a-zA-Z0-9]+)*$)");
	if (regex_match(name, name_pattern))
		return "1";
	else
	{
		std::regex char_check(R"(^[a-zA-Z0-9_-]+$)");
		std::regex length_check(R"(^\d{1,10}$)");
		if (!regex_match(name, char_check))
			return "Username contains invalid character. Only charecters [Aa-Zz], digits[0-9] and [_-] are allowed";
		else if (!regex_match(name, length_check))
			return "Too long username. Max lenght is 10 digits";
	}
}

std::string Validation::password(std::string password)
{
	// Ensures the password consists of at least 8 digits as followes
	/*
	* at least one uppercase letter
	* at least one lowercase letter
	* at least one number
	* at least on of the specified speacial characters: ~!@#$%^&*:;()<>_-
	*/
	std::regex password_pattern(R"((?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[~!@#$%^&*:;()<>_-]).{8,})");
	if (regex_match(password, password_pattern))
		return "1";
	else
	{
		std::regex upper_lower_case_check(R"(^(?=.*[A-Z])(?=.*[a-z]).*$)");
		std::regex number_check(R"(^(?=.*\d).*$)");
		std::regex special_char_check(R"(^(?=.*[~!@#$%^&*:;()<>_-]).*$)");
		std::regex min_length_check(R"(^.{8,}$)");

		if (!regex_match(password, min_length_check))
			return "Too short password. At least 8 digits";
		else if (!regex_match(password, upper_lower_case_check))
			return "Password must contain at least one uppercase and one lowercase letter";
		else if (!regex_match(password, number_check))
			return "Password must contain at least one number";
		else if (!regex_match(password, special_char_check))
			return "Password must contain at least one special character [~!@#$%^&*:;()<>_-]";
	}
}

std::string Validation::email(std::string email)
{
	// Ensures that email match the format: something@example.com |.net |.edu |.org |.gov |.mil
	std::regex email_pattern(R"((\w+)(\.\w+)*@(\w+)(\.(com|net|edu|gov|mil|org)))");
	if (regex_match(email, email_pattern))
		return "1";
	else
		return "Invalid email address";
}

std::string Validation::phoneNumber(std::string phone_number)
{
	// Ensures that the phone number
	/*
	* Consists of exactly 11 digit
	* Starts with 010|011|012|015
	*/
	std::regex phone_number_pattern(R"(^(010|011|012|015)\d{8}$)");
	if (regex_match(phone_number, phone_number_pattern))
		return "1";
	else
		return "Invalid phone number. It must be 11 digit in the format: 01xxxxxxxxx";
}
