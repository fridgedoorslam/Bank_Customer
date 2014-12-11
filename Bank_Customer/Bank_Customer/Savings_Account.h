#ifndef Savings_Account_h_
#define Savings_Account_h_
#include "Account.h"


class Savings_Account : public Account {
public:
	Savings_Account();
	Savings_Account(int, double, Date&);
	double getInterestRate();
private:
	double interest_rate;
};

#endif