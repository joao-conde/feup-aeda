#pragma once

#include <string>
#include "defs.h"
#include "utils.h"


using namespace std;


class Investor {

private:
	string name;
	tlmv_t phone;
	double maxInvestment;
	double availableBudget;

public:
	
	/**
	* A default constructor.
	*/
	Investor() = default;

	/**
	* A constructor.
	* The construtor creates a Investor object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the Investor object.
	*/
	Investor(ifstream& in);

	/**
	* A constructor.
	* The construtor creates a Investor object using the data passed as arguments.
	* @param name The Investor name.
	*/
	Investor(string name, tlmv_t phone, double maxInvest, double budget);



};