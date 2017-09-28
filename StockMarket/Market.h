#pragma once

#include <map>
#include <vector>
#include "Client.h"
#include "Transaction.h"
#include "Order.h"

using namespace std;


/**
*  Singleton Class to implement most of the logic behind the StockMarket
*/

class Market
{
private:
	static Market * singleton_instance;  /**< Market pointer. Contains the pointer to the singleton instance of Market. */
	nif_t currentNIF;					/**<  nif_t NIF. Saves the NIF of the current user. */
	
	/**
	* A default constructor.
	*/
	Market();

	/**
	* A destructor.
	* Deletes all dynamically allocated memory.
	*/
	~Market();	

	map<nif_t, Client *> clients;			/**< Map clients. A map where the key's are clients NIF's and the values are client pointers. Corresponds a NIF and a client. */
	vector<Transaction *> transactions;		/**< Vector transactions. A vector saving pointers of all Market's transactions. */
	vector<Order *> unfulfilled_orders;		/**< Vector unfulfilled_orders. A vector saving pointers of all Market's unfulfilled orders. */

	string clientsFile;		   /**< string clientsFile. String with the client's file name. */
	string ordersFile;         /**< string ordersFile. String with the order's file name. */
	string transactionsFile;   /**< string transactionsFile. String with the transaction's file name. */
	string companysFile;       /**< string companysFile. String with the company's file name. */
	
	bool clientsChanged;	   /**<	bool clientsChanged. Boolean set to true if any changes done to the clients during execution. */	
	bool transactionsChanged;  /**< bool transactionsChanged. Boolean set to true if any changes done to the transactions during execution. */
	bool ordersChanged;		   /**< bool ordersChanged. Boolean set to true if any changes done to the orders during execution. */
	bool companysChanged;     /**< bool companysChanged. Boolean set to true if any changes done to the companys during execution. */

public:

	/**
	* A member function returning the one and only instace of Market (creates it if one doesn't exist).
	* @return A pointer to the singleton instance of Market.
	*/
	static Market * instance();

	/**
	* A member function that signs in the user.
	* @param name Name of the client/user
	* @param nif  NIF othe client/user
	* @return A boolean, true if signing in was done successfully.
	*/
	bool signIn(string name, nif_t nif);

	/**
	* A member function that signs out the user.
	*/
	void signOut();

	/**
	* A member function that signs up the user.
	* @param name Name of the client/user
	* @param nif  NIF othe client/user
	* @return A boolean, true if signing up was done successfully.
	*/
	bool signUp(string name, nif_t nif);

	/**
	* A member function that returns the current user's NIF.
	* @return The current user's nif.
	*/
	nif_t getCurrentNIF() const;

	/**
	* A const member function that displays the client's information.
	*/
	void showClientInfo() const;

	/**
	* A const member function that displays the client's history of transactions.
	*/
	void showClientHistory() const;

	/**
	* A const member function that displays the client's unfulfilled orders.
	*/
	void showClientOrders() const;

	/**
	* A member function that erases a client's unfulfilled order.
	* @param The number corresponding to the order to be erased (sorted by date placed).
	* @return A boolean, true if deletion of the order was done successfully.
	*/
	bool eraseClientOrder(unsigned choice);

	/**
	* A const member function that displays the buy orders.
	*/
	void listBuyOrders() const;

	/**
	* A const member function that displays the sell orders.
	*/
	void listSellOrders() const;

	/**
	* A const member function used to get the client's history of transactions.
	* @param c A client pointer.
	* @return A vector of the client's transactions.
	*/
	vector<Transaction*> clientHistory(Client * c) const;

	/**
	* A const member function that prints the transactions to the COUT output stream.
	*/
	void printTransactions() const;

	/**
	* Overload of member function that prints the transactions of a given Stock.
	* @param stock The Stock's name.
	*/
	void printTransactions(string stock) const;

	/**
	* Overload of member function that prints the transactions between 2 days.
	* @param day1 The first day of the interval.
	* @param day2 The last day of the interval.
	*/
	void printTransactions(Date day1, Date day2) const;

	/**
	* Overload of member function that prints the daily transactions.
	* @param d The day whose transactions will be shown. 
	*/
	void printTransactions(Date d) const;
	
	/**
	* A member function that adds an order to the unfulfilledOrders vector. Can be from Sell or Buy type.
	* @param o A pointer to the order.
	*/
	pair< vector<Transaction *>::iterator, vector<Transaction *>::iterator > placeOrder(Order * o);	// Abstracts of Buy/Sell type
	
	/**
	*	A const member function that saves ALL information to the files.
	*/
	void saveChanges() const;	

	/**
	* Overload of Operator << for class Market.
	* Prints the Market statistics.
	* @param out The outstream to write to.
	* @param m The Market.
	* @return Returns the output stream to allow chainning
	*/
	friend ostream& operator<<(ostream & out, const Market & m);
};

