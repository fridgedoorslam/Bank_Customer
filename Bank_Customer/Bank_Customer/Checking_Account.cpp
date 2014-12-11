#include <iostream>
#include "Checking_Account.h"
#include "Account.h"

using namespace std;

Checking_Account::Checking_Account(int number, double balance, Date& date) : Account(number, balance, date)
{
	type = 1;
	monthly_fee = 5;
	overdraft_fee = 10;
}

double Checking_Account::getMonthlyFee() { return monthly_fee; }
double Checking_Account::getOverdraftFee() { return overdraft_fee; }