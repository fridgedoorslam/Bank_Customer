#include "Date.h"

//Default Constructor
Date::Date() {
	day = 0;
	month = 0;
	year = 0;
}

//Constructor
Date::Date(int Day, int Month, int Year, char Slash) {
	day = Day;
	month = Month;
	year = Year;
	slash = Slash;
}

//Getters
int Date::getDay() const { return day; }

int Date::getMonth() const { return month; }

int Date::getYear() const { return year; }

char Date::getSlash() const { return slash; }

//Setters
void Date::setDay(int DAY){ day = DAY; }

void Date::setMonth(int MONTH){ month = MONTH; }

void Date::setYear(int YEAR){ year = YEAR; }

void Date::setSlash(char SLASH){ slash = SLASH; }


//Operators

//Input Operator
istream& operator >> (istream& input, Date& d) {
	input >> d.month >> d.slash >> d.day >> d.slash >> d.year;
	return input;
}

//Output Operator
ostream& operator<<(ostream& output, const Date& d) {
	output << d.getMonth() << d.getSlash() << d.getDay()
		<< d.getSlash() << d.getYear();
	return output;
}

//Equal Operator
bool Date::operator==(const Date& date) const {
	return ((getMonth() == date.getMonth()) &&
		(getDay() == date.getDay()) &&
		(getYear() == date.getYear()));
}

//Less than Operator
bool Date::operator<(const Date& date) const {
	if (getYear() < date.getYear()) {
		return true;
	}

	else if ((getYear() == date.getYear()) &&
		(getMonth() < date.getMonth())) {
		return true;
	}

	else if ((getYear() == date.getYear()) &&
		(getMonth() == date.getMonth()) &&
		(getDay() < date.getDay())) {
		return true;
	}

	else {
		return false;
	}
}

//Functions

int calculateDays(int month) {
	return (int)(28 + (month + (int)floor(month / 8)) % 2 + 2 % month + 2 * floor(1 / month));
}