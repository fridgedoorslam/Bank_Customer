#ifndef Date_h
#define Date_h

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

class Date {
public:
	//Constructors
	Date();
	Date(int, int, int, char);

	//Getters
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	char getSlash() const;

	//Setters
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	void setSlash(char);

	//Functions
	void printDate() const;

	//Operators
	friend istream& operator>>(istream&, Date&);
	friend ostream& operator<<(ostream&, const Date&);
	bool operator ==(const Date&) const;
	bool operator <(const Date&) const;

private:
	int day, month, year;
	char slash;
};

//Other Functions
int calculateDays(int);

#endif