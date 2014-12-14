#include <iostream>
#include "Savings_Account.h"
#include "Account.h"

using namespace std;

//Constructor
Savings_Account::Savings_Account(int number, double balance, Date& date) : Account(number, balance, date)
{
	type = 2;
	interest_rate = 0.01;
}

//Getters
double Savings_Account::getInterestRate() { return interest_rate; }

//Setters
void Savings_Account::setInterestRate(double interest_rate) { interest_rate = 0.01; }