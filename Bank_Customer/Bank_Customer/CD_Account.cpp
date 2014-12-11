#include <iostream>
#include "CD_Account.h"
#include "Account.h"

using namespace std;

//Constructors
CD_Account::CD_Account(int number, double balance, Date& date, double interestRate, Date& maturityDate) : Account(number, balance, date), interest_rate(interestRate), maturity_date(maturityDate)
{
	type = 3;
	interest_rate = interestRate;
	maturity_date = maturityDate;
}

//Getters
double CD_Account::getInterest() const { return interest_rate; }

Date& CD_Account::getMaturityDate() const { return maturity_date; }

//Setters
void CD_Account::setInterest(double interestRate) { interest_rate = interestRate; }

void CD_Account::setDate(Date& maturityDate) { maturity_date = maturityDate; }