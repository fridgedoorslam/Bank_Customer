#include <iostream>
#include "Savings_Account.h"
#include "Account.h"

using namespace std;

Savings_Account::Savings_Account(){};

Savings_Account::Savings_Account(int number, double balance, Date& date) : Account(number, balance, date)
{
	type = 2;
	interest_rate = 0.01;
}

double Savings_Account::getInterestRate() { return interest_rate; }