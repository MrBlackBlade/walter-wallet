#include "Bank.h"


UserStructure Bank::users;
TransactionStructure Bank::transactions;

void Bank::init() {
	makeUsers();
	makeTransactions();
}

void Bank::makeUsers() {
	vector<vector<string>> usersTable = FileSystemManagement::readFile(FileSystemManagement::userFile);
	for (vector<string> row : usersTable) {
		if (row[0] == "admin") {
			Admin* admin = new Admin(
				row[1],
				row[2],
				row[3],
				row[4],
				row[5]
			);
			users.insert(admin);
		}
		else if (row[0] == "user") {
			User* user = new User(
				row[1],
				row[2],
				row[3],
				stod(row[4]),
				row[5],
				row[6],
				(row[7] == "true")
			);
			users.insert(user);
		}
		
	}

}

void Bank::makeTransactions() {
	vector<vector<string>> transactionsTable = FileSystemManagement::readFile(FileSystemManagement::transactionFile);
	for (vector<string> row : transactionsTable) {
		Transaction* transaction = new Transaction(
			users.getUser(row[1]),
			users.getUser(row[2]),
			stod(row[3]),
			std::chrono::system_clock::from_time_t(stol(row[0])),
			TransactionState(stoi(row[4]))
		);
		transactions.insert(transaction);
		/*transaction->getSender()->insertTransacton(transaction);
		transaction->getReciever()->insertTransacton(transaction);*/
		//transactions.insert(transaction);
	}
}

UserStructure* Bank::getUsers() {
	return &users;
}

Admin* Bank::asAdmin() {
	return users.getAdmin("admin");
}

TransactionStructure* Bank::getTransactions() {
	return &transactions;
}

void Bank::makeNewTransaction(User* sender, User* recipient, double amount, TransactionState state) {
	if (state == completedTransaction)
	{
		sender->setBalance((sender->getBalance() - amount));
		recipient->setBalance((recipient->getBalance() + amount));
	}
	transactions.insert(new Transaction(sender, recipient, amount, std::chrono::system_clock::now(), state));
}

void Bank::makeSystemTransaction(Admin* sender, User* recipient, double amount)
{
	recipient->setBalance((recipient->getBalance() + amount));
	transactions.insert(new Transaction(users.getUser("system"), recipient, amount, std::chrono::system_clock::now(), completedTransaction));
}

void Bank::makeSystemTransaction(User* sender, Admin* recipient, double amount)
{
	sender->setBalance((sender->getBalance() - amount));
	transactions.insert(new Transaction(sender, users.getUser("system"), amount, std::chrono::system_clock::now(), completedTransaction));
}

void Bank::processRequest(Transaction* transaction, TransactionState state) {
	if (state == acceptedRequest)
	{
		transaction->getSender()->setBalance((transaction->getSender()->getBalance() - transaction->getAmount()));
		transaction->getRecipient()->setBalance((transaction->getRecipient()->getBalance() + transaction->getAmount()));
	}
	transaction->setState(state);
}
