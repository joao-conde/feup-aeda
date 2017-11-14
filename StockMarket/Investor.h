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

	double getBudget() const;
	double getMaxInv() const;
	tlmv_t getPhoneNumber() const;

	void debitInvest(double value);

	friend ostream& operator<<(ostream& out, const Investor &i);

	friend bool operator<(const Investor &i1, const Investor &i2);
};

/**
* A structure to encapsulate the Hash and Comparison functions of Investor Pointers.
*/
struct investorPtrHash
{
	/**
	* Hash Function for Investor*
	* @param i Pointer to an Investor object.
	* @return hash value.
	*/
	int operator() (const Investor * i) const
	{
		return (int)i->getPhoneNumber();
	}

	/**
	* Comparison Function for Investor*
	* @param i1 Pointer to an Investor object.
	* @param i2 Pointer to an Investor object.
	* @return true if Investors pointed by i1 and i2 are the same, false otherwise.
	*/
	bool operator() (const Investor * i1, const Investor * i2) const
	{
		return i1 == i2; // Two client's are distinct if their pointers are distinct
	}
};