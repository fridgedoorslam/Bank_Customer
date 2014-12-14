#ifndef Checking_Account_h_
#define Checking_Account_h_
#include "Account.h"


class Checking_Account : public Account {
public:
	//Constructor
	Checking_Account(int, double, Date&);
	
	//Getters
	double getMonthlyFee();
	double getOverdraftFee();

	//Setters
	void setMonthlyFee(double);
	void setOverdraftFee(double);

private:
	double monthly_fee;
	double overdraft_fee;
};

#endif