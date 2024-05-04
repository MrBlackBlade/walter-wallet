#pragma once
#include <map>
#include <unordered_map>
#include <list>
#include "Transaction.h"
using namespace std;

class User;
class Transaction;

class TransactionStructure
{
private:
	list<Transaction> transactions;
	map<long, Transaction*> transactionsByTime;
	multimap<double, Transaction*> transactionsByAmount;
	unordered_map<User*, map<long, Transaction*>> transactionsByUser;
public:
	void insert(Transaction* transaction);
	vector<Transaction*> get();
	vector<Transaction*> get(User* user);
	vector<Transaction*> get(long start, long end);
	vector<Transaction*> get(double start, double end);
};

