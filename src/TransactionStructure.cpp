#include "TransactionStructure.h"


void TransactionStructure::insert(Transaction* transaction) {
	transactionsByTime.insert(make_pair(transaction->getEpochTime(), transaction));
	transactionsByAmount.insert(make_pair(transaction->getAmount(), transaction));
}

vector<Transaction*> TransactionStructure::get() {
	vector<Transaction*> transactions;
	for (auto i = transactionsByTime.begin(); i != transactionsByTime.end(); i++) {
		transactions.push_back(i->second);
	}
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