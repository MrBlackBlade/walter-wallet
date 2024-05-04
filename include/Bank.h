#pragma once
#include "User.h"
#include "Transaction.h"
#include "TransactionStructure.h"
#include <unordered_map>
#include "VirtualUser.h"
#include "FileSystemManagement.h"
#include <chrono>
using namespace std;

class User;
enum TransactionState;
class Transaction;
class TransactionStructure;

class Bank
{
	static unordered_map<string, User> users;
	static TransactionStructure transactions;
public:
	static void init();
	static void makeUsers();
	static void makeTransactions();
	static void makeNewTransaction(User* sender, User* recipient, double amount, TransactionState state);
	static void processRequest(Transaction* transaction, TransactionState state);
	static unordered_map<string, User>* getUsers();
	static TransactionStructure* getTransactions();
	/*static void insertTransacton(Transaction transaction);*/
};

