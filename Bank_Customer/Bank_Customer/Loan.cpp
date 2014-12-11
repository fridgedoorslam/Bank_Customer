#include "Loan.h"
#include "Account.h"

using namespace std;

//Constructors
Loan::Loan(int number, double balance, Date& date, double interestRate) : Account(number, balance, date), interest_rate(interestRate)
{
	type = 4;
	interest_rate = interestRate;

}

//Getters
double Loan::getInterest() const { return interest_rate; }

//Setters
void Loan::setInterest(double interestRate) { interest_rate = interestRate; }