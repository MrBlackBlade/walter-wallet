#pragma once
#include <map>
#include "Transaction.h"
using namespace std;
class TransactionStructure
{
private:
	map<long, Transaction*> transactionsByTime;
	multimap<double, Transaction*> transactionsByAmount;
public:
	void insert(Transaction* transaction);
	vector<Transaction*> get();
	vector<Transaction*> get(long start, long end);
	vector<Transaction*> get(double start, double end);
};

