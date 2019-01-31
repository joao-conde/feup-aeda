#pragma once

#include <iostream>
#include "Client.h"
#include "Date.h"
#include "defs.h"

class Client;

/*
Class to represent a transaction
*/

/**
*  A class used to represent a transaction.
*/

class Transaction
{
	nif_t sellerNIF;	/**< nif_t sellerNIF. The NIF from the client that sold the stock. */
	nif_t buyerNIF;		/**< nif_t buyerNIF. The NIF from the client that bought the stock. */
	string stock;		/**< string stock. The name of the stock product. */
	double value;		/**< double value. The value of the stock. */
	unsigned quantity;	/**< unsigned quantity. The quantity of stock. */
	Date time_stamp;	/**< Date time_stamp. The time where the transaction occured. */

public:

	/**
	* A default constructor.
	*/
	Transaction() = default;

	/**
	* A constructor.
	* The construtor creates a transaction object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the transaction object.
	*/
	Transaction(ifstream& in);

	/**
	* A constructor.
	* The construtor creates a transaction object using the data passed as arguments.
	* @param buyerNIF The NIF from the buyer.
	* @param sellerNIF The NIF from the seller.
	* @param stock The stock name.
	* @param value The value of the stock.
	* @param quantity The amount of stock.
	*/
	Transaction(nif_t buyerNIF, nif_t sellerNIF, string stock, double value, unsigned quantity);

	/**
	* A const member function with no arguments to get the transaction's Stock name.
	* @return A string, the Stock's name.
	*/
	string getStock() const;

	/**
	* A const member function with no arguments to get the transaction's Value Per Stock.
	* @return A double, the value per stock transactioned.
	*/
	double getValue() const;

	/**
	* A const member function with no arguments to get the transaction's quantity of stock.
	* @return An unsigned, the quantity.
	*/
	unsigned getQuantity() const;

	/**
	* A const member function with no arguments to get the transaction's seller NIF.
	* @return A nif_t , the seller NIF.
	*/
	nif_t getSellerNIF() const;

	/**
	* A const member function with no arguments to get the transaction's buyer NIF.
	* @return A nif_t , the buyer NIF.
	*/
	nif_t getBuyerNIF() const;

	/**
	* A const member function with no arguments to get the transaction's date.
	* @return A Date object , the date of the transaction.
	*/
	Date getDate() const;

	/**
	* A const member function to write the transaction to a save file.
	* @param out The outputstream file to write to.
	*/
	void saveChanges(ofstream& out) const;

	friend ostream& operator<<(ostream&, const Transaction&);
};

/**
* Overload of Operator << for class Transaction.
* Prints the transaction in a human friendly way.
* @param out The outstream to write to.
* @param t The transaction to be written.
* @return Returns the output stream to allow chainning
*/
ostream& operator<<(ostream& out, const Transaction& t);