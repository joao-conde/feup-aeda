#pragma once

#include <string>
#include "defs.h"
#include "utils.h"


using namespace std;


class Investor {

private:
	string name; /**< string name. The investors's name. */
	tlmv_t phone; /**< tlmv_t phone. The investor's phone number. */
	double maxInvestment; /**< double maxInvestment. The maximum value the investors is willing to spend. */
	double availableBudget; /**< double availableBudget. The investor's budget used to finance. */

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
	Investor(string name, tlmv_t phone, double maxInvest = 0, double budget = 0);

	/**
	* A getter method returning investor's budget.
	* @return Returns the investor's budget.
	*/
	double getBudget() const;

	/**
	* A getter method returning investor's maximum investment.
	* @return Returns the investor's maximum investment.
	*/
	double getMaxInv() const;

	/**
	* A getter method returning investor's phone number.
	* @return Returns the investor's phone number.
	*/
	tlmv_t getPhoneNumber() const;

	/**
	* Debits the investor budget with an amount invested.
	* @param value The value of the investment.
	*/
	void debitInvest(double value);

	/**
	* Adds capital to the investor.
	* @param loan The value of the loan to the investor.
	*/
	void addBudget(double loan);

	/**
	* Updates the investor phone number with a new one.
	* @param phone The new investor's phone number.
	*/
	void updatePhoneN(tlmv_t phone);

	/**
	* Overload of Operator << for class Investor.
	* Prints the investor in a human friendly way.
	* @param out The outstream to write to.
	* @param i The investor to be written.
	* @return Returns the output stream to allow chainning
	*/
	friend ostream& operator<<(ostream& out, const Investor &i);

	/**
	* Overload of Operator == for class Investor.
	* Compares 2 investor's.
	* @param i1 Left side Investor.
	* @param i2 Right side Investor.
	* @return Returns true if i1 equals i2 meaning same name and phone number (unique qualifiers). False otherwise.
	*/
	friend bool operator==(const Investor &i1, const Investor &i2);

	/**
	* Overload of Operator < for class Investor.
	* Compares 2 investor's.
	* @param i1 Left side Investor.
	* @param i2 Right side Investor.
	* @return Returns true if i1 has a greater or equal budget than i2. False otherwise.
	*/
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
		return i1 == i2; // Two investor's are distinct if their pointers are distinct
	}
};