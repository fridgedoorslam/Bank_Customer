#ifndef Loan_h
#define Loan_h
#include <iostream>
#include "Account.h"


class Loan : public Account {
public:
	//Constructor
	Loan(int, double, Date&, double);

	//Getters
	double getInterest() const;

	//Setters
	void setInterest(double);

private:
	double interest_rate;

};

#endif