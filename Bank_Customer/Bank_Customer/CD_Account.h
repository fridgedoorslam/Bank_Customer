#ifndef CD_Account_h_
#define CD_Account_h_
#include "Account.h"


class CD_Account : public Account {
public:
	//Constructor
	CD_Account(int, double, Date&, double, Date&);

	//Getters
	double getInterest() const;
	Date& getMaturityDate() const;

	//Setters
	void setInterest(double);
	void setDate(Date&);

private:
	double interest_rate;
	Date& maturity_date;
};

#endif
