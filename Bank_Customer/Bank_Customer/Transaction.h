#ifndef Transaction_h
#define Transaction_h

#include "Date.h"
#include <iostream>
#include <string>


class Transaction {
public:
	//Constructors
	Transaction();
	Transaction(int, const std::string, double, const Date&, std::string);

	//Getters
	int getAccount() const;
	std::string getType() const;
	double getAmount() const;
	const Date& getDate() const;
	std::string getInfo() const;

	//Setters
	void setAccount(int);
	void setType(const std::string);
	void setAmount(double);
	void setDate(const Date&);
	void setInfo(std::string);

	//Operators
	friend istream& operator>>(std::istream&, std::vector<Transaction*>&);
	friend ostream& operator<<(std::ostream&, const Transaction&);
	bool operator<(const Transaction&) const;

private:
	int account_number;
	std::string type, info;
	double amount;
	Date transDate;
};

#endif