#include "Customer.h"

//Default constructor

//Constructor
Customer::Customer(int Id, int SSN, string First, string Last, string Address) {
	customer_id = Id;
	social_security = SSN;
	first_name = First;
	last_name = Last;
	address = Address;
}

//Getters
int Customer::getId() const { return customer_id; }
int Customer::getSocial() const { return social_security; }
string Customer::getFirst() const { return first_name; }
string Customer::getLast() const { return last_name; }
string Customer::getAddress() const { return address; }
const vector<Account*>& Customer::getAccounts() const { return pAccounts; }

//Setters
void Customer::setId(int Id) { customer_id = Id; }
void Customer::setSocial(int SSN) { social_security = SSN; }
void Customer::setFirst(string First) { first_name = First; }
void Customer::setLast(string Last) { last_name = Last; }
void Customer::setAddress(string Address) { address = Address; }
void Customer::setAccount(Account* Account) { pAccounts.push_back(Account); }


//Operators

//Input operator
istream& operator>>(istream& Input, vector<Customer*>& vector) {
	int new_id, new_ssn;
	string new_first, new_last, new_address;
	Input >> new_id >> new_ssn >> new_first >> new_last;
	Input >> std::ws;
	getline(Input, new_address);
	Customer* new_customer = new Customer(new_id, new_ssn, new_first, new_last, new_address);
	vector.push_back(new_customer);
	return Input;
}