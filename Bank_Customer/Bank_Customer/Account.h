#ifndef Account_h
#define Account_h

#include <vector>
#include <algorithm>
#include "Transaction.h"
#include "Date.h"

class Customer;

class Account
{
public:
	Account();
	//Constructor
	Account(int, double, Date);

	//Getters
	int getType() const;
	int getNumber() const;
	double getBalance();
	Date getDate() const;
	std::vector<Transaction*>& getTransactions(); //Changed to const for iter
	std::vector<Customer*> getOwners();

	//Setters
	void setType(int);
	void setNumber(int);
	void setBalance(double);
	void setOwner(Customer*);
	void setDate(Date);
	void setTransaction(Transaction*);

	//Operators
	friend std::istream& operator>>(std::istream&, std::vector<Account*>&);

	//Functions
	double calculate_total();
	int calculate_months(const Date&, const Date&);

protected:
	int type;
	int account_number;
	double opening_balance;
	Date opening_date;
	std::vector<Transaction*> pTransactions;
	std::vector<Customer*> pOwners;
};

//Sorting function to sort vector of transaction pointers
bool sort_transactions(Transaction*, Transaction*);

#endif