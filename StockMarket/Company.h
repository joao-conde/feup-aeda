#pragma once

#include <iostream>
#include <string>

#include "utils.h"


//typedef unsigned int nif_t;

using namespace std;

class Company {

private:
	
	string name, business_area;
	nif_t NIF;
	double max_transaction_value;

public:

	/**
	* A default constructor.
	*/
	Company() = default;

	/**
	* A constructor.
	* The construtor creates a company object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the company object.
	*/
	Company(ifstream& in);

	/**
	* A constructor.
	* The construtor creates a company object using the data passed as arguments.
	* @param name The company name.
	* @param activity The company business area.
	* @param NIF The company NIF.
	* @param max_transaction The highest value transaction ever made by that company.
	*/
	Company(string name, string activity, nif_t NIF, double max_transaction);


	/**
	* A const member function that returns the name of the company.
	*/
	string getName() const;

	/**
	* A const member function that returns the business area of a certain company.
	*/
	string getArea() const; 

	/**
	* A const member function that returns the maximum transaction value.
	*/
	double getValue() const;

	/**
	* A member function that changes the maximum transaction value.
	*/
	void setValue(double value);

	/**
	* A const member function to write the company to a save file.
	* @param out The outputstream file to write to.
	*/
	void saveChanges(ofstream& out) const;

	/**
	* Overload of Operator << for class Company.
	* Prints the company in a human friendly way.
	* @param out The outstream to write to.
	* @param c The company to be written.
	* @return Returns the output stream to allow chainning
	*/
	friend ostream& operator<<(ostream&, const Company&);

	friend bool operator<(const Company &c1, const Company &c2);

};