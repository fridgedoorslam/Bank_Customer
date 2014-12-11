#ifndef Checking_Account_h_
#define Checking_Account_h_
#include "Account.h"


class Checking_Account : public Account {
public:
	Checking_Account(int, double, Date&);
	double getMonthlyFee();
	double getOverdraftFee();
private:
	double monthly_fee;
	double overdraft_fee;
};

#endif