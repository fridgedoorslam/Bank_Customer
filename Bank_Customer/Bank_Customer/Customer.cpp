#include "Customer.h"

//Default constructor

//Constructor
Customer::Customer(int ID, int SSN, string FIRST, string LAST, string ADDRESS) {
	customer_id = ID;
	social_security = SSN;
	first_name = FIRST;
	last_name = LAST;
	address = ADDRESS;
}

//Getters
int Customer::getId() const { return customer_id; }

int Customer::getSocial() const { return social_security; }

string Customer::getFirst() const { return first_name; }

string Customer::getLast() const { return last_name; }

string Customer::getAddress() const { return address; }

const vector<Account*>& Customer::getAccounts() const { return pAccounts; }

//Setters
void Customer::setId(int ID) { customer_id = ID; }

void Customer::setSocial(int SSN) { social_security = SSN; }

void Customer::setFirst(string FIRST) { first_name = FIRST; }

void Customer::setLast(string LAST) { last_name = LAST; }

void Customer::setAddress(string ADDRESS) { address = ADDRESS; }

void Customer::setAccount(Account* ACCOUNT) { pAccounts.push_back(ACCOUNT); }


//Operators

//Input operator
istream& operator>>(istream& INPUT, vector<Customer*>& vector) {
	int new_id, new_ssn;
	string new_first, new_last, new_address;
	INPUT >> new_id >> new_ssn >> new_first >> new_last;
	INPUT >> std::ws;
	getline(INPUT, new_address);
	Customer* new_customer = new Customer(new_id, new_ssn, new_first, new_last, new_address);
	vector.push_back(new_customer);
	return INPUT;
}