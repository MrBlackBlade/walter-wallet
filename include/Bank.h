#pragma once
#include "User.h"
#include <unordered_map>
using namespace std;
class Bank
{
	static unordered_map<string, User> users;
public:
	static void init();
	static void makeUsers();
	static unordered_map<string, User> getUsers();
};

