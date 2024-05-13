#include "UserStructure.h"

void UserStructure::insert(Admin* admin)
{
	admins.push_back(*admin);

	adminsByNameOrdered.insert(make_pair(admin->getUsername(), &(admins.back())));
	adminsByName.insert(make_pair(admin->getUsername(), &(admins.back())));
	adminsByName[admin->getUsername()] = &(admins.back());
}

Admin* UserStructure::getAdmin(string username)
{
	return adminsByName[username];
}

vector<Admin*> UserStructure::getAdmins()
{
	vector<Admin*> admins;
	for (auto i = adminsByNameOrdered.begin(); i != adminsByNameOrdered.end(); i++) {
		admins.push_back(i->second);
	}

	return admins;
}

void UserStructure::insert(User* user)
{
	users.push_back(*user);

	usersByNameOrdered.insert(
		make_pair(
			user->getUsername(), &( users.back() )
		)
	);
	usersByName.insert(
		make_pair(
			user->getUsername(), &( users.back() )
		)
	);
	usersByName[user->getUsername()] = &(users.back());
}

void UserStructure::erase(Admin* admin)
{
	adminsByName.erase(admin->getUsername());
	adminsByNameOrdered.erase(admin->getUsername());

	auto it = find(admins.begin(), admins.end(),
		*admin);

	if (it != admins.end()) {
		admins.erase(it);
	}
}

void UserStructure::erase(User* user)
{
	usersByName.erase(user->getUsername());
	usersByNameOrdered.erase(user->getUsername());

	auto it = find(users.begin(), users.end(),
		*user);

	if (it != users.end()) {
		users.erase(it);
	}
}

void UserStructure::modifyUser(User* user, User newUser)
{
	usersByName.erase(user->getUsername());
	usersByNameOrdered.erase(user->getUsername());
	
	user->setBalance(newUser.getBalance());
	user->setDisplayName(newUser.getDisplayName());
	user->setEmail(newUser.getEmail());
	user->setName(newUser.getUsername());
	user->setPassword(newUser.getPassword());
	user->setPhoneNumber(newUser.getPhoneNumber());
	user->setSuspended(newUser.getSuspended());
	
	usersByNameOrdered.insert(make_pair(user->getUsername(), user));
	usersByName.insert(make_pair(user->getUsername(), user));
}

void UserStructure::modifyUser(User* user, const string username, const string displayName, double balance, const string phoneNumber, const string email, bool isSuspend)
{
	usersByName.erase(user->getUsername());
	usersByNameOrdered.erase(user->getUsername());

	user->setBalance(balance);
	user->setDisplayName(displayName);
	user->setEmail(email);
	user->setName(username);
	user->setPhoneNumber(phoneNumber);
	user->setSuspended(isSuspend);

	usersByNameOrdered.insert(make_pair(user->getUsername(), user));
	usersByName.insert(make_pair(user->getUsername(), user));
}

User* UserStructure::getUser(string username)
{
	return usersByName[username];
}

vector<User*> UserStructure::getUsers()
{
	vector<User*> users;
	for (auto i = usersByNameOrdered.begin(); i != usersByNameOrdered.end(); i++) {
		users.push_back(i->second);
	}

	return users;
}
