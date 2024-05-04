#include "Bank.h"


unordered_map<string, User> Bank::users;
TransactionStructure Bank::transactions;

void Bank::init() {
	makeUsers();
	makeTransactions();
}

void Bank::makeUsers() {
	vector<vector<string>> usersTable = FileSystemManagement::readFile(FileSystemManagement::userFile);
	VirtualUser::setMaxID(stoi(usersTable.back().front()));
	for (vector<string> row : usersTable) {
		User user = User(
			stoi(row[0]),
			row[1],
			row[2],
			row[3],
			stod(row[4]),
			row[5],
			row[6],
			(row[7] == "true")
		);
		users.insert(make_pair(user.getUsername(), user));
	}

}

void Bank::makeTransactions() {
	vector<vector<string>> transactionsTable = FileSystemManagement::readFile(FileSystemManagement::transactionFile);
	for (vector<string> row : transactionsTable) {
		Transaction* transaction = new Transaction(
			&users.find(row[1])->second,
			&users.find(row[2])->second,
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

unordered_map<string, User>* Bank::getUsers() {
	return &users;
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

void Bank::processRequest(Transaction* transaction, TransactionState state) {
	if (state == acceptedRequest)
	{
		transaction->getSender()->setBalance((transaction->getSender()->getBalance() - transaction->getAmount()));
		transaction->getRecipient()->setBalance((transaction->getRecipient()->getBalance() + transaction->getAmount()));
	}
	transaction->setState(state);
}

//void Bank::insertTransacton(Transaction transaction) {
//	transactions.insert(transaction);
//}