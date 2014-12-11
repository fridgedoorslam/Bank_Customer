#include "Checking_Account.h"
#include "Savings_Account.h"
#include "CD_Account.h"
#include "Loan.h"

Account::Account(){};
//Constructors
Account::Account(int number, double balance, Date date) {
	account_number = number;
	opening_balance = balance;
	opening_date = date;
}


//Getters
int Account::getType() const { return type; }

int Account::getNumber() const { return account_number; }

double Account::getBalance() { return opening_balance; }

vector<Customer*> Account::getOwners() { return pOwners; }

Date Account::getDate() const { return opening_date; }

vector<Transaction*>& Account::getTransactions() { return pTransactions; } //Changed to const for iter

//Setters
void Account::setType(int Type) { type = Type; }

void Account::setNumber(int NUMBER) { account_number = NUMBER; }

void Account::setBalance(double BALANCE) { opening_balance = BALANCE; }

void Account::setOwner(Customer* OWNER) { pOwners.push_back(OWNER); }

void Account::setDate(Date DATE) { opening_date = DATE; }

void Account::setTransaction(Transaction* TRANSACTION) { pTransactions.push_back(TRANSACTION); }

//Operators
istream& operator>>(istream& INPUT, vector<Account*>& vector) {
	int type, number;
	double balance;
	Date date;
	INPUT >> type >> number >> balance >> date;
	if (type == 1) {
		Checking_Account* new_account = new Checking_Account(number, balance, date);
		vector.push_back(new_account);
	}
	else if (type == 2) {
		Savings_Account* new_account = new Savings_Account(number, balance, date);
		vector.push_back(new_account);
	}
	else if (type == 3) {
		double interest_rate;
		Date maturity_date;
		INPUT >> interest_rate >> maturity_date;
		CD_Account* new_account = new CD_Account(number, balance, date, interest_rate, maturity_date);
		vector.push_back(new_account);
	}
	else if (type == 4) {
		double interest_rate;
		INPUT >> interest_rate;
		Loan* new_account = new Loan(number, balance, date, interest_rate);
		vector.push_back(new_account);
	}
	return INPUT;
}

//Functions
double Account::calculate_total() {
	double total = opening_balance;
	vector<Transaction*>::const_iterator transaction_iter;
	sort(pTransactions.begin(), pTransactions.end(), sort_transactions);
	for (transaction_iter = pTransactions.begin(); transaction_iter != pTransactions.end(); ++transaction_iter) {
		if ((*transaction_iter)->getType() == "d") {
			total += (*transaction_iter)->getAmount();
		}
		else {
			total -= (*transaction_iter)->getAmount();
		}
	}
	return total;
}

int Account::calculate_months(const Date& todays_date, const Date& opening_date) {
	int months = ((todays_date.getYear() - opening_date.getYear()) * 12) +
		(todays_date.getMonth() - opening_date.getMonth());
	return months;
}

bool sort_transactions(Transaction* a, Transaction* b) {
	if (a->getDate() < b->getDate()) {
		return true;
	}
	return false;
}