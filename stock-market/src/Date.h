#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
*  A class used to represent a date. Each date object contains 3 integers, representing day, month and year.
*/

class Date {
private:
	unsigned day;	/**< unsigned day. Unsigned Integer representing the date day. */
	unsigned month;	/**< unsigned month. Unsigned Integer representing the date month. */
	unsigned year;	/**< unsigned year. Unsigned Integer representing the date year. */

public:
	
	/**
	* A default constructor.
	* The default construtor creates a date object with the current system date.
	*/
	Date(); 
	
	/**
	* A constructor.
	* The construtor creates a date object with the specified date string specified as argument.
	* @param data A string with the date in the DD/MM/YY format
	*/
	Date(string data); 
	
	/**
	* A constructor.
	* The construtor creates a date object with the specified day, month and year passed as arguments.
	* @param day A unsigned short representing the day
	* @param month A unsigned short representing the month
	* @param year A unsigned short representing the year
	*/
	Date(int day, int month, int year);
	
	/**
	* A member function with no arguments to get the date's day.
	* @return An integer, the date's day
	*/
	int get_day() const;
	
	/**
	* A member function with no arguments to get the date's month.
	* @return An integer, the date's month
	*/
	int get_month() const;

	/**
	* A member function with no arguments to get the date's year.
	* @return An integer, the date's year
	*/
	int get_year() const;

	/**
	* Operator << for class Date.
	* Prints the specified Date as 2nd argument in the outstream passed as 1st argument.
	* @param out The outstream to write to.
	* @param date The date to be written.
	* @return Returns the output stream to allow chainning
	*/
	friend ostream& operator<<(ostream& out, const Date & date);

	/**
	* Operator >> for Date class.
	* Reads the dare from the input stream to change de date object.
	* @param in Input stream where to read the date from
	* @param date Date object to be changed
	* @return Returns the input stream to allow chainning
	*/
	friend istream& operator>>(istream& in, Date& date);

	/**
	* Overload of Operator <= for class Date.
	* @param d1 First date
	* @param d2 Second date
	* @return Returns a boolean value, true if d1 <= d2
	*/
	friend bool operator<=(const Date& d1, const Date& d2);

	/**
	* Overload of Operator < for class Date.
	* @param d1 First date
	* @param d2 Second date
	* @return Returns a boolean value, true if d1 < d2
	*/
	friend bool operator<(const Date& d1, const Date& d2);

	/**
	* Overload of Operator == for class Date.
	* @param d1 First date
	* @param d2 Second date
	* @return Returns a boolean value, true if d1 equals d2
	*/
	friend bool operator==(const Date& d1, const Date& d2);
};


