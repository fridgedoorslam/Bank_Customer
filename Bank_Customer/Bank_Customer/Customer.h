#ifndef Customer_h
#define Customer_h

#include <string>
#include <vector>
#include <iostream>
#include "Account.h"
#include "Bank.h"

class Bank;

class Customer
{
public:
	//Constructors
	Customer();
	Customer(int, int, std::string, std::string, std::string);

	//Getters
	int getId() const;
	int getSocial() const;
	std::string getFirst() const;
	std::string getLast() const;
	std::string getAddress() const;
	const std::vector<Account*>& getAccounts() const;

	//Setters
	void setId(int);
	void setSocial(int);
	void setFirst(std::string);
	void setLast(std::string);
	void setAddress(std::string);
	void setAccount(Account*);

	//Operators
	friend std::istream& operator>>(std::istream&, std::vector<Customer*>&);

private:
	int customer_id, social_security;
	std::string first_name, last_name, address;
	std::vector<Account*> pAccounts;
};

#endif