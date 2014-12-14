#include <string>
#include "Transaction.h"

//Default Constructor
Transaction::Transaction(){
	amount = 0.0;
}

//Constructor
Transaction::Transaction(int Number, const string Type, double Amount, const Date& TransDate, string Info) {
	account_number = Number;
	type = Type;
	amount = Amount;
	transDate = TransDate;
	info = Info;
}

//Getters
int Transaction::getAccount() const { return account_number; }

string Transaction::getType() const { return type; }

double Transaction::getAmount() const { return amount; }

const Date& Transaction::getDate() const { return transDate; }

string Transaction::getInfo() const { return info; }

//Setters
void Transaction::setAccount(int Account) { account_number = Account; }

void Transaction::setType(const string Type) { type = Type; }

void Transaction::setAmount(double Amount) { amount = Amount; }

void Transaction::setDate(const Date& TransDate) { transDate = TransDate; }

void Transaction::setInfo(string Info) { info = Info; }


//Operators

//Input Operator
istream& operator>>(istream& Input, vector<Transaction*>& Vector) {
	int account;
	string type, info;
	double amount;
	Date date;
	Input >> account >> type >> amount >> date;
	Input >> std::ws;
	getline(Input, info);
	Transaction* new_transaction = new Transaction(account, type, amount, date, info);
	Vector.push_back(new_transaction);
	return Input;
}

//Output Operator
ostream& operator<<(ostream& Output, const Transaction& Transaction) {
	Output << Transaction.getDate();
	if (Transaction.getType() == "d") {
		cout << " Deposit, $" << Transaction.getAmount() << " from" << Transaction.getInfo() << ".";
	}
	else {
		cout << " Withdrawal, $" << Transaction.getAmount() << " to" << Transaction.getInfo() << ".";
	}
	return Output;
}

//Less than Operator
bool Transaction::operator<(const Transaction& Transaction) const {
	if (getDate() < Transaction.getDate()) { return true; }
	else if (getDate() == Transaction.getDate() && getType() == "d") { return true; }
	else { return false; }
}