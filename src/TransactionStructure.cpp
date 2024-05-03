#include "TransactionStructure.h"


void TransactionStructure::insert(Transaction* transaction) {
	transactions.push_back(*transaction);
	/*for (string e : transaction.toStringArray()) {
		cout << e << "--";
	}
	cout << endl;*/
	transactionsByTime.insert(make_pair(transaction->getEpochTime(), &(transactions.back())));
	transactionsByAmount.insert(make_pair(transaction->getAmount(), &(transactions.back())));
	map<long, Transaction*>& senderTransactions = transactionsByUser[transactions.back().getSender()];
	senderTransactions.insert(make_pair(transaction->getEpochTime(), &(transactions.back())));
	map<long, Transaction*>& recieverTransactions = transactionsByUser[transactions.back().getReciever()];
	recieverTransactions.insert(make_pair(transaction->getEpochTime(), &(transactions.back())));
}

vector<Transaction*> TransactionStructure::get() {
	vector<Transaction*> transactions;
	for (auto i = transactionsByTime.begin(); i != transactionsByTime.end(); i++) {
		transactions.push_back(i->second);
	}
	/*for (Transaction* transaction : transactions) {
		for (string e : transaction->toStringArray()) {
			cout << e << "+++";
		}
		cout << endl;
	}*/
	return transactions;
}

vector<Transaction*> TransactionStructure::get(User* user) {
	vector<Transaction*> transactions;
	for (auto i = transactionsByUser[user].begin(); i != transactionsByUser[user].end(); i++) {
		transactions.push_back(i->second);
	}
	/*for (Transaction* transaction : transactions) {
		for (string e : transaction->toStringArray()) {
			cout << e << "+++";
		}
		cout << endl;
	}*/
	return transactions;
}

vector<Transaction*> TransactionStructure::get(long start, long end) {
	vector<Transaction*> transactions;
	for (auto i = transactionsByTime.lower_bound(start); i != transactionsByTime.upper_bound(end); i++) {
		transactions.push_back(i->second);
	}
	return transactions;
}

vector<Transaction*> TransactionStructure::get(double start, double end) {
	vector<Transaction*> transactions;
	for (auto i = transactionsByAmount.lower_bound(start); i != transactionsByAmount.upper_bound(end); i++) {
		transactions.push_back(i->second);
	}
	return transactions;
}