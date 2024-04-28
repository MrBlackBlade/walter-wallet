#pragma once
#include<string>
class Validation
{
public:
	static std::string name(std::string name);
	static std::string password(std::string password);
	static std::string email(std::string email);
	static std::string phone_number(std::string phone_number);
};
