#ifndef Savings_Account_h_
#define Savings_Account_h_
#include "Account.h"


class Savings_Account : public Account {

public:
	//Constructors
	Savings_Account();
	Savings_Account(int, double, Date&);

	//Getters
	double getInterestRate();

	//Setters
	void setInterestRate(double);

private:
	double interest_rate;
};

#endif